/**
 * @file	Source\Game\GameCamera.cpp
 *
 * �Q�[���J�����N���X�̎���.
 */
#include"stdafx.h"
#include"GameCamera.h"

#include"Window\MenuWindow\MenuSystem.h"

/**
 * Starts this object.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
void GameCamera::Start()
{

	//�����l��ݒ�.
	PlusPosition_ = Vector3(0, 1.4f, 0);

	//�J�����̎��_�̕�����ݒ�.
	Camera_.SetPosDirection(Vector3(0.0f, 0.2f, -1.0f));

	//�J�����̒����_��ݒ�.
	Vector3 target;
	target.Add(Player_->Transform_.Position_ , PlusPosition_);
	Camera_.SetTarget(target);

	//������ݒ�.
	DistanceMax_ = Distance_ = 8.0f;
	Camera_.SetDistance(Distance_);

	//�X�V
	Camera_.Update();

	//�r���[�s��̋t�s����擾.
	ViewInvMatrix_ = &Camera_.GetViewInvMatrix();

	//�J�����R���W������������.
	CameraCollision_.Start(0.1f,&Camera_.GetPosDirection(), &Camera_.GetTarget());
	CameraCollision_.SetDefaultDistance(DistanceMax_);

}

/**
 * �X�V.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
void GameCamera::Update()
{
	//�J�����܂킷��[

	Vector2 Rstick = Vector2::Zero;
	Vector2 Lstick = Vector2::Zero;

	if (!g_MenuSystem->GetEffectiveness())
	{
		//���j���[���J����Ă��Ȃ��̂ŉ�]�ł���.
		
		//�X�e�B�b�N�̏����擾.
		Rstick = XInput().GetRightStick();
		Lstick = XInput().GetLeftStick();

		//����].
		Camera_.SpinHorizontally(Rstick.x* SpinSpeed * Time().DeltaTime());

		//�c��].
		Camera_.SpinVertically(Rstick.y * SpinSpeed * Time().DeltaTime() * -1);

	}

	//�J�����̒����_��ݒ�.
	Vector3 target;
	target.Add(Player_->Transform_.Position_, PlusPosition_);
	Camera_.SetTarget(target);

	//�J�����R���W�����̍X�V.
	CameraCollision_.Update();

	//�������擾.
	float dis = CameraCollision_.GetDistance();

	//�������v�Z.
	if (dis > Distance_)
	{
		//�L�тĂ���̂Ŋ�����t����.

		//�߂鑬�x.
		float speed = 2.0f *  Time().DeltaTime();
		float movement = Rstick.Length() + Lstick.Length();
		Distance_ += (dis - Distance_) * movement * speed;

	}
	else
	{
		//�k�܂��Ă���̂ł��̂܂ܐݒ�.
		Distance_ = dis;
	}

	//�ő勗���𒴂��Ȃ��悤�ɂ���.
	Distance_ = fmin(Distance_, DistanceMax_);
	//������ݒ�.
	Camera_.SetDistance(Distance_);

	//�J�����̍X�V.
	Camera_.Update();

}