/**
 * @file	_Physics\nkBoxCollider.h
 *
 * �{�b�N�X�R���C�_�[�N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * �{�b�N�X�R���C�_�[�N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class BoxCollider : public ICollider
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		BoxCollider()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~BoxCollider()
		{
		}

		/**
		 * �{�b�N�X�R���C�_�[�쐬.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	size	�T�C�Y.
		 */
		void Create(const D3DXVECTOR3& size);

		/**
		 * �{�f�B�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		btCollisionShape* GetBody()override
		{
			return Shape_;
		}

		void Release()override
		{
			SAFE_DELETE(Shape_);
		}

	private:

		/** �{�b�N�X�`��. */
		btBoxShape* Shape_;
	
	};

}// namespace nkEngine