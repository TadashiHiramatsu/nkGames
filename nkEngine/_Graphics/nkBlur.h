//�u���[
#pragma once

namespace nkEngine
{

	class CBlur
	{
	public:
		//�R���X�g���N�^
		CBlur();
		
		//�f�X�g���N�^
		~CBlur();
		
		//������
		//param[in] ����
		//param[in] �c��
		//param[in] ���ƂȂ�e�N�X�`��
		void Init(int w,int h,const CTexture& srcTexture);
		//�`��
		void Render();

		//�e�N�X�`�����擾
		const CTexture* GetTexture()const
		{
			return m_rt[1].GetTexture();
		}

		int GetSizeW()
		{
			return m_srcTexWH[0];
		}

		int GetSizeH()
		{
			return m_srcTexWH[1];
		}

	private:
		CRenderTarget m_rt[2]; //�K�E�V�A���u���[�̌��ʂ�`�����ރ����_�����O�^�[�Q�b�g
		const CTexture*	m_srcTexture; //�\�[�X�ƂȂ�e�N�X�`��
		ID3DXEffect* m_Effect; //�G�t�F�N�g
		int m_srcTexWH[2]; //�e�N�X�`���̕�
		CSprite m_fullscreen;
	};
}