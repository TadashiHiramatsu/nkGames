/**
 * @file	_Physics\nkSphereCollider.cpp
 *
 * ���̃R���C�_�[�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSphereCollider.h"

namespace nkEngine
{

	/**
	 * ���̃R���C�_�[�̍쐬.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param	radius	The ���a.
	 */
	void SphereCollider::Create(const float radius)
	{
		Shape_ = new btSphereShape(radius);
	}

}// namespace nkEngine