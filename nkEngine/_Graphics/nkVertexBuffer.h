//���_�o�b�t�@
#pragma once

namespace nkEngine
{
	//���_�o�b�t�@
	class CVertexBuffer
	{
	public:
		//�R���X�g���N�^
		CVertexBuffer();
		
		//�f�X�g���N�^
		~CVertexBuffer();
		
		//���_�o�b�t�@�̍쐬
		//param[in] ���_��
		//param[in] ���_�X�g���C�h
		//param[in] ���_���C�A�E�g
		//param[in] �\�[�X���_�o�b�t�@�B�쐬���ꂽ���_�o�b�t�@�ɃR�s�[����܂��BNULL�w��\
		void Create(int numVertex, int stride, const D3DVERTEXELEMENT9* VertexLayout, const void* pSrcVertexBuffer);
	
		//���_�o�b�t�@�̊J��
		void Release();

		//IDirect3DVertexBuffer9*���擾
		//return ���_�o�b�t�@
		IDirect3DVertexBuffer9* GetBody()
		{
			return m_pVB;
		}
		
		//���_�X�g���C�h���擾
		//return ���_�X�g���C�h
		int GetStride() const
		{
			return m_stride;
		}

		//���_��`���擾
		//return ���_��`
		IDirect3DVertexDeclaration9* GetVertexDecl()
		{
			return m_pVertexDecl;
		}
	
		//���_�o�b�t�@���X�V
		//param[in] �\�[�X���_�o�b�t�@
		void Update(const void* data);
	private:
		IDirect3DVertexBuffer9* m_pVB; //���_�o�b�t�@
		IDirect3DVertexDeclaration9* m_pVertexDecl; //���_��`
		int m_stride; //���_�X�g���C�h
		int m_numVertex; //���_��
		int m_size; //�o�b�t�@�T�C�Y
	};
}