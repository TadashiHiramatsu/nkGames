/**
 * @file	_Physics\nkRigidBody.h
 *
 * 剛体クラスの定義.
 */
#pragma once

#include"nkCollider.h"
#include"../_Math/nkVector.h"

namespace nkEngine
{

	/**
	 * 剛体情報.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct RigidBodyInfoS : Noncopyable
	{
	public:

		/** 座標. */
		Vector3 Position_ = Vector3::Zero;
		/** 回転. */
		Quaternion Rotation_ = Quaternion::Identity;
		/** コライダー. */
		ICollider* Collider_ = nullptr;
		/** 質量. */
		float Mass_ = 0.0f;

	};

	/**
	 * 剛体クラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class RigidBody : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		RigidBody()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~RigidBody()
		{
			Release();
		}

		/**
		 * 作成.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	rbInfo	Information describing the rb.
		 */
		void Create(RigidBodyInfoS& rbInfo);

		/**
		 * 解放.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Release();

		/**
		 * Gets the body.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		btRigidBody* GetBody()
		{
			return RigidBody_;
		}

	private:

		/** 剛体. */
		btRigidBody* RigidBody_ = nullptr;
		/** モーションステート. */
		btDefaultMotionState* MotionState_ = nullptr;
	
	};

}// namespace nkEngine