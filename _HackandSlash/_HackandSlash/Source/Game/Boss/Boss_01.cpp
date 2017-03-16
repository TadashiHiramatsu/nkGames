/**
* �{�X_01�N���X�̎���.
*/
#include"stdafx.h"
#include"Boss_01.h"

/**
* ������.
*/
void Boss_01::Start()
{
	//���f���f�[�^�����\�[�X�o�^���ēǂݍ���.
	SMDResources().Load(SkinModelDataHandle_, "Boss_01.X", &Animation_);

	//���f�������_�[��������.
	ModelRender_.Load(SkinModelDataHandle_.GetBody());

	//���N���X�̏�����.
	IBoss::Start();

	//�ҋ@��Ԃɕω�.
	ChangeState(StateCodeE::Waiting);

	//�ҋ@�A�j���[�V�������J�n
	PlayAnimation(AnimationCodeE::Waiting, 0.3f);

	Transform_.Position_ = Vector3(10, 5, 0);

	Radius_ = 1.2f;
	Height_ = 2.5f;
	//�L�����N�^�[�R���g���[���̏�����
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);

}

/**
* �X�V.
*/
void Boss_01::Update()
{
	//�ړ��x�N�g��.
	Vector3 movespeed = CharacterController_.GetMoveSpeed();
	
	switch (State_)
	{
	case StateCodeE::Spawn:
		break;
	case StateCodeE::Waiting:
		break;
	case StateCodeE::Chase:
		break;
	case StateCodeE::Turn:
		break;
	case StateCodeE::Attack:
		break;
	case StateCodeE::Death:
		break;
	default:
		break;
	}

	//�L�����N�^�[�R���g���[���Ɉړ�����ݒ�
	CharacterController_.SetMoveSpeed(movespeed);
	//�L�����N�^�[�R���g���[���̍X�V
	CharacterController_.Update();

	//�v�Z�I�������|�W�V�������擾
	Transform_.Position_ = CharacterController_.GetPosition();

	//�A�j���[�V�������X�V
	AnimationControl();

	//���N���X���X�V
	IBoss::Update();
}

/**
* �`��.
*/
void Boss_01::Render()
{
	//���N���X�̕`��
	IBoss::Render();
}

/**
* ���.
*/
void Boss_01::Release()
{
	//���̂̍폜.
	CharacterController_.RemoveRigidBody();
}

/**
* �_���[�W�֐�.
*/
void Boss_01::Damage()
{
}

/**
* �A�j���[�V�����Ǘ�.
*/
void Boss_01::AnimationControl()
{
	//�A�j���[�V�����^�C��
	float time = Time().DeltaTime();

	switch (State_)
	{
	case StateCodeE::Spawn:
		break;
	case StateCodeE::Waiting:
		//�ҋ@�A�j���[�V����.
		PlayAnimation(AnimationCodeE::Waiting, 0.3f);
		break;
	case StateCodeE::Chase:
		break;
	case StateCodeE::Turn:
		break;
	case StateCodeE::Attack:
		break;
	case StateCodeE::Death:
		break;
	default:
		break;
	}
	
	//�A�j���[�V�����X�V.
	Animation_.Update(time);

}
