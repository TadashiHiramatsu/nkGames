/**
 * @file _Component\nkCharacterController.h
 *
 * キャラクターコントローラクラスの定義.
 */
#pragma once

#include"../_Physics/nkCapsuleCollider.h"

namespace nkEngine
{

	/**
	 * キャラクターコントローラクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class CharacterController
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		CharacterController();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~CharacterController();

		/**
		 * 初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param radius The radius.
		 * @param height The height.
		 * @param pos    The position.
		 */
		void Init(float radius, float height, const D3DXVECTOR3& pos);

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * 座標を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The position.
		 */
		const D3DXVECTOR3& GetPosition() const 
		{
			return Position_;
		}

		/**
		 * 座標を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param pos The position.
		 */
		void SetPosition(const D3DXVECTOR3& pos)
		{
			Position_ = pos;
		}

		/**
		 * 移動速度を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The move speed.
		 */
		const D3DXVECTOR3& GetMoveSpeed() const
		{
			return MoveSpeed_;
		}

		/**
		 * 移動速度を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param ms The milliseconds.
		 */
		void SetMoveSpeed(const D3DXVECTOR3& ms)
		{
			MoveSpeed_ = ms;
		}

		/**
		 * ジャンプさせる.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Jump()
		{
			isJump_ = true;
			isOnGround_ = false;
		}

		/**
		 * ジャンプフラグを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return True if jump, false if not.
		 */
		bool IsJump() const
		{
			return isJump_;
		}

		/**
		 * 地面の上にいるか判定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return True if on ground, false if not.
		 */
		bool IsOnGround() const
		{
			return isOnGround_;
		}

		/**
		 * コライダーを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the collider.
		 */
		CapsuleCollider* GetCollider()
		{
			return &Collider_;
		}

		/**
		 * 重力を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param _gravity The gravity.
		 */
		void SetGravity(float _gravity)
		{
			Gravity_ = _gravity;
		}

		/**
		 * 剛体を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the rigidbody.
		 */
		RigidBody* GetRigidbody()
		{
			return &RigidBody_;
		}

		/**
		 * 剛体を物理エンジンから削除.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void RemoveRigidBody();

	private:

		/** 座標. */
		D3DXVECTOR3 Position_; 
		/** 移動速度. */
		D3DXVECTOR3 MoveSpeed_;
		/** ジャンプフラグ. */
		bool isJump_;
		/** 地面の上にいる。true:地面上,false:空中. */
		bool isOnGround_;
		/** カプセル形状のコライダー. */
		CapsuleCollider Collider_;
		/** 半径. */
		float Radius_;
		/** 高さ. */
		float Height_;
		/** 剛体. */
		RigidBody RigidBody_;
		/** 重力. */
		float Gravity_;

	};

}// namespace nkEngine