/**
 * @file Source\Game\Player\Player.h
 *
 * �v���C���[�N���X�̒�`.
 */
#pragma once

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

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
			Attack_ = 1;
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
		int InvincibleTime_;

	};

	/** �A�j���[�V�����R�[�h�̗�. */
	enum AnimationCodeE
	{
		AnimationInvalid = -1,	//!< ����
		AnimationWaiting = 0,	//!< �ҋ@
		AnimationWalk,			//!< ����
		AnimationRun,			//!< ����
		AnimationAttack,		//!< �U��
		AnimationHit,			//!< ����
		AnimationDead,			//!< ���S
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
		StateDead,			//!< ���S
	};

public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Player();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~Player();

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

private:

	/**
	 * �X�e�[�g�X�V�֐�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param nextState State of the next.
	 */
	void ChangeState(StateCodeE nextState);

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

	/** ���C�g. */
	Light Light_;
	/** ���f�������_�[. */
	ModelRender ModelRender_;
	/** �A�j���[�V����. */
	Animation Animation_;

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

	//ParticleEmitter Particle;
	//D3DXMATRIX* mParticle;
	//D3DXVECTOR3 ParticlePos;

	/** ���蕐��̃g�����X�t�H�[��. */
	Transform WeaponTransformL_;
	/** ���蕐��̃��C�g. */
	Light WeaponLightL_;
	/** ���蕐��̃��f�������_�[. */
	ModelRender WeaponModelRenderL_;

	/** �E�蕐��̃g�����X�t�H�[��. */
	Transform WeaponTransformR_;
	/** �E�蕐��̃��C�g. */
	Light WeaponLightR_;
	/** �E�蕐��̃��f�������_�[. */
	ModelRender WeaponModelRenderR_;

	/** ���G���Ԍv���p���[�J���^�C��. */
	float InvincibleLT_ = 0.0f;
	/** ���C�t�񕜎��ԗp���[�J���^�C��. */
	float RecoveryLT_ = 0.0f;

	/** �R���W�����I�u�W�F�N�g. */
	unique_ptr<btCollisionObject> CollisionObject_;
	/** ���̌`��R���C�_�[. */
	unique_ptr<SphereCollider>	SphereShape_;

};