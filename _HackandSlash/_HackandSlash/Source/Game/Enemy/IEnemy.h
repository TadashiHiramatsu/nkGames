/**
 * @file Source\Game\Monster\IEnemy.h
 *
 * �G�̊��N���X�̒�`.
 */
#pragma once

#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\Player\Player.h"
#include"../GameCamera.h"

/**
 * �G�̊��N���X.
 * ���ׂĂ̓G�͂��̃N���X���p������
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class IEnemy : public IGameObject
{
protected:

	/** �X�e�[�g�R�[�h. */
	enum class StateCodeE
	{
		Spawn,		//!< �o��.
		Waiting,	//!< �����~�܂�.
		Loitering,	//!< �p�j.
		Chase,		//!< �ǂ�����.
		Attack,		//!< �U��.
		Hit,		//!< �q�b�g.
		Death,		//!< ��.
	};

public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	IEnemy();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual ~IEnemy();

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Update()override;

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Render()override;

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Release()override;

	/**
	 * �_���[�W�֐�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Damage()
	{
	}

	/**
	 * �|�W�V������ݒ�.
	 * �o���ʒu��ݒ肷��Ƃ��̂��߂Ɏg���Ă���̂ő��Ŏg���ƕs�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param [in,out] pos The position.
	 */
	void SetPosition(Vector3& pos)
	{
		Transform_.Position_ = pos;
		DefaultPosition_ = pos;
	}

	/**
	* �v���C���[�̃|�C���^��ݒ�.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/11
	*
	* @param [in,out] p If non-null, the Player to process.
	*/
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

	/**
	* ���x����ݒ�.
	*/
	void SetLevel(int l)
	{
		Level_ = l;
	}

	/**
	* �ړ����x��ݒ�.
	*
	* @param speed	�ړ����x.
	*/
	void SetMoveSpeed(float speed)
	{
		MoveSpeed_ = speed;
	}

	/**
	* �ړ����x���擾.
	*/
	float GetMoveSpeed() const
	{
		return MoveSpeed_;
	}

	/**
	* �ړ�������ݒ�.
	*
	* @param dir	�ړ������x�N�g��.
	*/
	void SetMoveDirection(const Vector3& dir)
	{
		MoveDirection_ = dir;
	}

	/**
	* �ړ��������擾.
	*/
	const Vector3& GetMoveDirection() const
	{
		return MoveDirection_;
	}

protected:

	/**
	 * State��ύX����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param nextState �ύX���StateCode.
	 */
	void ChangeState(StateCodeE nextState)
	{
		State_ = nextState;
	}

	/**
	 * �A�j���[�V�����Ǘ�.
	 * �p����̃N���X�Ŏ�������
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void AnimationControl() 
	{
	}

	/**
	 * �v���C���[�ւ̕����x�N�g�����v�Z.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to player dir.
	 */
	Vector2& GetToPlayerDir()
	{
		Vector3 toP;
		toP.Sub(Player_->Transform_.Position_, Transform_.Position_);
		toP.y = 0;
		toP.Normalize();
		return Vector2(toP.x, toP.z);
	}

	/**
	 * �v���C���[�Ƃ̋������v�Z. 
	 * �������l�����Ȃ�������Ԃ��܂�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to player dis.
	 */
	float GetToPlayerDis()
	{
		Vector3 toP;
		toP.Sub(Player_->Transform_.Position_ ,Transform_.Position_);
		toP.y = 0;
		return toP.Length();
	}

	/**
	 * �ړI�n�܂ł̕����x�N�g�����擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to destination.
	 */
	Vector2& GetToDestination()
	{
		Vector3 toD;
		toD.Sub(Destination_, Transform_.Position_);
		toD.y = 0;
		toD.Normalize();
		return Vector2(toD.x, toD.z);
	}

	/**
	 * �ړI�n�܂ł̋������v�Z. 
	 * �������l�����Ȃ�������Ԃ��܂�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to destination dis.
	 */
	float GetToDestinationDis()
	{
		Vector3 toD;
		toD.Sub(Destination_, Transform_.Position_);
		toD.y = 0;
		return toD.Length();
	}

	/**
	* ���Ńp�[�e�B�N���̔���. 
	*
	* @param bonename	�{�[����.
	* @param param		�p�[�e�B�N�����.
	*/
	void DisappearanceParticleSet(char* bonename, const ParticleParameterS& param)
	{
		//�s����擾.
		Matrix posmatrix = *ModelRender_.FindBoneWorldMatrix(bonename);
		
		//���W���擾.
		Vector3 pos;
		pos.x = posmatrix.m[3][0];
		pos.y = posmatrix.m[3][1];
		pos.z = posmatrix.m[3][2];

		//��������(�b).
		float LifeTime = 8.0f;

		//�p�[�e�B�N���G�~�b�^���쐬.
		ParticleEmitter* pe = NewGO<ParticleEmitter>();
		//������.
		pe->Start(g_MainCamera->GetCamera(), param, pos, LifeTime);
	}

protected:

	/** �X�L�����f���f�[�^�n���h��. */
	SkinModelDataHandle SkinModelDataHandle_;
	/** ���f�������_. */
	ModelRender ModelRender_;
	/** �A�j���[�V����. */
	Animation Animation_;

	/** ���a. */
	float Radius_;
	/** ����. */
	float Height_;
	/** �L�����N�^�[�R���g���[��. */
	CharacterController CharacterController_;

	/** �q�b�g�|�C���g. */
	int Hp_;

	/** �X�|�[���ʒu ��������̋����ړ��ł���. */
	Vector3 DefaultPosition_ = Vector3::Zero;
	/** ����. */
	float Distance_;
	/** �ړI�n. */
	Vector3 Destination_ = Vector3::Zero;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;
	/**   
	 * �v���C���[��ǂ�������ő勗��   
	 * �����鋗�������p. 
	 */
	float toPlayerMaxDis_; 
	/** �v���C���[���U�����n�߂鋗��. */
	float PlayerAttackDis_;

	/** �����~�܂鎞��. */
	float WaitingTime_;
	/** �����~�܂鎞�Ԍv���̂��߂̃��[�J���^�C��. */
	float WaitingLT_;

	/** �X�e�[�g. */
	StateCodeE State_;

	/** �A�j���[�V�����C�x���g. */
	AnimationEventController AnimationEvent_;

	/** �A���t�@�l. */
	float Alpha_ = 1.0f;

	/** ���S��������̈�x����̃t���O. */
	bool isOnceDeath_ = false;

	/** ���ł܂ł̎���(�b). */
	float DisappearanceTime_ = 5.0f;
	/** ���Ŏ��Ԃ̃��[�J���^�C��. */
	float DisappearanceLT_ = 0.0f;

	/** ���x��. */
	int Level_ = 1;

	/** �ړ����x. */
	float MoveSpeed_ = 50.0f;
	/** �ړ�����. */
	Vector3 MoveDirection_ = Vector3::Zero;

};