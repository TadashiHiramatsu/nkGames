#include"nkEngine/nkstdafx.h"
#include"nkLight.h"

namespace nkEngine
{
	CLight::CLight()
	{
		//�f�B�t���[�Y���C�g����
		m_diffuseLightDirection[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_diffuseLightDirection[1] = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		m_diffuseLightDirection[2] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_diffuseLightDirection[3] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		m_diffuseLightDirection[4] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_diffuseLightDirection[5] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//�f�B�t���[�Y���C�g�F
		m_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_diffuseLightColor[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_diffuseLightColor[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_diffuseLightColor[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_diffuseLightColor[4] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_diffuseLightColor[5] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		//�����B
		m_ambientLight = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	}
	CLight::~CLight()
	{
	}
}