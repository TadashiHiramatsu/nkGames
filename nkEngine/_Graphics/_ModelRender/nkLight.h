//���C�g�N���X
#pragma once

namespace nkEngine
{
	//���C�g�N���X
	class CLight
	{
	public:
		//�R���X�g���N�^
		CLight();
		//�f�X�g���N�^
		~CLight();
		
		//�f�B�t���[�Y���C�g�̌�����ݒ�
		//param[in] ���C�g�̔ԍ�
		//param[in] ���C�g�̕���
		void SetDiffuseLightDirection(int no, const D3DXVECTOR3 lightDir)
		{
			NK_ASSERT(no < LIGHT_NUM, "���C�g�̐��吙������");
			m_diffuseLightDirection[no] = lightDir;
		}

		
		//�f�B�t���[�Y���C�g�̌������擾�B
		//param[in]	���C�g�̔ԍ�
		//return	���C�g�̌���
		const D3DXVECTOR3& GetDiffuseLightDirection(int no) const
		{
			return m_diffuseLightDirection[no];
		}

		//�f�B�t���[�Y���C�g�̐F��ݒ�
		//param[in] ���C�g�̔ԍ�
		//param[in] ���C�g�̐F
		void SetDiffuseLightColor(int no, const D3DXVECTOR4 lightDir)
		{
			NK_ASSERT(no < LIGHT_NUM, "���C�g�̐F�吙������");
			m_diffuseLightColor[no] = lightDir;
		}


		//�f�B�t���[�Y���C�g�̐F���擾�B
		//param[in]	���C�g�̔ԍ�
		//return	���C�g�̐F
		const D3DXVECTOR4& GetDiffuseLightColor(int no) const
		{
			return m_diffuseLightColor[no];
		}

		//�A���r�G���g���C�g��ݒ�
		//param[in] �A���r�G���g�̐F
		void SetAmbientLight(const D3DXVECTOR3 amb)
		{
			m_ambientLight = amb;
		}

		//�A���r�G���g���C�g���擾
		//return �A���r�G���g���C�g
		const D3DXVECTOR3& GetAmbientLight()const
		{
			return m_ambientLight;
		}

	public:
		static const int LIGHT_NUM = 6;//���C�g�̐�
	private:
		D3DXVECTOR3 m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
		D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
		D3DXVECTOR3	m_ambientLight;						//����
	};

}