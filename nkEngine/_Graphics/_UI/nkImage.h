/**
 * @file _Graphics\_UI\nkImage.h
 *
 * イメージクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * イメージクラス.
	 * 2Dの画像をスクリーンに描画します.
	 * 使用するためにはRectTransformクラスのポインタを設定する必要あり.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Image : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Image()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Image()
		{
		}

		/**
		 * ファイルのロードを行う.
		 * エフェクトとテクスチャ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param filepass "Asset/Texture/"を省いたファイルパス.
		 */
		void Load(const char* filepass);

		/**
		 * ファイルのロードを行う　 
		 * エフェクトのみ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Load();

		/**
		 * 初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Init();

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * テクスチャを設定する.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] tex テクスチャ.
		 */
		void SetTexture(shared_ptr<Texture>& tex)
		{
			Texture_ = tex;
		}

		/**
		 * トランスフォームを設定する.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] rt If non-null, the right.
		 */
		void SetTransform(RectTransform* rt)
		{
			RectTransform_ = rt;
		}

		/**
		* モノクロ設定.
		*
		* @param flag	モノクロフラグ.
		*/
		void SetMonochrome(bool flag)
		{
			isMonochrome_ = flag;
		}

	private:

		/** エフェクト. */
		Effect* Effect_ = nullptr;
		/** プリミティブ. */
		Primitive Primitive_;
		/** テクスチャ. */
		shared_ptr<Texture> Texture_;
		/** レクトトランスフォーム. */
		RectTransform* RectTransform_ = nullptr;

		/** モノクロフラグ. */
		bool isMonochrome_ = false;

	public:

		/** UV座標 x:左, y:上, z:右 ,w:下 . */
		Vector4 RectUV_ = Vector4(0, 0, 1, 1);
		/** 色. */
		Vector4 Color_ = Vector4(1, 1, 1, 1);

		/** 初期化されているかフラグ. */
		bool isInit = false;
	

	};

}// namespace nkEngine