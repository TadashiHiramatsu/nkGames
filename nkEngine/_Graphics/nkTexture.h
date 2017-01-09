/**
 * @file _Graphics\nkTexture.h
 *
 * テクスチャクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * テクスチャクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Texture
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Texture();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Texture();

		/**
		 * テクスチャを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] tex If non-null, the tex.
		 */
		void SetTextureDX(IDirect3DTexture9* tex)
		{
			D3DTexture_ = tex;
		}

		/**
		 * テクスチャを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the texture dx.
		 */
		IDirect3DTexture9* GetTexture() const
		{
			return D3DTexture_;
		}

		/**
		 * 読み込み.
		 * "Asset/Texture/"内に保存されているテクスチャを読み込めます.
		 * 
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param filePath "Asset/Texture/"を省いたファイルパス.
		 */
		void Load(const char* filePath);

	private:

		/** テクスチャ. */
		IDirect3DTexture9* D3DTexture_;

	};

}// namespace nkEngine