/**
 * @file _Graphics\_PreRender\nkShadow.h
 *
 * シャドウマップクラス.
 */
#pragma once

#include"..\nkCamera.h"
#include"..\nkBlur.h"

namespace nkEngine
{

	class CModelRender;

	/**
	 * シャドウマップクラス.
	 * シングルトンクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CShadowMap
	{
	public:

		/** シャドウマップの数. */
		static const int MAX_SHADOW_MAP = 3;

		/**
		* シャドウレシーバー用のパラメータ.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/09
		*/
		struct ShadowReceiverParamS
		{
		public:

			/** ライトビュープロジェクション行列. */
			D3DXMATRIX LightViewProjMatrix_[MAX_SHADOW_MAP];
			/** バリアンスシャドウマップを行うかのフラグ. */
			bool isVSM_;
			/** シャドウマップの枚数. */
			int numShadowMap_;

		};

		/** ライトビューの計算の仕方. */
		enum CalcLightViewFuncE {
			CalcLightViewFunc_PositionDirection,	//!< ライトの位置と方向で計算する。
			CalcLightViewFunc_PositionTarget,		//!< ライトの位置と注視点で計算する。
		};

	private:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CShadowMap();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CShadowMap();

	public:

		/**
		* インスタンスの取得.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/09
		*
		* @return The instance.
		*/
		inline static CShadowMap& GetInstance()
		{
			static CShadowMap instance;
			return instance;
		}

		/**
		 * 作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param config コンフィグ.
		 */
		void Create(const ShadowConfigS& config);

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * 開放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * モデルをエントリー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] skinModel モデル.
		 */
		void Entry(CModelRender* skinModel);

		/**
		 * テクスチャを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param texNumber テクスチャナンバ.
		 *
		 * @return Null if it fails, else the texture.
		 */
		const Texture* GetTexture(int texNumber) const
		{
			return Blur_[texNumber].GetTexture();
			//return m_shadowMapRT[texNumber].GetTexture();
		}

		/**
		 * ライトの方向を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param dir The dir.
		 */
		void SetLightDirection(const D3DXVECTOR3& dir)
		{
			LightDirection_ = dir;
		}

		/**
		 * ライトの視点を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param pos The position.
		 */
		void SetLightPosition(const D3DXVECTOR3& pos)
		{
			LightPosition_ = pos;
		}

		/**
		 * ライトの注視点を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param target The target.
		 */
		void SetLightTarget(const D3DXVECTOR3& target)
		{
			LightTarget_ = target;
		}

		/**
		 * 近平面を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The near.
		 */
		float GetNear() const
		{
			return Near_;
		}

		/**
		 * 近平面を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param idx The near.
		 */
		void SetNear(float idx)
		{
			Near_ = idx;
		}

		/**
		 * 遠平面を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The far.
		 */
		float GetFar() const
		{
			return Far_;
		}

		/**
		 * 遠平面を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param idx The far.
		 */
		void SetFar(float idx)
		{
			Far_ = idx;
		}

		/**
		 * 有効フラグの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return True if enable, false if not.
		 */
		bool isEnable()const
		{
			return isEnable_;
		}

		/**
		 * ライトビューの設定の仕方を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param func The function.
		 */
		void SetCalcLightViewFunc(CalcLightViewFuncE func)
		{
			CalcLightViewFunc_ = func;
		}

		/**
		 * シャドウレシーバー用のパラメータを取得 return シャドウレシーバー用のパラメータ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The shadow receiver parameter.
		 */
		const ShadowReceiverParamS& GetShadowReceiverParam()
		{
			return ShadowReceiverParam_;
		}

		/**
		 * ライトビュープロジェクション行列の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The light view projection matrix.
		 */
		const D3DXMATRIX& GetLightViewProjectionMatrix() const
		{
			return LightViewProjMatrix_;
		}

	private:

		/** 有効フラグ. */
		bool isEnable_;
		/** シャドウマップ用レンダーターゲット. */
		RenderTarget ShadowMapRT_[MAX_SHADOW_MAP];
		/** 影を書き込むモデル. */
		vector<CModelRender*> ShadowModels_;

		/** ライトの視点. */
		D3DXVECTOR3 LightPosition_;
		/** ライトの方向. */
		D3DXVECTOR3 LightDirection_;
		/** ライトの注視点. */
		D3DXVECTOR3 LightTarget_;

		/** ライトビュー行列. */
		D3DXMATRIX LightViewMatrix_;
		/** プロジェクション行列. */
		D3DXMATRIX ProjMatrix_;
		/** ライトビュープロジェクション行列. */
		D3DXMATRIX LightViewProjMatrix_;

		/** ライトビューの計算方法. */
		CalcLightViewFuncE	CalcLightViewFunc_;

		/** 近平面. */
		float Near_;
		/** 遠平面. */
		float Far_;
		/** アスペクト比. */
		float Aspect_;
		/** 影を落とす範囲の幅. */
		float ShadowAreaW_[MAX_SHADOW_MAP];
		/** 影を落とす範囲の高さ. */
		float ShadowAreaH_[MAX_SHADOW_MAP];

		/** ブラー処理クラス. */
		Blur Blur_[MAX_SHADOW_MAP];
		/** シャドウレシーバー用のパラメータ. */
		ShadowReceiverParamS ShadowReceiverParam_;

	};

	/**
	 * シャドウマップクラスの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CShadowMap.
	 */
	inline static CShadowMap& Shadow()
	{
		return CShadowMap::GetInstance();
	}

}// namespace nkEngine