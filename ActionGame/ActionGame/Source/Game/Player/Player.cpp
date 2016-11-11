#include"stdafx.h"
#include"Player.h"
#include"../GameCamera.h"

namespace
{
	AnimationEventGroup AnimationEventTbl[Player::AnimationNum]
	{
		//AnimationWaiting
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationRun
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack
		{
			
			END_ANIMATION_EVENT(),
		},
	};

	SParicleEmitParameter AttackParticle
	{
		"fire_02.png",						//!<テクスチャのファイルパス。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!<初速度。
		0.1f,								//!<寿命。単位は秒。
		0.001f,								//!<発生時間。単位は秒。
		0.5f,								//!<パーティクルの幅。
		0.5f,								//!<パーティクルの高さ。
		D3DXVECTOR3(0.05f, 0.05f, 0.05f),		//!<初期位置のランダム幅。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!<初速度のランダム幅。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!<速度の積分のときのランダム幅。
		{									//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。		
			D3DXVECTOR4(0.0f,  0.0f, 1.0f, 1.0f),
			D3DXVECTOR4(0.25f, 0.0f, 0.5f,  0.5f),
			D3DXVECTOR4(0.5f,  0.0f, 0.75f, 0.5f),
			D3DXVECTOR4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		0,									//!<UVテーブルのサイズ。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!<重力。	
		true,								//!<死ぬときにフェードアウトする？
		0.5f,								//!<フェードする時間。
		1.0f,								//!<初期アルファ値。	
		true,								//!<ビルボード？
		1.0f,								//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,									//!<0半透明合成、1加算合成。
	};
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	Model.Load("Player.X",&Animation);
	Model.SetTransform(&Transform);
	Model.SetLight(&Light);
	Model.SetCamera(MainCamera.GetCamera());
	Model.SetShadowCasterFlag(true);
	Model.SetShadowReceiverFlag(true);

	MainCamera.SetPlayerTranceform(&Transform);

	Transform.Position = D3DXVECTOR3(0, 1, 0);

	CharacterController.Init(0.4f, 0.3f, Transform.Position);
	ChangeState(StateCode::StateWaiting);
	Animation.SetAnimationLoopFlags(StateCode::StateAttack, false);

	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 5.0f, 6.0f) + Transform.GetPosition());
	Shadow().SetLightTarget(Transform.GetPosition());

	mParticle = Model.FindBoneWorldMatrix("Bip01_R_Finger0");
	ParticlePos = D3DXVECTOR3(mParticle->m[3][0], mParticle->m[3][1], mParticle->m[3][2]);

	Particle.Init(MainCamera.GetCamera(), AttackParticle, &ParticlePos);
}

void Player::Update()
{
	if (State == StateCode::StateWaiting || State == StateCode::StateRun)
	{
		ChangeState(StateCode::StateWaiting);
		D3DXVECTOR3 moveSpeed = CharacterController.GetMoveSpeed();
		if (Input.GetKeyButton(KeyCode::Space) && !CharacterController.IsJump())
		{
			moveSpeed.y = 5.0f;
			CharacterController.Jump();
		}


		D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0);
		if (Input.GetKeyButton(KeyCode::W))
		{
			move += D3DXVECTOR3(0, 0, 1);
		}
		if (Input.GetKeyButton(KeyCode::S))
		{
			move += D3DXVECTOR3(0, 0, -1);
		}
		if (Input.GetKeyButton(KeyCode::A))
		{
			move += D3DXVECTOR3(-1, 0, 0);
		}
		if (Input.GetKeyButton(KeyCode::D))
		{
			move += D3DXVECTOR3(1, 0, 0);
		}

		//カメラの正面方向に合わせる
		D3DXVECTOR3 dirForward = MainCamera.GetDirectionForward();
		D3DXVECTOR3 dirRight = MainCamera.GetDirectionRight();
		D3DXVECTOR3 moveDir;
		moveDir.x = dirRight.x * move.x + dirForward.x * move.z;
		moveDir.y = 0.0f;	//Y軸はいらない。
		moveDir.z = dirRight.z * move.x + dirForward.z * move.z;

		static float MOVE_SPEED = 4.0f;
		moveSpeed.x = moveDir.x * MOVE_SPEED;
		moveSpeed.z = moveDir.z * MOVE_SPEED;


		//走っている
		float len = D3DXVec3Length(&moveDir);
		if (len > 0.0f)
		{
			ChangeState(StateCode::StateRun);
			D3DXQuaternionRotationAxis(&Transform.Rotation, &D3DXVECTOR3(0, 1, 0), atan2f(moveDir.x, moveDir.z) + D3DXToRadian(180.0f));
		}
		CharacterController.SetMoveSpeed(moveSpeed);
		CharacterController.Update();


		if (Input.GetKeyButton(KeyCode::Shift_L) && !CharacterController.IsJump())
		{
			ChangeState(StateCode::StateAttack);
			Particle.SetCreate(true);
		}
	}
	else if (State == StateCode::StateAttack)
	{
		D3DXVECTOR3 moveSpeed = CharacterController.GetMoveSpeed();
		moveSpeed *= 0.8f;
		CharacterController.SetMoveSpeed(moveSpeed);
		CharacterController.Update();

		if (!Animation.IsPlayAnim())
		{
			ChangeState(StateCode::StateWaiting);
			Particle.SetCreate(false);
		}
	}

	Transform.Position = CharacterController.GetPosition();
	
	AnimationControl();

	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 5.0f, 6.0f) + Transform.GetPosition());
	Shadow().SetLightTarget(Transform.GetPosition());

	Model.Update();
	ParticlePos = D3DXVECTOR3(mParticle->m[3][0], mParticle->m[3][1], mParticle->m[3][2]);
	Particle.Update();
}

void Player::Render()
{
	Model.Render();
	Particle.Render();

}

void Player::Release()
{
	Model.Release();
}

void Player::ChangeState(StateCode _NextState)
{
	State = _NextState;
}

void Player::AnimationControl()
{
	float time = 1.0f / 60.0f;
	switch (State)
	{
	case AnimationWaiting:
		PlayAnimation(AnimationCode::AnimationWaiting, 0.1f);
		break;
	case StateRun:
		PlayAnimation(AnimationCode::AnimationRun, 0.1f);
		time = 1.0f / 30.0f;
		break;
	case StateAttack:
		PlayAnimation(AnimationCode::AnimationAttack, 0.1f);
		time = 1.0f / 60.0f;
		break;
	default:
		break;
	}
	Animation.Update(time);
}

void Player::PlayAnimation(AnimationCode _AnimCode, float interpolateTime)
{
	if (Animation.GetNowAnimationNo() != _AnimCode)
	{
		Animation.PlayAnimation(_AnimCode, interpolateTime);
	}
}
