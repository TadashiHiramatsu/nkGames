/**
 * @file _Graphics\_PostEffect\nkBloom.h
 *
 * ブルームクラスの定義.
 */
#pragma once

#include"..\nkBlur.h"

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
		Bloom();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Bloom();

		/**
		 * 作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param isEnable True if this object is enable.
		 */
		void Create(bool isEnable);
		
		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

	private:

		/**
		 * Updates the weight described by parameter1.
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
		/** The primitive. */
		Primitive Primitive_;
		/** The blur [ 2]. */
		Blur Blur_[2];

	};

}// namespace nkEngine