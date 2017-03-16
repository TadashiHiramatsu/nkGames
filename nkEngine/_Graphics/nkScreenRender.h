/**
 * @file _Graphics\nkScreenRender.h
 *
 * シーンをレンダリングするクラスを定義.
 */
#pragma once

#include"_PostEffect\nkPostEffect.h"

namespace nkEngine
{

	/**
	 * シーンレンダークラス.
	 * シングルトンクラス
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CScreenRender : Noncopyable
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CScreenRender()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CScreenRender()
		{
		}

	public:

		/**
		 * インスタンスの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The instance.
		 */
		inline static CScreenRender& GetInstance()
		{
			static CScreenRender instance;
			return instance;
		}

		/**
		 * 初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Start();

		/**
		 * グラフィック関連の初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param config The configuration.
		 */
		void StartGraphic(const GraphicsConfigS& config);

		/**
		* 更新.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/09
		*/
		void Loop();

		/**
		 * メインレンダーターゲットを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param num Number of.
		 *
		 * @return The main render target.
		 */
		RenderTarget& GetMainRenderTarget()
		{
			return MainRT_[CurrentMainRT_];
		}

		/**
		 * メインレンダリングターゲットを切り替え.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void ToggleMainRenderTarget()
		{
			CurrentMainRT_ ^= 1;
		}

	private:

		/**
		 * バックバッファにレンダリング.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void BackBufferRender();

	private:

		/** デバイス. */
		IDirect3DDevice9* Device_ = nullptr;

		/** バックバッファのレンダーターゲット. */
		RenderTarget BackBufferRT_;

		/** 現在使用されているメインレンダーターゲット. */
		unsigned char CurrentMainRT_ = 0;
		/** メインのレンダーターゲット. */
		RenderTarget MainRT_[2];

		/** The post effect. */
		PostEffect PostEffect_;

		/** プリミティブ. */
		Primitive Primitive_;
		/** エフェクト. */
		Effect* Effect_ = nullptr;

	};

	/**
	 * スクリーンレンダークラスの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CScreenRender.
	 */
	inline static CScreenRender& ScreenRender()
	{
		return CScreenRender::GetInstance();
	}
	 
}// namespace nkEngine