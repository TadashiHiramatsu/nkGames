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
	class Sprite
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		Sprite();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		~Sprite();

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
		 * �X�V.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Update();

		/**
		 * �`��.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Render();

		/**
		 * �J�����ݒ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param [in,out]	camera	If non-null, the camera.
		 */
		void SetCamera(Camera* camera)
		{
			Camera_ = camera;
		}

		/**
		 * �g�����X�t�H�[���̐ݒ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param [in,out]	transform	If non-null, the transform.
		 */
		void SetTransform(Transform* transform)
		{
			Transform_ = transform;
		}

	private:

		/** �v���~�e�B�u. */
		Primitive Primitive_;
		/** �G�t�F�N�g. */
		ID3DXEffect* Effect_;
		/** �J����. */
		Camera* Camera_;
		/** �g�����X�t�H�[��. */
		Transform* Transform_;
		/** �e�N�X�`��. */
		Texture Texture_;
		/** �r���{�[�h�t���O. */
		bool isBillboard_ = false;

	};

}// namespace nkEngine