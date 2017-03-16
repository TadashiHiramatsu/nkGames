/**
 * @file _Graphics\nkTexture.cpp
 *
 * テクスチャクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkTexture.h"

namespace nkEngine
{

	/**
	 * 読み込み. "Asset/Texture/"内に保存されているテクスチャを読み込めます.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param filePath		 "Asset/Texture/"を省いたファイルパス.
	 * @param isRegistration True if this object is registration.
	 */
	void Texture::Load(const char * filePath, bool isRegistration)
	{
		isRegistration_ = isRegistration;

		D3DTexture_ = TextureResources().Load(filePath, isRegistration_);
	}

}// namespace nkEngine