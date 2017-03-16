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
	class Image : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Image()
		{
		}

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
		 * @param filepass "Asset/Texture/"���Ȃ����t�@�C���p�X.
		 */
		void Load(const char* filepass);

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

		/**
		* ���m�N���ݒ�.
		*
		* @param flag	���m�N���t���O.
		*/
		void SetMonochrome(bool flag)
		{
			isMonochrome_ = flag;
		}

	private:

		/** �G�t�F�N�g. */
		Effect* Effect_ = nullptr;
		/** �v���~�e�B�u. */
		Primitive Primitive_;
		/** �e�N�X�`��. */
		shared_ptr<Texture> Texture_;
		/** ���N�g�g�����X�t�H�[��. */
		RectTransform* RectTransform_ = nullptr;

		/** ���m�N���t���O. */
		bool isMonochrome_ = false;

	public:

		/** UV���W x:��, y:��, z:�E ,w:�� . */
		Vector4 RectUV_ = Vector4(0, 0, 1, 1);
		/** �F. */
		Vector4 Color_ = Vector4(1, 1, 1, 1);

		/** ����������Ă��邩�t���O. */
		bool isInit = false;
	

	};

}// namespace nkEngine