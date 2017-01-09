/**
 * @file	_Physics\nkBoxCollider.cpp
 *
 * �{�b�N�X�R���C�_�[�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkBoxCollider.h"

namespace nkEngine
{

	/**
	* �R���X�g���N�^.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*/
	BoxCollider::BoxCollider() :
		Shape_(nullptr)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	BoxCollider::~BoxCollider()
	{
		SAFE_DELETE(Shape_);
	}

	/**
	 * �{�b�N�X�`��̍쐬.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param	size	�T�C�Y.
	 */
	void BoxCollider::Create(const D3DXVECTOR3 & size)
	{
		Shape_ = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
	}

}// namespace nkEngine