#pragma once

#include"../modelRender/nkSkinModel.h"
#include"..\nkCamera.h"
#include"..\nkBlur.h"

namespace nkEngine
{

	class CCamera;

	class CShadowMap
	{
	public:

		//�V���h�E�}�b�v�̐�
		static const int MAX_SHADOW_MAP = 3;

		//�V���h�E���V�[�o�[�p�̃p�����[�^
		struct SShadowReceiverParam
		{
			D3DXMATRIX mLightViewProjection[MAX_SHADOW_MAP]; //���C�g�r���[�}�g���N�X
			bool vsmFlag; //�o���A���X�V���h�E�}�b�v���s�����̃t���O
			int numShadowMap; //�V���h�E�}�b�v�̖���
		};

		//���C�g�r���[�̌v�Z�̎d���B
		enum EnCalcLightViewFunc {
			enCalcLightViewFunc_PositionDirection,	//���C�g�̈ʒu�ƕ����Ōv�Z����B
			enCalcLightViewFunc_PositionTarget,		//���C�g�̈ʒu�ƒ����_�Ōv�Z����B
		};

		//�쐬
		//param[in] �R���t�B�O
		void Create(const SShadowConfig& config);

		//�X�V
		void Update();

		//�`��
		void Render();

		//�J��
		void Release();

		//���f�����G���g���[
		//param[in] ���f��
		void Entry(CModelRender* SkinModel);

		//�e�N�X�`�����擾
		//param[in] �e�N�X�`���[�i���o�[
		const CTexture* GetTexture(int texNumber) const
		{
			return m_blur[texNumber].GetTexture();
			//return m_shadowMapRT[texNumber].GetTexture();
		}

		//���C�g�̕�����ݒ�
		void SetLightDirection(const D3DXVECTOR3& dir)
		{
			m_vLightDirection = dir;
		}

		//���C�g�̎��_��ݒ�
		void SetLightPosition(const D3DXVECTOR3& pos)
		{
			m_vLightPosition = pos;
		}

		//���C�g�̒����_��ݒ�
		void SetLightTarget(const D3DXVECTOR3& ter)
		{
			m_vLightTarget = ter;
		}

		//�ߕ��ʂ��擾
		float GetNear() const
		{
			return m_near;
		}

		//�ߕ��ʂ�ݒ�
		void SetNear(float fnear)
		{
			m_near = fnear;
		}

		//�����ʂ��擾
		float GetFar() const
		{
			return m_far;
		}

		//�����ʂ�ݒ�
		void SetFar(float ffar)
		{
			m_far = ffar;
		}

		//�L���t���O�̎擾
		bool isEnable()const
		{
			return m_isEnable;
		}

		//���C�g�r���[�̐ݒ�̎d����ݒ�
		void SetCalcLightViewFunc(EnCalcLightViewFunc func)
		{
			m_calcLightViewFunc = func;
		}

		//�C���X�^���X�擾
		inline static CShadowMap& GetInstance()
		{
			static CShadowMap instance;
			return instance;
		}

		//�V���h�E���V�[�o�[�p�̃p�����[�^���擾
		//return �V���h�E���V�[�o�[�p�̃p�����[�^
		const SShadowReceiverParam& GetShadowReceiverParam()
		{
			return m_shadowReceiverParam;
		}

		//���C�g�r���[�v���W�F�N�V�����s��̎擾
		const D3DXMATRIX& GetLightViewProjectionMatrix() const
		{
			return m_mLightViewProjection;
		}

	private:
		//�R���X�g���N�^
		CShadowMap();
		//�f�X�g���N�^
		~CShadowMap();
	private:
		bool m_isEnable; //�L���t���O	

		CRenderTarget m_shadowMapRT[MAX_SHADOW_MAP]; //�V���h�E�}�b�v�p�����_�[�^�[�Q�b�g
		vector<CModelRender*> m_shadowModels; //�e���������ރ��f��

		D3DXVECTOR3 m_vLightPosition; //���C�g�̎��_
		D3DXVECTOR3 m_vLightDirection; //���C�g�̕���
		D3DXVECTOR3 m_vLightTarget; //���C�g�̒����_

		D3DXMATRIX m_mLightView; //���C�g�r���[�s��
		D3DXMATRIX m_mProjection; //�v���W�F�N�V�����s��
		D3DXMATRIX m_mLightViewProjection; //���C�g�r���[�v���W�F�N�V�����s��

		EnCalcLightViewFunc	m_calcLightViewFunc; //���C�g�r���[�̌v�Z���@�B

		float m_near; //�ߕ���
		float m_far; //������
		float m_Aspect; //�A�X�y�N�g��
		float m_shadowAreaW[MAX_SHADOW_MAP]; //�e�𗎂Ƃ��͈͂̕�
		float m_shadowAreaH[MAX_SHADOW_MAP]; //�e�𗎂Ƃ��͈͂̍���

		CBlur m_blur[MAX_SHADOW_MAP]; //�u���[�����N���X
		SShadowReceiverParam m_shadowReceiverParam; //�V���h�E���V�[�o�[�p�̃p�����[�^
	};

	inline static CShadowMap& Shadow()
	{
		return CShadowMap::GetInstance();
	}
}