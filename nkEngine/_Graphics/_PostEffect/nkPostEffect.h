/**
 * @file _Graphics\_PostEffect\nkPostEffect.h
 *
 * ポストエフェクトクラスの定義.
 */
#pragma once

#include"nkAntiAliasing.h"
#include"nkBloom.h"

namespace nkEngine
{

	/**
	 * ポストエフェクトクラス.
	 * 作成したポストエフェクトはこいつで使用する
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	class PostEffect : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		PostEffect()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		~PostEffect()
		{
		}

		/**
		 * 作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param config The configuration.
		 */
		void Create(const GraphicsConfigS& config);

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void Render();

		/**
		 * フルスクリーン描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void RenderFullScreen();

	private:

		/** フルスクリーン描画用プリミティブ. */
		Primitive Primitive_;

		/** ブルーム. */
		Bloom Bloom_;
		/** アンチエイリアス. */
		AntiAliasing AntiAliasing_;

	};
}