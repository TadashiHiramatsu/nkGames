/**
 * @file _Graphics\nkBlur.h
 *
 * ブラークラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ブラークラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Blur
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Blur();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Blur();

		/**
		 * 初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param w			 横幅.
		 * @param h			 縦幅.
		 * @param srcTexture 元となるテクスチャ.
		 */
		void Init(int w,int h,const Texture& srcTexture);

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * テクスチャを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the texture.
		 */
		const Texture* GetTexture()const
		{
			return BlurRT_[1].GetTexture();
		}

		/**
		 * テクスチャの横幅.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The size w.
		 */
		int GetSizeW()
		{
			return SrcTexWH_[0];
		}

		/**
		 * テクスチャの高さ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The size h.
		 */
		int GetSizeH()
		{
			return SrcTexWH_[1];
		}

	private:

		/** ガウシアンブラーの結果を描きこむレンダリングターゲット. */
		RenderTarget BlurRT_[2];
		/** ソースとなるテクスチャ. */
		const Texture*	SrcTexture_;
		/** エフェクト. */
		ID3DXEffect* Effect_;
		/** テクスチャの幅. */
		int SrcTexWH_[2];
		/** プリミティブ. */
		Primitive Primitive_;

	};

}// namespace nkEngine