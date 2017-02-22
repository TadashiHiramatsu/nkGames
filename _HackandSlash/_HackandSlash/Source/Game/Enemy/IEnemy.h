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
	enum StateCodeE
	{
		StateSpawn,		//!< �o��
		StateWaiting,	//!< �����~�܂�
		StateLoitering, //!< �p�j
		StateChase,		//!< �ǂ�����
		StateAttack,	//!< �U��
		StateDamage,	//!< �_���[�W
		StateDeath,		//!< �����Ď�
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
	 * �_���[�W���󂯂�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Damage(){}

	/**
	 * �|�W�V������ݒ�.
	 * �o���ʒu��ݒ肷��Ƃ��̂��߂Ɏg���Ă���̂ő��Ŏg���ƕs�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param [in,out] pos The position.
	 */
	void SetPosition(D3DXVECTOR3& pos)
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
	D3DXVECTOR2& GetToPlayerDir()
	{
		D3DXVECTOR2 toP = D3DXVECTOR2(Player_->Transform_.Position_.x, Player_->Transform_.Position_.z) - D3DXVECTOR2(Transform_.Position_.x, Transform_.Position_.z);
		D3DXVec2Normalize(&toP, &toP);
		return toP;
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
		D3DXVECTOR3 toP = Player_->Transform_.Position_ - Transform_.Position_;
		return D3DXVec2Length(&D3DXVECTOR2(toP.x, toP.z));
	}

	/**
	 * �ړI�n�܂ł̕����x�N�g�����擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to destination.
	 */
	D3DXVECTOR2& GetToDestination()
	{
		D3DXVECTOR2 toD = Destination_ - D3DXVECTOR2(Transform_.Position_.x, Transform_.Position_.z);
		D3DXVec2Normalize(&toD, &toD);
		return toD;
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
		D3DXVECTOR2 toD = Destination_ - D3DXVECTOR2(Transform_.Position_.x, Transform_.Position_.z);
		return D3DXVec2Length(&toD);
	}

protected:

	/** �X�L�����f���f�[�^�n���h��. */
	SkinModelDataHandle SkinModelDataHandle_;
	/** ���f�������_. */
	ModelRender ModelRender_;
	/** �A�j���[�V����. */
	Animation Animation_;

	/** The radius. */
	float Radius_;
	/** The height. */
	float Height_;
	/** �L�����N�^�[�R���g���[��. */
	CharacterController CharacterController_;

	/** �q�b�g�|�C���g. */
	int Hp_;

	/** �X�|�[���ʒu ��������̋����ړ��ł���. */
	D3DXVECTOR3 DefaultPosition_;
	/** ����. */
	float Distance_;
	/** �ړI�n. */
	D3DXVECTOR2 Destination_;

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

	/** �A���t�@�f�[�^. */
	float Alpha_ = 1.0f;

	//���S�p�[�e�B�N�����o�����߂̈�x����̃t���O
	bool isOnceDeath = false;

};