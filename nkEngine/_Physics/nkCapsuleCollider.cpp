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
	* �J�v�Z���R���C�_�[�쐬.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*
	* @param	radius	The radius.
	* @param	height	The height.
	*/
	void CapsuleCollider::Create(float radius, float height)
	{
		Shape_ = new btCapsuleShape(radius, height);
	}

}// namespace nkEngine