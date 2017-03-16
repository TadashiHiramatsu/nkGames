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
		DiffuseLightDirection_[0] = Vector3::Zero;
		DiffuseLightDirection_[1] = Vector3::Zero;
		DiffuseLightDirection_[2] = Vector3::Zero;
		DiffuseLightDirection_[3] = Vector3::Zero;
		DiffuseLightDirection_[4] = Vector3::Zero;
		DiffuseLightDirection_[5] = Vector3::Zero;

		//�f�B�t���[�Y���C�g�F
		DiffuseLightColor_[0] = Vector4::Zero;
		DiffuseLightColor_[1] = Vector4::Zero;
		DiffuseLightColor_[2] = Vector4::Zero;
		DiffuseLightColor_[3] = Vector4::Zero;
		DiffuseLightColor_[4] = Vector4::Zero;
		DiffuseLightColor_[5] = Vector4::Zero;

		//�����̐ݒ�
		AmbientLight_ = Vector3(0.2f, 0.2f, 0.2f);
		
		//���Ȕ����F�̐ݒ�
		EmissionLightColor_ = Vector3::Zero;
	
	}

}// namespace nkEngine