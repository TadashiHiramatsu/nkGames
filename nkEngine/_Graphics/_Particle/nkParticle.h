/**
 * @file _Graphics\_Particle\nkParticle.h
 *
 * �p�[�e�B�N���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{
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

		/** Values that represent states. */
		enum StateE 
		{
			StateRun = 0,	//!< ����.
			StateFadeOut,	//!< �t�F�[�h�A�E�g.
			StateDead,		//!< ��.
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
		void Start(Camera* camera, const ParticleParameterS& param, D3DXVECTOR3& emitPosition, char* filepath);

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
		void AddForce(const D3DXVECTOR3 addForce)
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
		bool GetDead() 
		{
			return isDead_;
		}

	private:

		/** �v���~�e�B�u. */
		Primitive Primitive_; 
		/** �G�t�F�N�g. */
		Effect* Effect_;
		/** �J����. */
		Camera* Camera_;

		/** The texture. */
		Texture Texture_;

		/** ���[���h�s��. */
		D3DXMATRIX WorldMatrix_;
		/** �X�P�[���s��. */
		D3DXMATRIX ScaleMatrix_;
		/** The scale. */
		D3DXVECTOR3	Scale_;
	
		/** ���C�t. */
		float Life_ = 0.0f;
		/** �^�C�}�[. */
		float Timer_ = 0.0f;
		/** ���x. */
		D3DXVECTOR3 Velocity_ = D3DXVECTOR3(0, 0, 0);
		/** ���W. */
		D3DXVECTOR3	Position_ = D3DXVECTOR3(0, 0, 0);
		/** �d��. */
		D3DXVECTOR3	Gravity_ = D3DXVECTOR3(0, 0, 0);
		/** Z������̉�]. */
		float RotateZ_ = 0;
		/** ���x�̐ϕ��̂Ƃ��̃����_����. */
		D3DXVECTOR3 AddVelocityRandomMargih_ = D3DXVECTOR3(0, 0, 0);
		/** ���S�t���O. */
		bool isDead_ = false;
		/** ���ʂƂ��Ƀt�F�[�h�A�E�g����H. */
		bool isFade_ = false;
		/** �t�F�[�h�̎���. */
		float FadeTime_ = 0.0f;
		/** ���. */
		StateE State_;
		/** �����A���t�@. */
		float InitAlpha_ = 1.0f;
		/** �A���t�@. */
		float Alpha_ = 1.0f;
		/** �r���{�[�h�H. */
		bool isBillboard_ = false;
		/** �O�����������. */
		D3DXVECTOR3 ApplyForce_ = D3DXVECTOR3(0, 0, 0);
		/** �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂�. */
		float Brightness_ = 0.0f;
		/** 0�����������A1���Z����. */
		int	AlphaBlendMode_ = 0;

	};

}// namespace nkEngine