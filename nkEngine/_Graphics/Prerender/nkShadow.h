#pragma once

#include"../modelRender/nkSkinModel.h"
#include"..\nkCamera.h"
#include"..\nkBlur.h"

namespace nkEngine
{

	class CCamera;

	class CShadowMap
	{
	public:

		//シャドウマップの数
		static const int MAX_SHADOW_MAP = 3;

		//シャドウレシーバー用のパラメータ
		struct SShadowReceiverParam
		{
			D3DXMATRIX mLightViewProjection[MAX_SHADOW_MAP]; //ライトビューマトリクス
			bool vsmFlag; //バリアンスシャドウマップを行うかのフラグ
			int numShadowMap; //シャドウマップの枚数
		};

		//ライトビューの計算の仕方。
		enum EnCalcLightViewFunc {
			enCalcLightViewFunc_PositionDirection,	//ライトの位置と方向で計算する。
			enCalcLightViewFunc_PositionTarget,		//ライトの位置と注視点で計算する。
		};

		//作成
		//param[in] コンフィグ
		void Create(const SShadowConfig& config);

		//更新
		void Update();

		//描画
		void Render();

		//開放
		void Release();

		//モデルをエントリー
		//param[in] モデル
		void Entry(CModelRender* SkinModel);

		//テクスチャを取得
		//param[in] テクスチャーナンバー
		const CTexture* GetTexture(int texNumber) const
		{
			return m_blur[texNumber].GetTexture();
			//return m_shadowMapRT[texNumber].GetTexture();
		}

		//ライトの方向を設定
		void SetLightDirection(const D3DXVECTOR3& dir)
		{
			m_vLightDirection = dir;
		}

		//ライトの視点を設定
		void SetLightPosition(const D3DXVECTOR3& pos)
		{
			m_vLightPosition = pos;
		}

		//ライトの注視点を設定
		void SetLightTarget(const D3DXVECTOR3& ter)
		{
			m_vLightTarget = ter;
		}

		//近平面を取得
		float GetNear() const
		{
			return m_near;
		}

		//近平面を設定
		void SetNear(float fnear)
		{
			m_near = fnear;
		}

		//遠平面を取得
		float GetFar() const
		{
			return m_far;
		}

		//遠平面を設定
		void SetFar(float ffar)
		{
			m_far = ffar;
		}

		//有効フラグの取得
		bool isEnable()const
		{
			return m_isEnable;
		}

		//ライトビューの設定の仕方を設定
		void SetCalcLightViewFunc(EnCalcLightViewFunc func)
		{
			m_calcLightViewFunc = func;
		}

		//インスタンス取得
		inline static CShadowMap& GetInstance()
		{
			static CShadowMap instance;
			return instance;
		}

		//シャドウレシーバー用のパラメータを取得
		//return シャドウレシーバー用のパラメータ
		const SShadowReceiverParam& GetShadowReceiverParam()
		{
			return m_shadowReceiverParam;
		}

		//ライトビュープロジェクション行列の取得
		const D3DXMATRIX& GetLightViewProjectionMatrix() const
		{
			return m_mLightViewProjection;
		}

	private:
		//コンストラクタ
		CShadowMap();
		//デストラクタ
		~CShadowMap();
	private:
		bool m_isEnable; //有効フラグ	

		CRenderTarget m_shadowMapRT[MAX_SHADOW_MAP]; //シャドウマップ用レンダーターゲット
		vector<CModelRender*> m_shadowModels; //影を書き込むモデル

		D3DXVECTOR3 m_vLightPosition; //ライトの視点
		D3DXVECTOR3 m_vLightDirection; //ライトの方向
		D3DXVECTOR3 m_vLightTarget; //ライトの注視点

		D3DXMATRIX m_mLightView; //ライトビュー行列
		D3DXMATRIX m_mProjection; //プロジェクション行列
		D3DXMATRIX m_mLightViewProjection; //ライトビュープロジェクション行列

		EnCalcLightViewFunc	m_calcLightViewFunc; //ライトビューの計算方法。

		float m_near; //近平面
		float m_far; //遠平面
		float m_Aspect; //アスペクト比
		float m_shadowAreaW[MAX_SHADOW_MAP]; //影を落とす範囲の幅
		float m_shadowAreaH[MAX_SHADOW_MAP]; //影を落とす範囲の高さ

		CBlur m_blur[MAX_SHADOW_MAP]; //ブラー処理クラス
		SShadowReceiverParam m_shadowReceiverParam; //シャドウレシーバー用のパラメータ
	};

	inline static CShadowMap& Shadow()
	{
		return CShadowMap::GetInstance();
	}
}