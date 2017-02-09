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
	class Image
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Image();

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
		 * @param _filepass "Asset/Texture/"を省いたファイルパス.
		 */
		void Load(const char* _filepass);

		/**
		 * ファイルのロードを行う.
		 * エフェクトのみ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] _tex The tex to load.
		 */
		void Load(shared_ptr<Texture>& _tex);

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

	private:

		/** エフェクト. */
		Effect* Effect_;
		/** プリミティブ. */
		Primitive Primitive_;
		/** テクスチャ. */
		shared_ptr<Texture> Texture_;
		/** レクトトランスフォーム. */
		RectTransform* RectTransform_;

	public:

		/** UV座標 x:左, y:上, z:右 ,w:下 . */
		D3DXVECTOR4 RectUV_;
		/** 色. */
		D3DXVECTOR4 Color_;

		bool isInit = false;

	};

}// namespace nkEngine