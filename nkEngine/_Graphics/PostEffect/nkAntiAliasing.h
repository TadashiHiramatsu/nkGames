//�A���`�G�C���A�V���O
#pragma once

namespace nkEngine
{

	//�|�X�g�G�t�F�N�g�ɂ��A���`�G�C���A�X
	class CAntiAliasing
	{
	public:

		//�R���X�g���N�^
		CAntiAliasing();

		//�f�X�g���N�^
		~CAntiAliasing();
		
		//������
		void Init();

		//�`�� 
		void Render();

		//���
		void Release();

	private:
		bool m_isEnable; //�L���t���O
		ID3DXEffect* m_effect; //�G�t�F�N�g

		float texSize[2];

		CSprite full;
	};
}