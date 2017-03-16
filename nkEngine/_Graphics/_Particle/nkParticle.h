/**
 * @file _Graphics\_Particle\nkParticle.h
 *
 * �p�[�e�B�N���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{
	/** �p�[�e�B�N���̃p�����[�^. */
	struct ParticleParameterS;

	/**
	 * �p�[�e�B�N���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Particle : public IGameObject
	{
	public:

		/** ���. */
		enum class StateCodeE 
		{
			Run = 0,	//!< ����.
			FadeOut,	//!< �t�F�[�h�A�E�g.
			Dead,		//!< ��.
		};

	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Particle()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Particle()
		{
		}

		/**
		 * ������. �I�[�o�[���C�h���Ă��Ȃ��̂Ŏ����ŌĂԕK�v����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param [in,out] camera	    If non-null, the camera.
		 * @param 		   param	    The parameter.
		 * @param [in,out] emitPosition If non-null, the emit position.
		 * @param [in,out] filepath	    If non-null, the filepath.
		 */
		void Start(const Camera* camera, const ParticleParameterS& param, const Vector3& emitPosition, char* filepath);

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update()override;

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] texture If non-null, the texture.
		 */
		void Render()override;

		/**
		 * Adds a force.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param addForce The add force.
		 */
		void AddForce(const Vector3 addForce)
		{
			ApplyForce_ = addForce;
		}

		/**
		 * Gets the dead.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool GetDead() const
		{
			return isDead_;
		}

	private:

		/** �v���~�e�B�u. */
		Primitive Primitive_; 
		/** �G�t�F�N�g. */
		Effect* Effect_;
		/** �J����. */
		const Camera* Camera_;

		/** The texture. */
		Texture Texture_;

		/** ���[���h�s��. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** �X�P�[���s��. */
		Matrix ScaleMatrix_ = Matrix::Identity;
		/** The scale. */
		Vector3	Scale_ = Vector3::One;
	
		/** ���C�t. */
		float Life_ = 0.0f;
		/** �^�C�}�[. */
		float Timer_ = 0.0f;
		/** ���x. */
		Vector3 Velocity_ = Vector3::Zero;
		/** ���W. */
		Vector3	Position_ = Vector3::Zero;
		/** �d��. */
		Vector3	Gravity_ = Vector3::Zero;
		/** Z������̉�]. */
		float RotateZ_ = 0;
		/** ���x�̐ϕ��̂Ƃ��̃����_����. */
		Vector3 AddVelocityRandomMargih_ = Vector3::Zero;
		/** ���S�t���O. */
		bool isDead_ = false;
		/** ���ʂƂ��Ƀt�F�[�h�A�E�g����H. */
		bool isFade_ = false;
		/** �t�F�[�h�̎���. */
		float FadeTime_ = 0.0f;
		/** ���. */
		StateCodeE State_;
		/** �����A���t�@. */
		float InitAlpha_ = 1.0f;
		/** �A���t�@. */
		float Alpha_ = 1.0f;
		/** �r���{�[�h�H. */
		bool isBillboard_ = false;
		/** �O�����������. */
		Vector3 ApplyForce_ = Vector3::Zero;
		/** �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂�. */
		float Brightness_ = 0.0f;
		/** 0�����������A1���Z����. */
		int	AlphaBlendMode_ = 0;

	};

}// namespace nkEngine