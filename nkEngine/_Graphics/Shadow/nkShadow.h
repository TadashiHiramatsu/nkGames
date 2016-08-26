#pragma once

#include"../modelRender/nkSkinModel.h"

namespace nkEngine
{

	class CShadowMap
	{
	public:
		
		~CShadowMap() {
			Release();
		}
		void Create(int w, int h,bool Active);
		void CreateLight();
		void Draw(D3DXMATRIX);
		void Release();
		void Entry(CModelRender* SkinModel);
		D3DXMATRIX* GetLVPMatrix()
		{
			return &m_LVPMatrix;
		}
		D3DXMATRIX* GetVPMatrix()
		{
			return &m_VPMatrix;
		}

		void SetLightPosition(D3DXVECTOR3 pos)
		{
			m_lightPosition = pos;
		}

		void SetLightDirection(D3DXVECTOR3 Dir)
		{
			m_lightDirection = Dir;
		}
		void SetEffect(ID3DXEffect* effect)
		{
			m_pEffect = effect;
		}
		/*!
		* @brief	�ߕ��ʁB
		*/
		float GetNear() const
		{
			return m_near;
		}
		/*!
		* @brief	������
		*/
		float GetFar() const
		{
			return m_far;
		}
		//�e�N�X�`���Q�b�g
		IDirect3DTexture9* GetTexture()
		{
			return m_shadowMapRT.GetTexture();
		}
		//�L����
		bool GetActive()
		{
			return m_isActive;
		}
		//�C���X�^���X�擾
		inline static CShadowMap& instance()
		{
			static CShadowMap instance;
			return instance;
		}
	private:
		CShadowMap():
			m_isActive(false),
			m_pEffect(nullptr),
			w(0),h(0),
			m_near(0.0f),m_far(0.0f)
		{
			m_lightPosition = D3DXVECTOR3(0, 0, 0);
			m_lightDirection = D3DXVECTOR3(0, 0, 0);
		}
		D3DVIEWPORT9       m_viewport;  // �e�N�X�`���̃r���[�|�[�g
		LPDIRECT3DSURFACE9 m_Backbuffer;
		LPDIRECT3DSURFACE9 m_BackZ;
		int w, h;

		CRenderTarget m_shadowMapRT;
		std::vector<CModelRender*> m_shadowModels;

		D3DXVECTOR3 m_lightPosition;
		D3DXVECTOR3 m_lightDirection;
		D3DXMATRIX m_lvMatrix;
		D3DXMATRIX m_LVPMatrix;
		D3DXMATRIX m_projMatrix;
		D3DXMATRIX m_VPMatrix;
		ID3DXEffect* m_pEffect;
		float						m_near;				//!<�ߕ��ʁB
		float						m_far;				//!<�����ʁB

		bool m_isActive;//�L���t���O
	};
	inline static CShadowMap& Shadow()
	{
		return CShadowMap::instance();
	}
}