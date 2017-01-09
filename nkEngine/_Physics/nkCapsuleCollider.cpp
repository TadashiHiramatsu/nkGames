/**
 * @file	_Physics\nkCapsuleCollider.cpp
 *
 * �J�v�Z���R���C�_�[�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkCapsuleCollider.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	CapsuleCollider::CapsuleCollider():
		Shape_(nullptr)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	CapsuleCollider::~CapsuleCollider()
	{
		delete Shape_;
	}
	
}// namespace nkEngine