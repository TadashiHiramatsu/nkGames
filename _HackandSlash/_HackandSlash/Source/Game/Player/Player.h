/**
 * @file Source\Game\Player\Player.h
 *
 * �v���C���[�N���X�̒�`.
 */
#pragma once

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

#include"PlayerEquipment.h"

/**
 * �v���C���[�N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class Player : public IGameObject
{
public:

	/**
	 * �v���C���[�p�����[�^�̍\����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct PlayerParameterS
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		PlayerParameterS()
		{
			Level_ = 1;
			Experience_ = 0;
			NextLevelExperience_ = 10;
			Attack_ = 10;
			MaxHp_ = NowHp_ = 100;
			InvincibleTime_ = 1.0f;
		}

	public:

		/** ���x��. */
		int Level_;
		/** ���݂̌o���l. */
		int Experience_;
		/** ���̃��x���ւ̌o���l. */
		int NextLevelExperience_;
		/** �U����. */
		int	Attack_;
		/** �̗�. */
		int MaxHp_;
		/** �̗�. */
		int NowHp_;
		/** ���G����. */
		float InvincibleTime_;


	};

	/** �A�j���[�V�����R�[�h�̗�. */
	enum AnimationCodeE
	{
		AnimationInvalid = -1,	//!< ����
		AnimationIdol = 0,	//!< �ҋ@
		AnimationRun,			//!< ����
		AnimationAttack_01,		//!< �U��
		AnimationDeath_01,		//!< ���S
		AnimationNum,			//!< �A�j���[�V�����̐�
	};


	/** �X�e�[�g�R�[�h�̗�. */
	enum StateCodeE
	{
		StateWaiting = 0,	//!< �ҋ@
		StateWalk,			//!< ����
		StateRun,			//!< ����
		StateAttack,		//!< �U��
		StateDamage,		//!< ����
		StateDeath,			//!< ���S
	};

public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Player()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~Player()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Update()override;

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Render()override;

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Release()override;

	/**
	 * �U�����󂯂�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Damage();

	/**
	 * ���x���A�b�v����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void ParameterUpdate();

	/**
	 * �o���l���Z.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param add The add.
	 */
	void AddExperience(int add)
	{
		Parameter_.Experience_ += add;
	}

	/**
	 * �v���C���[�p�����[�^�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @return The player parameter.
	 */
	PlayerParameterS& GetParameter()
	{
		return Parameter_;
	}

	/**
	 * �|�W�V�����̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @return The position.
	 */
	D3DXVECTOR3& GetPosition()
	{
		return Transform_.Position_;
	}

	//����ł��邩��Ԃ�
	bool GetDeathFlag()
	{
		return (State_ == StateCodeE::StateDeath);
	}

	EquipmentItem* GetEquipmentItem(ItemTypeE type)
	{
		return PlayerEquipment_.GetEquipmentItem(type);
	}

	void SetEquipmentItem(EquipmentItem* item)
	{
		PlayerEquipment_.SetEquipmentItem(item);
	}

private:

	/**
	 * �X�e�[�g�X�V�֐�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param nextState State of the next.
	 */
	void ChangeState(StateCodeE nextState)
	{
		State_ = nextState;
	}

	/**
	 * �A�j���[�V�����Ǘ��֐�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void AnimationControl();

	/**
	 * �A�j���[�V�����؂�ւ��֐�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param animCode		  The animation code.
	 * @param interpolateTime The interpolate time.
	 */
	void PlayAnimation(AnimationCodeE animCode, float interpolateTime);

private:

	/** ���f�������_�[. */
	ModelRender ModelRender_;
	/** �A�j���[�V����. */
	Animation Animation_;
	/** �@���}�b�v. */
	Texture Normal_;
	/** �X�y�L�����}�b�v. */
	Texture Specular_;

	/** ���. */
	StateCodeE State_;

	/** The radius. */
	float Radius_ = 0.0f;
	/** The height. */
	float Height_ = 0.0f;
	/** �L�����N�^�[�R���g���[��. */
	CharacterController CharacterController_;

	/** �A�j���[�V�����C�x���g. */
	AnimationEventController AnimationEvent_;

	/** �v���C���[�̃p�����[�^. */
	PlayerParameterS Parameter_;

	/** ���C�t�񕜎��ԗp���[�J���^�C��. */
	float RecoveryLT_ = 0.0f;

	/** ���G���ԗp���[�J���^�C��. */
	float InvincibleLT = 0.0f;

	/** �R���W�����I�u�W�F�N�g. */
	unique_ptr<btCollisionObject> CollisionObject_;
	/** ���̌`��R���C�_�[. */
	unique_ptr<SphereCollider> SphereShape_;

	/** �������. */
	PlayerEquipment PlayerEquipment_;

};