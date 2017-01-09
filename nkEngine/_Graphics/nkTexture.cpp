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
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Texture::Texture() :
		D3DTexture_(nullptr)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Texture::~Texture()
	{
		SAFE_RELEASE(D3DTexture_);
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
	void Texture::Load(const char * filePath)
	{
		//デバイスを取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		//ファイルパスを作成
		char* baseDir = "Asset/Texture/";
		char fp[64];
		strcpy(fp, baseDir);
		strcat(fp, filePath);

		//テクスチャの読み込み
		if(FAILED(D3DXCreateTextureFromFile(
			Device,
			fp,
			&D3DTexture_)))
		{
			NK_ASSERT(false, "failed lloadtexture");
		}
	}

}// namespace nkEngine