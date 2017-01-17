/**
 * @file _Graphics\nkTexture.h
 *
 * �e�N�X�`���N���X�̒�`.
 */
#pragma once

#include"../_Resources/nkTextureResources.h"

namespace nkEngine
{

	/**
	 * �e�N�X�`���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Texture
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Texture();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Texture();

		/**
		 * �e�N�X�`����ݒ�.
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
		 * �e�N�X�`�����擾.
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
		 * �ǂݍ���. "Asset/Texture/"���ɕۑ�����Ă���e�N�X�`����ǂݍ��߂܂�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param filePath		 "Asset/Texture/"���Ȃ����t�@�C���p�X.
		 * @param isRegistration (Optional) True if this object is registration.
		 */
		void Load(const char* filePath, bool isRegistration = false);

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/11
		 */
		void Release()
		{
			if (!isRegistration_)
			{
				//���\�[�X�ɓo�^���Ă��Ȃ��̂ł����ŉ��.
				SAFE_RELEASE(D3DTexture_);
			}
		}

	private:

		/** �e�N�X�`��. */
		IDirect3DTexture9* D3DTexture_;
		/** �e�N�X�`�����\�[�X�ɓo�^����Ă��邩�t���O. */
		bool isRegistration_ = false;

	};

}// namespace nkEngine