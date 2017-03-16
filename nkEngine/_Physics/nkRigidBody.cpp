/**
 * @file	_Physics\nkRigidBody.cpp
 *
 * ���̃N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkRigidBody.h"
#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * �쐬.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param [in,out]	rbInfo	Information describing the rb.
	 */
	void RigidBody::Create(RigidBodyInfoS& rbInfo)
	{
		//���
		Release();

		//�g�����X�t�H�[���쐬
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(rbInfo.Position_.x, rbInfo.Position_.y, rbInfo.Position_.z));
		transform.setRotation(btQuaternion(rbInfo.Rotation_.x, rbInfo.Rotation_.y, rbInfo.Rotation_.z, rbInfo.Rotation_.w));
		MotionState_ = new btDefaultMotionState;
		btRigidBody::btRigidBodyConstructionInfo btrbInfo(rbInfo.Mass_, MotionState_, rbInfo.Collider_->GetBody(), btVector3(0, 0, 0));

		//���̂��쐬�B
		RigidBody_ = new btRigidBody(btrbInfo);
	}

	/**
	* ���.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*/
	void RigidBody::Release()
	{
		SAFE_DELETE(RigidBody_);
		SAFE_DELETE(MotionState_);
	}

}// namespace nkEngine