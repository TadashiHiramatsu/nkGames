/**
 * @file _Graphics\nkTexture.cpp
 *
 * �e�N�X�`���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkTexture.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Texture::Texture() :
		D3DTexture_(nullptr)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Texture::~Texture()
	{
		SAFE_RELEASE(D3DTexture_);
	}

	/**
	* �ǂݍ���.
	* "Asset/Texture/"���ɕۑ�����Ă���e�N�X�`����ǂݍ��߂܂�.
	*
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param filePath "Asset/Texture/"���Ȃ����t�@�C���p�X.
	*/
	void Texture::Load(const char * filePath)
	{
		//�f�o�C�X���擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		//�t�@�C���p�X���쐬
		char* baseDir = "Asset/Texture/";
		char fp[64];
		strcpy(fp, baseDir);
		strcat(fp, filePath);

		//�e�N�X�`���̓ǂݍ���
		if(FAILED(D3DXCreateTextureFromFile(
			Device,
			fp,
			&D3DTexture_)))
		{
			NK_ASSERT(false, "failed lloadtexture");
		}
	}

}// namespace nkEngine