#pragma once

namespace nkEngine
{
	enum EIndexFormat
	{
		eIndexFormat16 = D3DFMT_INDEX16, //16bit�C���f�b�N�X
		eIndexFormat32 = D3DFMT_INDEX32, //32bit�C���f�b�N�X
	};
	class CIndexBuffer
	{
	public:
		//�R���X�g���N�^
		CIndexBuffer();
		
		//�f�X�g���N�^
		~CIndexBuffer();

		//�C���f�b�N�X�o�b�t�@�̍쐬
		// param[in] �C���f�b�N�X�̐�
		// param[in] �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
		// param[in] �\�[�X�C���f�b�N�X�o�b�t�@
		void Create(int _IndexNum, EIndexFormat _Format, const void* _pSrcIndexBuffer);

		//�C���f�b�N�X�o�b�t�@�̉��
		void Release();

		//�C���f�b�N�X�o�b�t�@�̎擾
		IDirect3DIndexBuffer9* GetBody()
		{
			return pIndexBuffer;
		}

	private:
		//�C���f�b�N�X�o�b�t�@
		IDirect3DIndexBuffer9* pIndexBuffer;
	};
}