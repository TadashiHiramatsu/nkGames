/**
 * @file	_Physics\nkSphereCollider.h
 *
 * ���̃R���C�_�[�N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * ���̃R���C�_�[�N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class SphereCollider : public ICollider
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		SphereCollider()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~SphereCollider()
		{
		}

		/**
		 * ���̃R���C�_�[�쐬.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	radius	���a.
		 */
		void Create(const float radius);

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

		/** ���̌`��. */
		btSphereShape* Shape_ = nullptr;
	
	};

}