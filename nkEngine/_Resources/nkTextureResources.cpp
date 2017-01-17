/**
 * @file _Resources\nkTextureResources.cpp
 *
 * �e�N�X�`�����\�[�X�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkTextureResources.h"

namespace nkEngine
{

	/**
	 * �e�N�X�`���̓ǂݍ���.
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
		//�f�o�C�X���擾
		IDirect3DDevice9* Device = Engine().GetDevice();
		
		//�e�N�X�`��
		IDirect3DTexture9* tex;

		if (isRegistration)
		{

			//�n�b�V���l�̍쐬
			int hash = Hash::MakeHash(filename);

			//�T��
			auto& it = TextureList_.find(hash);

			if (it == TextureList_.end())
			{
				//�쐬����Ă��Ȃ�

				//�t�@�C���p�X���쐬
				char* baseDir = "Asset/Texture/";
				char fp[64];
				strcpy(fp, baseDir);
				strcat(fp, filename);

				//�e�N�X�`���̓ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(
					Device,
					fp,
					&tex)))
				{
					NK_ASSERT(false, "failed lloadtexture");
				}

				//���X�g�ɓo�^
				TextureList_.insert(make_pair(hash, tex));

			}
			else
			{
				//�쐬����Ă���
				tex = it->second;
			}
		}
		else
		{
			//�t�@�C���p�X���쐬
			char* baseDir = "Asset/Texture/";
			char fp[64];
			strcpy(fp, baseDir);
			strcat(fp, filename);

			//�e�N�X�`���̓ǂݍ���
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