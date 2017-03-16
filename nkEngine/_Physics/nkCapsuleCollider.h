/**
 * @file	_Physics\nkCapsuleCollider.h
 *
 * �J�v�Z���R���C�_�[�N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * �J�v�Z���R���C�_�[.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CapsuleCollider : public ICollider
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CapsuleCollider()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CapsuleCollider()
		{
		}

		/**
		 * �J�v�Z���R���C�_�[�쐬.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	radius	The radius.
		 * @param	height	The height.
		 */
		void Create(float radius, float height);

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

		/**
		* ���.
		*/
		void Release()override
		{
			SAFE_DELETE(Shape_);
		}

	private:

		/** �J�v�Z���`��. */
		btCapsuleShape* Shape_ = nullptr;
	
	};

}// namespace nkEngine