#pragma once

#include "nkEngine/_Physics/nkCapsuleCollider.h"
#include "nkEngine/_Physics/CRigidBody.h"

namespace nkEngine
{
	class CharacterController
	{
	public:
		//コンストラクタ
		CharacterController();

		//デストラクタ
		~CharacterController();

		//初期化
		void Init(float _radius,float _height,const D3DXVECTOR3& _pos);

		//更新
		void Update();

		//座標を取得
		const D3DXVECTOR3& GetPosition() const 
		{
			return Position;
		}

		//座標を設定
		void SetPosition(const D3DXVECTOR3& _pos)
		{
			Position = _pos;
		}

		//移動速度を取得
		const D3DXVECTOR3& GetMoveSpeed()const
		{
			return MoveSpeed;
		}

		//移動速度を設定
		void SetMoveSpeed(const D3DXVECTOR3& _ms)
		{
			MoveSpeed = _ms;
		}

		//ジャンプさせる
		void Jump()
		{
			isJump = true;
			isOnGround = false;
		}

		//ジャンプフラグを取得
		bool IsJump()const
		{
			return isJump;
		}

		//地面の上にいるか判定
		bool IsOnGround()const
		{
			return isOnGround;
		}

		//コライダーを取得
		CCapsuleCollider* GetCollider()
		{
			return &Collider;
		}

		//重力を設定
		void SetGravity(float _gravity)
		{
			Gravity = _gravity;
		}

		//剛体を取得
		CRigidBody* GetRigidbody()
		{
			return &RigidBody;
		}

		//剛体を物理エンジンから削除
		void RemoveRigidBody();

	private:
		//座標
		D3DXVECTOR3 Position; 
		//移動速度
		D3DXVECTOR3 MoveSpeed; 
		//ジャンプフラグ
		bool isJump;
		//地面の上にいる
		bool isOnGround;
		//コライダー
		CCapsuleCollider Collider;
		//半径
		float Radius;
		//高さ
		float Height;
		//剛体
		CRigidBody RigidBody;
		//重力
		float Gravity;
	};
}