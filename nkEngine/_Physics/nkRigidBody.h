/**
 * @file	_Physics\nkRigidBody.h
 *
 * 剛体クラスの定義.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * 剛体情報.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct RigidBodyInfoS
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		RigidBodyInfoS() :
			Collider_(nullptr),
			Mass_(0.0f),
			Position_(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			Rotation_(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
		{
		}

	public:

		/** 座標. */
		D3DXVECTOR3 Position_;
		/** 回転. */
		D3DXQUATERNION Rotation_;
		/** コライダー. */
		ICollider* Collider_;
		/** 質量. */
		float Mass_;

	};

	/**
	 * 剛体クラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CRigidBody
	{
	public:

		/**
		 * Default constructor.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CRigidBody();

		/**
		 * Destructor.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CRigidBody();

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
		btRigidBody* RigidBody_;
		/** モーションステート. */
		btDefaultMotionState* MotionState_;
	};

}// namespace nkEngine