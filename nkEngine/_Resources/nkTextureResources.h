/**
 * @file _Resources\nkTextureResources.h
 *
 * �e�N�X�`�����\�[�X�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �e�N�X�`�����\�[�X�N���X.
	 * �V���O���g���N���X.
	 * �悭�g�p����e�N�X�`����ۑ����Ă���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/17
	 */
	class CTextureResources
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/17
		 */
		CTextureResources()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/17
		 */
		~CTextureResources()
		{
		}
	
	public:

		/**
		 * �C���X�^���X�̎擾.
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
		 * �e�N�X�`���̓ǂݍ���.
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

		/** �e�N�X�`���̃��X�g(map). */
		map<int, IDirect3DTexture9*> TextureList_;

	};

	/**
	 * �e�N�X�`�����\�[�X�N���X�̎擾.
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