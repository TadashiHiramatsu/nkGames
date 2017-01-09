/**
 * @file _Graphics\nkScreenRender.h
 *
 * シーンをレンダリングするクラスを定義.
 */
#pragma once

#include"_PostEffect\nkAntiAliasing.h"
#include"_PostEffect\nkBloom.h"

namespace nkEngine
{

	/**
	 * シーンレンダークラス.
	 * シングルトンクラス
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CScreenRender
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CScreenRender();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CScreenRender();

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
		 *
		 * @param initParam The init parameter.
		 */
		void Start(const InitParamS& initParam);

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
		 * @date 2017/01/09
		 *
		 * @return The main render target.
		 */
		CRenderTarget& GetMainRenderTarget()
		{
			return MainRT_;
		}

	private:

		/** バックバッファのレンダーターゲット. */
		CRenderTarget BackBufferRT_;
		/** メインのレンダーターゲット. */
		CRenderTarget MainRT_;
		/** アンチエイリアシング. */
		CAntiAliasing AntiAliasing_;
		/** ブルーム. */
		CBloom Bloom_;
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