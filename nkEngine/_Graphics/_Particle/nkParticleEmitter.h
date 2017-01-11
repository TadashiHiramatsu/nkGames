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
	struct ParicleParameterS 
	{
	public:

		/** �e�N�X�`���̃t�@�C���p�X. */
		const char* TexturePath_;
		/** �����x. */
		D3DXVECTOR3	InitVelocity_;
		/** �����B�P�ʂ͕b. */
		float		Life_;
		/** �������ԁB�P�ʂ͕b. */
		float		IntervalTime_;
		/** �p�[�e�B�N���̕�. */
		float		W_;
		/** �p�[�e�B�N���̍���. */
		float		H_;
		/** �����ʒu�̃����_����. */
		D3DXVECTOR3	InitPositionRandomMargin_;
		/** �����x�̃����_����. */
		D3DXVECTOR3	InitVelocityVelocityRandomMargin_;
		/** ���x�̐ϕ��̂Ƃ��̃����_����. */
		D3DXVECTOR3	AddVelocityRandomMargih_;
		/** UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�. */
		D3DXVECTOR4	UVTable_[4];
		/** UV�e�[�u���̃T�C�Y. */
		int			UVTableSize_;
		/** �d��. */
		D3DXVECTOR3	Gravity_;
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
	class ParticleEmitter
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		ParticleEmitter();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~ParticleEmitter();

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
		 */
		void Render();

		/**
		 * �p�[�e�B�N���ɗ͂�������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param addForce The add force.
		 */
		void AddForce(const D3DXVECTOR3& addForce);

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release()
		{
			auto p = ParticleList_.begin();

			while (p != ParticleList_.end())
			{
				p = ParticleList_.erase(p);
			}

			ParticleList_.clear();
		
		}

		/**
		 * Sets a create.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param _is True to is.
		 */
		void SetCreate(bool isCreate)
		{
			isCreate_ = isCreate;
		}

	private:

		/** �^�C�}�[. */
		float Timer_;
		/** �J����. */
		Camera*	Camera_;
		/** �p�����[�^. */
		ParicleParameterS Param_;
		/** �G�~�b�^�[�̍��W. */
		D3DXVECTOR3* EmitPosition_;
		/** �p�[�e�B�N���̃��X�g. */
		list<Particle*>	ParticleList_;
		/** The texture. */
		Texture Texture_;
		/** �쐬���邩. */
		bool isCreate_;
	
	};
}