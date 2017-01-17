/**
 * @file _Resources\nkTextureResources.cpp
 *
 * テクスチャリソースクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkTextureResources.h"

namespace nkEngine
{

	/**
	 * テクスチャの読み込み.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/17
	 *
	 * @param filename The filename to load.
	 *
	 * @return Null if it fails, else a pointer to an IDirect3DTexture9.
	 */
	IDirect3DTexture9* CTextureResources::Load(const char* filename, bool isRegistration)
	{
		//デバイスを取得
		IDirect3DDevice9* Device = Engine().GetDevice();
		
		//テクスチャ
		IDirect3DTexture9* tex;

		if (isRegistration)
		{

			//ハッシュ値の作成
			int hash = Hash::MakeHash(filename);

			//探索
			auto& it = TextureList_.find(hash);

			if (it == TextureList_.end())
			{
				//作成されていない

				//ファイルパスを作成
				char* baseDir = "Asset/Texture/";
				char fp[64];
				strcpy(fp, baseDir);
				strcat(fp, filename);

				//テクスチャの読み込み
				if (FAILED(D3DXCreateTextureFromFile(
					Device,
					fp,
					&tex)))
				{
					NK_ASSERT(false, "failed lloadtexture");
				}

				//リストに登録
				TextureList_.insert(make_pair(hash, tex));

			}
			else
			{
				//作成されている
				tex = it->second;
			}
		}
		else
		{
			//ファイルパスを作成
			char* baseDir = "Asset/Texture/";
			char fp[64];
			strcpy(fp, baseDir);
			strcat(fp, filename);

			//テクスチャの読み込み
			if (FAILED(D3DXCreateTextureFromFile(
				Device,
				fp,
				&tex)))
			{
				NK_ASSERT(false, "failed lloadtexture");
			}
		}


		return tex;
	}

}// namespace nkEngine