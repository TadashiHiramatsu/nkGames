/**
 * @file _Graphics\_ModelRender\nkLight.cpp
 *
 * ���C�g�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkLight.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Light::Light()
	{
		//�f�B�t���[�Y���C�g����
		DiffuseLightDirection_[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		DiffuseLightDirection_[1] = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		DiffuseLightDirection_[2] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		DiffuseLightDirection_[3] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		DiffuseLightDirection_[4] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		DiffuseLightDirection_[5] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//�f�B�t���[�Y���C�g�F
		DiffuseLightColor_[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[4] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[5] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		//�����̐ݒ�
		AmbientLight_ = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
		
		//���Ȕ����F�̐ݒ�
		EmissionLightColor_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	}

}// namespace nkEngine