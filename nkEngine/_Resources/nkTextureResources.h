/**
 * @file _Resources\nkTextureResources.h
 *
 * テクスチャリソースクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * テクスチャリソースクラス.
	 * シングルトンクラス.
	 * よく使用するテクスチャを保存しておく.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/17
	 */
	class CTextureResources
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/17
		 */
		CTextureResources()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/17
		 */
		~CTextureResources()
		{
		}
	
	public:

		/**
		 * インスタンスの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/17
		 *
		 * @return The instance.
		 */
		static CTextureResources& GetInstance()
		{
			static CTextureResources instance;
			return instance;
		}

		/**
		 * テクスチャの読み込み.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/17
		 *
		 * @param filename		 The filename to load.
		 * @param isRegistration (Optional) True if this object is registration.
		 *
		 * @return Null if it fails, else a pointer to an IDirect3DTexture9.
		 */
		IDirect3DTexture9* Load(const char* filename, bool isRegistration = false);
		 
	private:

		/** テクスチャのリスト(map). */
		map<int, IDirect3DTexture9*> TextureList_;

	};

	/**
	 * テクスチャリソースクラスの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/17
	 *
	 * @return A reference to the CTextureResources.
	 */
	static CTextureResources& TextureResources()
	{
		return CTextureResources::GetInstance();
	}

}