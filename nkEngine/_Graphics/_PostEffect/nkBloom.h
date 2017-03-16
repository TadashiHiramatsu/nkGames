/**
 * @file _Graphics\_PostEffect\nkBloom.h
 *
 * ブルームクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ブルームクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Bloom : Noncopyable
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

		/** 有効フラグ. */
		bool isEnable_;

		/** 重み. */
		static const int NUM_WEIGHTS = 8;
		/** 重み [num weights]. */
		float Weights_[NUM_WEIGHTS];

		/** エフェクト. */
		Effect* Effect_;
		
		/** レンダリングターゲット. */
		RenderTarget LuminanceRT_;
	
		/** ぼかし合成用のRT. */
		RenderTarget CombineRT_;

		/** ダウンサンプリング用RTの数. */
		static const int NUM_DOWN_SAMPLING_RT = 10;
		/** 輝度をダウンサンプリングするためのRT. */
		RenderTarget DownSamplingRT_[NUM_DOWN_SAMPLING_RT];

	};

}// namespace nkEngine