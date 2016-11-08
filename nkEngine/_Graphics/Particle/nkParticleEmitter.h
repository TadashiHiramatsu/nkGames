#pragma once

#include"nkParticle.h"

namespace nkEngine
{
	struct SParicleEmitParameter {
		//�������B
		void Init()
		{
			memset(this, 0, sizeof(SParicleEmitParameter));
			initAlpha = 1.0f;
			brightness = 1.0f;
			isBillboard = true;
		}
		const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		D3DXVECTOR3	initVelocity;						//!<�����x�B
		float		life;								//!<�����B�P�ʂ͕b�B
		float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		float		w;									//!<�p�[�e�B�N���̕��B
		float		h;									//!<�p�[�e�B�N���̍����B
		D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		D3DXVECTOR4	uvTable[4];							//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
		int			uvTableSize;						//!<UV�e�[�u���̃T�C�Y�B
		D3DXVECTOR3	gravity;							//!<�d�́B
		bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		float		initAlpha;							//!<�����A���t�@�l�B
		bool		isBillboard;						//!<�r���{�[�h�H
		float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		int			alphaBlendMode;						//!<0�����������A1���Z�����B
	};

	//�p�[�e�B�N���G�~�b�^
	class CParticleEmitter
	{
	public:
		//�R���X�g���N�^
		CParticleEmitter();

		//�f�X�g���N�^
		~CParticleEmitter();

		//������
		void Init(CCamera* _Camera, const SParicleEmitParameter& _Param, D3DXVECTOR3* _EmitPosition);

		//�X�V
		void Update();

		//�`��
		void Render();

		//�p�[�e�B�N���ɗ͂�������
		void AddForce(const D3DXVECTOR3& _AddForce);

		//���
		void Release()
		{
			std::list<CParticle*>::iterator p = particleList.begin();
			while (p != particleList.end()) {
				p = particleList.erase(p);
			}
			particleList.clear();
		}

		void SetCreate(bool _is)
		{
			isCreate = _is;
		}

	private:
		float					timer;			//!<�^�C�}�[
		CCamera*				camera;			//!<�J�����B
		SParicleEmitParameter	param;			//!<�p�����[�^�B
		D3DXVECTOR3*			EmitPosition;	//�G�~�b�^�[�̍��W�B
		std::list<CParticle*>	particleList;	//!<�p�[�e�B�N���̃��X�g�B
		CTexture m_pTextures;
		bool isCreate;
	};
}