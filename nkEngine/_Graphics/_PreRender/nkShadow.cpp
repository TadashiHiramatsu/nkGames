/**
 * @file _Graphics\_PreRender\nkShadow.cpp
 *
 * シャドウマップクラス.
 */
#include"nkEngine/nkstdafx.h"
#include"nkShadow.h"

namespace nkEngine
{

	//無名空間
	//ここに書かれたものはこのファイルでしか扱えないグローバルになる
	namespace 
	{
		/** The shadow area table[ c shadow map maximum shadow map][ 2]. */
		const float shadowAreaTable[CShadowMap::MAX_SHADOW_MAP][2] =
		{
			{ 20.0f, 20.0f },
			{ 45.0f, 45.0f },
			{ 120.0f, 120.0f },
		};
	}

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CShadowMap::CShadowMap() :
		isEnable_(false),
		Near_(1.0f),
		Far_(1000.0f),
		Aspect_(1.0f),
		CalcLightViewFunc_(CalcLightViewFunc_PositionTarget),
		LightTarget_(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		LightPosition_(D3DXVECTOR3(0.0f, 3.0f, 0.0f)),
		LightDirection_(D3DXVECTOR3(0.0f, -1.0f, 0.0f))
	{
		
		D3DXMatrixIdentity(&LightViewMatrix_);
		
		for (int i = 0; i < MAX_SHADOW_MAP; i++) 
		{
			ShadowAreaW_[i] = shadowAreaTable[i][0];
			ShadowAreaH_[i] = shadowAreaTable[i][1];
		}

	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CShadowMap::~CShadowMap()
	{
		Release();
	}

	/**
	 * 作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param config The configuration.
	 */
	void CShadowMap::Create(const ShadowConfigS& config)
	{
		//解放
		Release();

		Near_ = config.Near_;
		Far_ = config.Fur_;

		isEnable_ = config.isEnable_;
		
		int w = config.ShadowMapW_;
		int h = config.ShadowMapH_;

		Aspect_ = (float)w / (float)h;

		//サイズの作成
		int wh[MAX_SHADOW_MAP][2] = 
		{
			{ w	    , h		 },
			{ w >> 1, h >> 1 },
			{ w >> 1, h >> 1 },
		};

		for (int i = 0; i < MAX_SHADOW_MAP; i++)
		{
			//レンダリングターゲットの作成
			ShadowMapRT_[i].Create(wh[i][0], wh[i][1], 1, D3DFMT_G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
			
			//ブラークラスの初期化
			Blur_[i].Init(w, h, *ShadowMapRT_[i].GetTexture());
		
		}

		//バリアンスシャドウマップ
		ShadowReceiverParam_.isVSM_ = true;

		//シャドウマップの数
		ShadowReceiverParam_.numShadowMap_ = MAX_SHADOW_MAP;
	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CShadowMap::Update()
	{
		if (isEnable_)
		{
			if (CalcLightViewFunc_ == CalcLightViewFunc_PositionTarget)
			{
				//ライトの視点と注視点で計算
				LightDirection_ = LightTarget_ - LightPosition_;
				D3DXVec3Normalize(&LightDirection_, &LightDirection_);
			}

			D3DXVECTOR3 vLightUp;
			float t = fabsf(D3DXVec3Dot(&LightDirection_, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)));

			if (fabsf((t - 1.0f)) < 0.00001f)
			{
				vLightUp = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			}
			else
			{
				vLightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}
			
			//ターゲット
			D3DXVECTOR3 vLightTarget;
			//ターゲットの作成
			vLightTarget = LightPosition_ + LightDirection_;

			//ライトから見たビュー行列を作成
			D3DXMatrixLookAtLH(&LightViewMatrix_, &LightPosition_, &vLightTarget, &vLightUp);
		
			for (int i = 0; i < MAX_SHADOW_MAP; i++) 
			{
				//プロジェクション行列を作成。平行投影.
				D3DXMatrixOrthoLH(&ProjMatrix_, ShadowAreaW_[i] * Aspect_,ShadowAreaH_[i],Near_,Far_);

				//ビュープロジェクション行列の作成
				D3DXMatrixMultiply(&ShadowReceiverParam_.LightViewProjMatrix_[i], &LightViewMatrix_, &ProjMatrix_);

			}

		}

	}

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CShadowMap::Render()
	{
		if (isEnable_)
		{
			
			//デバイスの取得
			IDirect3DDevice9* Device = Engine().GetDevice();

			//バックバッファの取得
			LPDIRECT3DSURFACE9 BackBuffer;
			LPDIRECT3DSURFACE9 BackDepthBuffer;
			
			Device->GetRenderTarget(0, &BackBuffer);
			Device->GetDepthStencilSurface(&BackDepthBuffer);

			for (int i = 0; i < MAX_SHADOW_MAP; i++)
			{

				Device->SetRenderTarget(0, ShadowMapRT_[i].GetSurface());
				Device->SetDepthStencilSurface(ShadowMapRT_[i].GetDepthSurface());
				
				Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

				//ビュープロジェクション行列のコピー
				LightViewProjMatrix_ = ShadowReceiverParam_.LightViewProjMatrix_[i];
				
				Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
				
				for (auto model : ShadowModelList_)
				{
					model->RenderToShadowMap();
				}
				
				Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

				//ブラーの描画
				Blur_[i].Render();
			}

			//バックバッファに戻す
			Device->SetRenderTarget(0, BackBuffer);
			Device->SetDepthStencilSurface(BackDepthBuffer);
			BackBuffer->Release();
			BackDepthBuffer->Release();

			//モデルの削除
			ShadowModelList_.clear();
		}

	}

	/**
	 * 解放
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CShadowMap::Release()
	{
		for (int i = 0; i < MAX_SHADOW_MAP; i++)
		{
			ShadowMapRT_[i].Release();
		}
	}

	/**
	 * モデルの設定.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param [in,out] model If non-null, the model.
	 */
	void CShadowMap::Entry(ModelRender* model)
	{
		ShadowModelList_.push_back(model);
	}

}// namespace nkEngine