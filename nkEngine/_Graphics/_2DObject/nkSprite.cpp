/**
 * @file	_Graphics\_2DObject\nkSprite.cpp
 *
 * スプライトクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSprite.h"

namespace nkEngine
{

	/**
	 * 読み込み.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 *
	 * @param	filePath	The file path to load.
	 */
	void Sprite::Load(const char * filePath)
	{
		//テクスチャのロード
		Texture_.Load(filePath);

		//エフェクトのロード
		Effect_ = EffectManager().LoadEffect("Sprite.fx");
	}

	/**
	 * 初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	void Sprite::Start()
	{
		//プリミティブの初期化

		//頂点バッファの作成 
		static SShapeVertex_PT vb[] =
		{
			{
				-1.0f, 1.0f, 0.0f, 1.0f,
				0.0f, 0.0f
			},
			{
				1.0f, 1.0f, 0.0f, 1.0f,
				1.0f, 0.0f
			},
			{
				-1.0f, -1.0f, 0.0f, 1.0f,
				0.0f, 1.0f
			},
			{
				1.0f, -1.0f, 0.0f, 1.0f,
				1.0f, 1.0f
			},
		};
		//インデックスバッファの作成
		short ib[] =
		{
			0,1,2,3
		};
		//プリミティブの作成
		Primitive_.Create(
			Primitive::TypeE::TriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			IndexFormatE::IndexFormat16,
			ib
		);

	}

	/**
	 * 描画.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	void Sprite::Render()
	{

		//ワールドビュープロジェクション行列の計算
		Matrix mWVP = Matrix::Identity;
		mWVP.Mul(Transform_->WorldMatrix_, Camera_->GetViewMatrix());
		mWVP.Mul(mWVP, Camera_->GetProjectionMatrix());

		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		//アルファブレンディングを行う
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// 透過処理を行う
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		// 半透明処理を行う
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

		//テクニックを設定.
		Effect_->SetTechnique("Sprite");

		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);

		//ワールドビュープロジェクション行列を設定.
		Effect_->SetMatrix("g_mWVP", &mWVP);

		//テクスチャを設定.
		Effect_->SetTexture("g_Texture", &Texture_);

		//UVを設定.
		Effect_->SetValue("g_RectUV", &RectUV_, sizeof(RectUV_));

		//色を設定.
		Effect_->SetValue("g_Color", &Color_, sizeof(Color_));
		
		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();

		//元に戻れ
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Sprite::Release()
	{
		Texture_.Release();
	}

}// namespace nkEngine