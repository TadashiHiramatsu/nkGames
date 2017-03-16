/**
 * @file _Graphics\_Particle\nkParticleEmitter.h
 *
 * �p�[�e�B�N���G�~�b�^�N���X�̒�`.
 */
#pragma once

#include"nkParticle.h"

namespace nkEngine
{

	/**
	 * �p�[�e�B�N���p�����[�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	struct ParticleParameterS
	{
	public:

		/** �e�N�X�`���̃t�@�C���p�X. */
		const char* TexturePath_;
		/** �����x. */
		Vector3	InitVelocity_;
		/** �����B�P�ʂ͕b. */
		float		Life_;
		/** �������ԁB�P�ʂ͕b. */
		float		IntervalTime_;
		/** �p�[�e�B�N���̕�. */
		float		W_;
		/** �p�[�e�B�N���̍���. */
		float		H_;
		/** �����ʒu�̃����_����. */
		Vector3	InitPositionRandomMargin_;
		/** �����x�̃����_����. */
		Vector3	InitVelocityVelocityRandomMargin_;
		/** ���x�̐ϕ��̂Ƃ��̃����_����. */
		Vector3	AddVelocityRandomMargih_;
		/** UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�. */
		Vector4	UVTable_[4];
		/** UV�e�[�u���̃T�C�Y. */
		int			UVTableSize_;
		/** �d��. */
		Vector3	Gravity_;
		/** ���ʂƂ��Ƀt�F�[�h�A�E�g����H. */
		bool		isFade_;
		/** �t�F�[�h���鎞��. */
		float		FadeTime_;
		/** �����A���t�@�l. */
		float		InitAlpha_;
		/** �r���{�[�h�H. */
		bool		isBillboard_;
		/** �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂�. */
		float		Brightness_;
		/** 0�����������A1���Z����. */
		int			AlphaBlendMode_;

	};

	/**
	 * �p�[�e�B�N���G�~�b�^�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class ParticleEmitter : public IGameObject
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		ParticleEmitter()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~ParticleEmitter()
		{
		}

		/**
		 * ������. 
		 * �I�[�o�[���C�h����Ȃ����ߎ����ŌĂԕK�v������.
		 *
		 * @author HiramatsuTadashi
		 *
		 * @param [in,out] camera	    �J����.
		 * @param 		   param	    �p�[�e�B�N�����.
		 * @param 		   emitPosition �������W.
		 * @param 		   lifeTime	    ����(�b).
		 */
		void Start(const Camera* camera, const ParticleParameterS& param, const Vector3& emitPosition, float lifeTime);

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update()override;

		/**
		 * �p�[�e�B�N���ɗ͂�������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param force ��.
		 */
		void AddForce(const Vector3& force);

	private:

		/** �������Ԃ̃��[�J���^�C��. */
		float IntervalLT_ = 0.0f;
		/** �J����. */
		const Camera* Camera_ = nullptr;
		/** �p�����[�^. */
		ParticleParameterS Param_;
		/** �G�~�b�^�[�̍��W. */
		Vector3 EmitPosition_;
		/** �p�[�e�B�N���̃��X�g. */
		list<Particle*>	ParticleList_;

		/** �G�~�b�^�̎���. */
		float LifeTime_ = 0.0f;
		/** �G�~�b�^�̎����̃��[�J���^�C��. */
		float LifeLT_ = 0.0f;

		/** �t�@�C���p�X. */
		char Filepath_[64];

	};
}