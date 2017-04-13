/**
* �E�H�[���b�N�̃{�X�N���X�̎���.
*/
#include"stdafx.h"
#include"Boss_Warlock.h"

#include"HFSM\WarlockState_Waiting.h"
#include"HFSM\WarlockState_Combat.h"
#include"HFSM\WarlockState_Death.h"

/**
* ������.
*/
void Boss_Warlock::Start()
{
	//���f���f�[�^�����\�[�X�o�^���ēǂݍ���.
	SMDResources().Load(SkinModelDataHandle_, "Boss_Warlock.X", &Animation_);

	//���f�������_�[��������.
	ModelRender_.Load(SkinModelDataHandle_.GetBody());

	//���N���X�̏�����.
	IBoss::Start();

	//�ҋ@�A�j���[�V�������J�n
	PlayAnimation(AnimationCodeE::Idol, 0.3f);

	Transform_.Position_ = Vector3(10, 5, 0);

	Radius_ = 1.8f;
	Height_ = 2.5f;
	//�L�����N�^�[�R���g���[���̏�����
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);

	InitHFSM();
}

/**
* �X�V.
*/
void Boss_Warlock::Update()
{
	//�ړ��x�N�g��.
	Vector3 movedir = CharacterController_.GetMoveSpeed();
	
	StateList_[(int)State_]->Update();

	switch (State_)
	{
	case StateCodeE::Waiting:
		break;
	case StateCodeE::Combat:
		break;
	case StateCodeE::Death:
		break;
	default:
		break;
	}

	//�L�����N�^�[�R���g���[���Ɉړ�����ݒ�
	Vector3 move = movedir;
	move.Normalize();
	move.Scale(MoveSpeed_);
	CharacterController_.SetMoveSpeed(move);
	//�L�����N�^�[�R���g���[���̍X�V
	CharacterController_.Update();

	//�v�Z�I�������|�W�V�������擾
	Transform_.Position_ = CharacterController_.GetPosition();

	//�A�j���[�V�������X�V
	AnimationControl();

	//���N���X�̍X�V
	IBoss::Update();
}

/**
* �`��.
*/
void Boss_Warlock::Render()
{
	//���N���X�̕`��
	IBoss::Render();
}

/**
* ���.
*/
void Boss_Warlock::Release()
{
	//���̂̍폜.
	CharacterController_.RemoveRigidBody();
}

/**
* �_���[�W�֐�.
*/
void Boss_Warlock::Damage()
{
}

/**
* �A�j���[�V�����Ǘ�.
*/
void Boss_Warlock::AnimationControl()
{
	//�A�j���[�V�����^�C��
	float time = Time().DeltaTime();

	//�A�j���[�V�����X�V.
	Animation_.Update(time);
}

/**
* ��ԑJ��.
*
* @param nextstate	���̏��.
*/
void Boss_Warlock::ChangeState(StateCodeE nextstate)
{
	if (State_ != StateCodeE::Invalid)
	{
		//��Ԃ��ݒ肳��Ă���.
		StateList_[(int)State_]->Exit();
	}

	State_ = nextstate;

	//�J�n���������s.
	StateList_[(int)State_]->Entry();

}

/**
* HFSM�̏�����.
*/
void Boss_Warlock::InitHFSM()
{
	//�ҋ@���
	StateList_.push_back(unique_ptr<WarlockState_Waiting>(new WarlockState_Waiting(this)));
	//�퓬���
	StateList_.push_back(unique_ptr<WarlockState_Combat>(new WarlockState_Combat(this)));
	//���S���
	StateList_.push_back(unique_ptr<WarlockState_Death>(new WarlockState_Death(this)));

	//�ҋ@��Ԃɕω�.
	ChangeState(StateCodeE::Waiting);
}
