/**
 * @file _Graphics\_UI\nkImage.h
 *
 * �C���[�W�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �C���[�W�N���X.
	 * 2D�̉摜���X�N���[���ɕ`�悵�܂�.
	 * �g�p���邽�߂ɂ�RectTransform�N���X�̃|�C���^��ݒ肷��K�v����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Image
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Image();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Image()
		{
		}

		/**
		 * �t�@�C���̃��[�h���s��.
		 * �G�t�F�N�g�ƃe�N�X�`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param _filepass "Asset/Texture/"���Ȃ����t�@�C���p�X.
		 */
		void Load(const char* _filepass);

		/**
		 * �t�@�C���̃��[�h���s��.
		 * �G�t�F�N�g�̂�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] _tex The tex to load.
		 */
		void Load(shared_ptr<Texture>& _tex);

		/**
		 * �t�@�C���̃��[�h���s���@ 
		 * �G�t�F�N�g�̂�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Load();

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Init();

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * �e�N�X�`����ݒ肷��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] tex �e�N�X�`��.
		 */
		void SetTexture(shared_ptr<Texture>& tex)
		{
			Texture_ = tex;
		}

		/**
		 * �g�����X�t�H�[����ݒ肷��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] rt If non-null, the right.
		 */
		void SetTransform(RectTransform* rt)
		{
			RectTransform_ = rt;
		}

	private:

		/** �G�t�F�N�g. */
		Effect* Effect_;
		/** �v���~�e�B�u. */
		Primitive Primitive_;
		/** �e�N�X�`��. */
		shared_ptr<Texture> Texture_;
		/** ���N�g�g�����X�t�H�[��. */
		RectTransform* RectTransform_;

	public:

		/** UV���W x:��, y:��, z:�E ,w:�� . */
		D3DXVECTOR4 RectUV_;
		/** �F. */
		D3DXVECTOR4 Color_;

		bool isInit = false;

	};

}// namespace nkEngine