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
	 * �ǂݍ���. "Asset/Texture/"���ɕۑ�����Ă���e�N�X�`����ǂݍ��߂܂�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param filePath		 "Asset/Texture/"���Ȃ����t�@�C���p�X.
	 * @param isRegistration True if this object is registration.
	 */
	void Texture::Load(const char * filePath, bool isRegistration)
	{
		isRegistration_ = isRegistration;

		D3DTexture_ = TextureResources().Load(filePath, isRegistration_);
	}

}// namespace nkEngine