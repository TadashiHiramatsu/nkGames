/**
 * @file	_Graphics\_2DObject\nkSprite.h
 *
 * �X�v���C�g�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �X�v���C�g�N���X.
	 * 3D��Ԃɔ|����\��
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	class Sprite : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		Sprite()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		~Sprite()
		{
		}

		/**
		 * �ǂݍ���.
		 * 
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param	filePath	The file path to load.
		 */
		void Load(const char* filePath);

		/**
		 * ������.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Start();

		/**
		 * �`��.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Render();

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/11
		 */
		void Release();

		/**
		 * �g�����X�t�H�[���̐ݒ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param [in,out]	transform	If non-null, the transform.
		 */
		void SetTransform(const Transform* transform)
		{
			Transform_ = transform;
		}

		/**
		 * �J�����̃|�C���^��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/12
		 *
		 * @param [in,out] camera If non-null, the camera.
		 */
		void SetCamera(const Camera* camera)
		{
			Camera_ = camera;
		}

	private:

		/** �v���~�e�B�u. */
		Primitive Primitive_;
		/** �G�t�F�N�g. */
		Effect* Effect_ = nullptr;
		/** �g�����X�t�H�[��. */
		const Transform* Transform_ = nullptr;
		/** �e�N�X�`��. */
		Texture Texture_;
		/** �J�����̃|�C���^. */
		const Camera* Camera_ = nullptr;

	public:

		/** UV���W x:��, y:��, z:�E, w:��. */
		Vector4 RectUV_ = Vector4(0, 0, 1, 1);
		/** �F. */
		Vector4 Color_ = Vector4(1, 1, 1, 1);

	};

}// namespace nkEngine