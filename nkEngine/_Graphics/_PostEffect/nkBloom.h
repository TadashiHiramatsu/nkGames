/**
 * @file _Graphics\_PostEffect\nkBloom.h
 *
 * ブルームクラスの定義.
 */
#pragma once

#include"nkBlur.h"

namespace nkEngine
{

	/**
	 * ブルームクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Bloom
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Bloom()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Bloom()
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
		void Create(const BloomConfigS& config);

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param [in,out] postEffect If non-null, the post effect.
		 */
		void Render(PostEffect* postEffect);

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

	private:

		/**
		 * 重みを計算.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param dis The dis.
		 */
		void UpdateWeight(float dis);

	private:

		/** Number of weights. */
		static const int NUM_WEIGHTS = 8;
		/** エフェクト. */
		ID3DXEffect* Effect_;
		/** レンダリングターゲット. */
		RenderTarget LuminanceRT_;
		/** 有効フラグ. */
		bool isEnable_;
		/** The weights [num weights]. */
		float Weights_[NUM_WEIGHTS];
		/** The blur [ 2]. */
		Blur Blur_[2];

	};

}// namespace nkEngine