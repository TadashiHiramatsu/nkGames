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
	enum class AnimationCodeE
	{
		Invalid = -1,				//!< ����
		Idol = 0,					//!< �ҋ@
		Walk,						//!< ����
		Run,						//!< ����
		Attack_Start,				//!< �U���A�j���[�V�����R�[�h�n��.
		Attack_01 = Attack_Start,	//!< �U��01
		Attack_08,					//!< �U��08
		Attack_End = Attack_08,		//!< �U��02
		Death_01,					//!< ���S
		AnimationNum,				//!< �A�j���[�V�����̐�
	};


	/** �X�e�[�g�R�[�h�̗�. */
	enum class StateCodeE
	{
		Waiting = 0,	//!< �ҋ@
		Walk,			//!< ����
		Run,			//!< ����
		Attack,			//!< �U��
		Damage,			//!< ����
		Death,			//!< ���S
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
	const Vector3& GetPosition() const
	{
		return Transform_.Position_;
	}

	/**
	* ����ł��邩��Ԃ�.
	*/
	bool GetDeathFlag() const
	{
		return (State_ == StateCodeE::Death);
	}

	/**
	* �A�C�e�����擾
	*
	* @param type	�A�C�e���^�C�v.
	*
	* @return �A�C�e��.
	*/
	EquipmentItem* GetEquipmentItem(ItemTypeE type)
	{
		return PlayerEquipment_.GetEquipmentItem(type);
	}

	/**
	* �A�C�e����ݒ�.
	*
	* @param item	�A�C�e��.
	*/
	void SetEquipmentItem(EquipmentItem* item)
	{
		PlayerEquipment_.SetEquipmentItem(item);
	}

	/**
	* �A�C�e�����ݒ肳��Ă��邩�̃t���O��Ԃ��܂�.
	*
	* @param type	�A�C�e���^�C�v.
	*
	* @return true or false.
	*/
	bool GetIsSet(ItemTypeE type) const
	{
		return PlayerEquipment_.GetIsSet(type);
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

	/**
	* ���X�|�[���֐�.
	*/
	void Respawn()
	{
		//�ҋ@��Ԃɕω�.
		ChangeState(StateCodeE::Waiting);
		PlayAnimation(AnimationCodeE::Idol, 0.0f);

		//���݂̌o���l��3����1�����X�g.
		float param  = Parameter_.Experience_ / 3;
		Parameter_.Experience_ -= param;

		//�ʒu�����X�|�[���ʒu�ɕύX.
		Transform_.Position_ = RespawnPosition_;

		//�̗͂�1�ɐݒ�.
		Parameter_.NowHp_ = 1;

		//�C���^�[�o���̃��[�J���^�C����������.
		InvincibleLT = 0.0f;
	}

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

	/** �Đ��̃��N�G�X�g���o���Ă���U�����[�V�����ԍ�. */
	AnimationCodeE ReqAttackAnimCode_;
	/** ���̍U�����[�V�����ԍ�. */
	AnimationCodeE NextAttackAnimCode_;

	/** ���X�|�[���ʒu. */
	Vector3 RespawnPosition_;

};