/**
 * @file _Graphics\_Particle\nkParticle.h
 *
 * �p�[�e�B�N���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{
	struct ParicleParameterS;

	/**
	 * �p�[�e�B�N���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Particle
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
		Particle();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Particle();

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] camera	    If non-null, the camera.
		 * @param 		   param	    The parameter.
		 * @param [in,out] emitPosition If non-null, the emit position.
		 */
		void Init(Camera* camera, const ParicleParameterS& param, D3DXVECTOR3* emitPosition);

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] texture If non-null, the texture.
		 */
		void Render(IDirect3DTexture9* texture);

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
		ID3DXEffect* Effect_;
		/** �J����. */
		Camera* Camera_;

		/** ���[���h�s��. */
		D3DXMATRIX WorldMatrix_;
		/** �X�P�[���s��. */
		D3DXMATRIX ScaleMatrix_;
		/** The scale. */
		D3DXVECTOR3	Scale_;
	
		/** ���C�t. */
		float Life_;
		/** �^�C�}�[. */
		float Timer_;
		/** ���x. */
		D3DXVECTOR3 Velocity_;
		/** ���W. */
		D3DXVECTOR3	Position_;
		/** �d��. */
		D3DXVECTOR3	Gravity_;
		/** Z������̉�]. */
		float RotateZ_;
		/** ���x�̐ϕ��̂Ƃ��̃����_����. */
		D3DXVECTOR3 AddVelocityRandomMargih_;
		/** ���S�t���O. */
		bool isDead_;
		/** ���ʂƂ��Ƀt�F�[�h�A�E�g����H. */
		bool isFade_;
		/** �t�F�[�h�̎���. */
		float FadeTime_;
		/** ���. */
		StateE State_;
		/** �����A���t�@. */
		float InitAlpha_;
		/** �A���t�@. */
		float Alpha_;
		/** �r���{�[�h�H. */
		bool isBillboard_;
		/** �O�����������. */
		D3DXVECTOR3 ApplyForce_;
		/** �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂�. */
		float Brightness_;
		/** 0�����������A1���Z����. */
		int	AlphaBlendMode_;

	};

}// namespace nkEngine