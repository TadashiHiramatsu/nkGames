/**
 * @file	_Physics\nkCollisionAttr.h
 *
 * �R���W�����̑������`.
 */
#pragma once

namespace nkEngine
{

	/** �R���W�����̑���. */
	enum ECollisionAttr
	{
		CollisionAttr_Ground,		//!< �n��
		CollisionAttr_Character,	//!< �L�����N�^�[
		CollisionAttr_User,			//!< ���[�U�[��`
	};

}// namespace nkEngine