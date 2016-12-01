//�p�[�e�B�N���{��
#pragma once

#define PI 3.14159265358979323846f

namespace nkEngine
{
	struct SParicleEmitParameter;

	class CParticle
	{
	public:
		enum eState {
			eStateRun,
			eStateFadeOut,
			eStateDead,
		};
	public:
		//�R���X�g���N�^
		CParticle();
		//�f�X�g���N�^
		~CParticle();
		
		//������
		void Init(CCamera* camera, const SParicleEmitParameter& param,D3DXVECTOR3* emitPosition);
		
		//�X�V
		void Update();

		//�`��
		void Render(IDirect3DTexture9* _pTextures);


		void AddForce(const D3DXVECTOR3 _AddForce)
		{
			this->applyForce = _AddForce;
		}

		bool GetDead() { return isDead; }
	private:
		//�v���~�e�B�u
		CPrimitive primitive; 
		//�V�F�[�_�[�G�t�F�N�g
		ID3DXEffect* Effect;
		CCamera* camera;

		D3DXMATRIX		mWorld;	//���[���h�s��B
		D3DXVECTOR3		vScale;
		D3DXMATRIX		mScale;	//�X�P�[���s��

		float			life;						//!<���C�t�B
		float			timer;						//!<�^�C�}�[�B
		D3DXVECTOR3		velocity;					//!<���x�B
		D3DXVECTOR3		position;					//!<���W�B
		D3DXVECTOR3		gravity;					//!<�d�́B
		float			rotateZ;					//!<Z������̉�]�B
		D3DXVECTOR3		addVelocityRandomMargih;	//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		bool			isDead;						//!<���S�t���O�B
		bool			isFade;						//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		float			fadeTIme;					//!<�t�F�[�h�̎��ԁB
		eState			state;						//!<��ԁB
		float			initAlpha;					//!<�����A���t�@�B
		float			alpha;						//!<�A���t�@�B
		bool			isBillboard;				//!<�r���{�[�h�H
		D3DXVECTOR3		applyForce;					//!<�O����������́B
		float			brightness;					//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		int				alphaBlendMode;				//!<0�����������A1���Z�����B
	};

}