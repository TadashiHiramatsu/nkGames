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
		//!<���C�g�r���[�̌v�Z�̎d���B
		enum EnCalcLightViewFunc {
			enCalcLightViewFunc_PositionDirection,	//���C�g�̈ʒu�ƕ����Ōv�Z����B
			enCalcLightViewFunc_PositionTarget,		//���C�g�̈ʒu�ƒ����_�Ōv�Z����B
		};
			
		//�쐬
		//param[in] ����
		//param[in] �c��
		void Create(int w, int h);

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
		const CTexture* GetTexture() const
		{
			return m_blur.GetTexture();
		}

		//���C�g�̕�����ݒ�
		void SetLightDirection(const D3DXVECTOR3& dir)
		{
			m_vLDirection = dir;
		}

		//���C�g�̎��_��ݒ�
		void SetLightPosition(const D3DXVECTOR3& pos)
		{
			m_vLPosition = pos;
		}

		//���C�g�̒����_��ݒ�
		void SetLightTarget(const D3DXVECTOR3& ter)
		{
			m_vLTarget = ter;
		}

		//���C�g�r���[�v���W�F�N�V�����s��̎擾
		D3DXMATRIX* GetLVPMatrix()
		{
			return &m_mLViewProj;
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
		bool IsActive()const
		{
			return m_isActive;
		}

		//�J������ݒ�BPSM���s���Ƃ��Ɏg�p�����
		void SetCamera(CCamera* camera)
		{
			m_camera = camera;
		}

		//���C�g�r���[�̐ݒ�̎d����ݒ�
		void SetCalcLightViewFunc(EnCalcLightViewFunc func)
		{
			m_calcLightViewFunc = func;
		}

		//�C���X�^���X�擾
		inline static CShadowMap& instance()
		{
			static CShadowMap instance;
			return instance;
		}
	private:
		//�R���X�g���N�^
		CShadowMap();
		//�f�X�g���N�^
		~CShadowMap();
	private:
		bool m_isActive; //�L���t���O	
		
		CRenderTarget m_shadowMapRT; //�V���h�E�}�b�v�p�����_�[�^�[�Q�b�g
		vector<CModelRender*> m_shadowModels; //�e���������ރ��f��
	
		D3DXVECTOR3 m_vLPosition; //���C�g�̎��_
		D3DXVECTOR3 m_vLDirection; //���C�g�̕���
		D3DXVECTOR3 m_vLTarget; //���C�g�̒����_

		D3DXMATRIX m_mLView; //���C�g�r���[�s��
		D3DXMATRIX m_mLViewProj; //���C�g�r���[�v���W�F�N�V�����s��
		D3DXMATRIX m_mProj; //�v���W�F�N�V�����s��

		EnCalcLightViewFunc	m_calcLightViewFunc; //���C�g�r���[�̌v�Z���@�B

		float m_near; //�ߕ���
		float m_far; //������
		float m_Aspect; //�A�X�y�N�g��
		float m_shadowAreaW; //�e�𗎂Ƃ��͈͂̕�
		float m_shadowAreaH; //�e�𗎂Ƃ��͈͂̍���

		CCamera* m_camera; //PSM���v�Z����Ƃ��Ɏg�p����J����

		CBlur m_blur;
	};
	inline static CShadowMap& Shadow()
	{
		return CShadowMap::instance();
	}
}