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
		void SetTransform(Transform* transform)
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
		void SetCamera(Camera* camera)
		{
			Camera_ = camera;
		}

	private:

		/** �v���~�e�B�u. */
		Primitive Primitive_;
		/** �G�t�F�N�g. */
		ID3DXEffect* Effect_;
		/** �g�����X�t�H�[��. */
		Transform* Transform_ = nullptr;
		/** �e�N�X�`��. */
		Texture Texture_;
		/** �J�����̃|�C���^. */
		Camera* Camera_;

	public:

		/** UV���W x:��, y:��, z:�E, w:��. */
		D3DXVECTOR4 RectUV_;
		/** �F. */
		D3DXVECTOR4 Color_;

	};

}// namespace nkEngine