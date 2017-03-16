/**
 * @file	_Physics\nkRigidBody.cpp
 *
 * 剛体クラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkRigidBody.h"
#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * 作成.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param [in,out]	rbInfo	Information describing the rb.
	 */
	void RigidBody::Create(RigidBodyInfoS& rbInfo)
	{
		//解放
		Release();

		//トランスフォーム作成
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(rbInfo.Position_.x, rbInfo.Position_.y, rbInfo.Position_.z));
		transform.setRotation(btQuaternion(rbInfo.Rotation_.x, rbInfo.Rotation_.y, rbInfo.Rotation_.z, rbInfo.Rotation_.w));
		MotionState_ = new btDefaultMotionState;
		btRigidBody::btRigidBodyConstructionInfo btrbInfo(rbInfo.Mass_, MotionState_, rbInfo.Collider_->GetBody(), btVector3(0, 0, 0));

		//剛体を作成。
		RigidBody_ = new btRigidBody(btrbInfo);
	}

	/**
	* 解放.
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