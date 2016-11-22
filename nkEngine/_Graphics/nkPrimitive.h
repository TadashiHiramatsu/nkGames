#pragma once

#include"nkVertexBuffer.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{
	struct SShapeVertex_PT {
		float		pos[4];
		float		uv[2];
	};

	//�v���~�e�B�u
	class CPrimitive {
	public:
		//	�v���~�e�B�u�^�C�v�B
		//�v���~�e�B�u�^�C�v
		enum EType {
			eTriangleList,		//�g���C�A���O�����X�g�B
			eTriangleStrip,		//�g���C�A���O���X�g���b�v�B
			eTypeNum,
		};

	public:
		//�R���X�g���N�^
		CPrimitive();
		//�f�X�g���N�^
		~CPrimitive();
		
		// �v���~�e�B�u�̍쐬�B
		// param[in] �v���~�e�B�u�^�C�v�B
		// param[in] ���_��
		// param[in] ���_�X�g���C�h
		// param[in] ���_���C�A�E�g�B
		// param[in] �\�[�X���_�o�b�t�@�B
		// param[in] �C���f�b�N�X�̐�
		// param[in] �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g�B
		// param[in] �\�[�X�C���f�b�N�X�o�b�t�@�B
		void Create(
			EType 					_PrimitiveType,
			int 					_NumVertex,
			int 					_VertexStride,
			const D3DVERTEXELEMENT9*	_VertexLayout,
			void*					_pSrcVertexBuffer,
			int 					_NumIndex,
			EIndexFormat			_IndexFormat,
			void*					_pSrcIndexbuffer);
		
		//���
		void Release();
		
		//���_�o�b�t�@���擾
		CVertexBuffer* GetVertexBuffer()
		{
			return &m_vertexBuffer;
		}
		
		//�C���f�b�N�X�o�b�t�@���擾
		CIndexBuffer*  GetIndexBuffer()
		{
			return &m_indexBuffer;
		}
		
		//�v���~�e�B�u�^�C�v���擾
		D3DPRIMITIVETYPE GetD3DPrimitiveType() const
		{
			return m_d3dPrimitiveType;
		}
		
		//���_�����擾
		int GetNumVertex() const
		{
			return m_numVertex;
		}
		
		//�|���S�������擾
		int GetNumPolygon() const
		{
			return m_numPolygon;
		}
		
		//���_��`���擾
		IDirect3DVertexDeclaration9* GetVertexDecl()
		{
			return m_vertexBuffer.GetVertexDecl();
		}

	private:
		int					m_numVertex;		//!<���_���B
		int					m_vertexStride;		//!<���_�X�g���C�h�B
		int					m_numIndex;			//!<�C���f�b�N�X���B
		int					m_numPolygon;		//!<�|���S���̐��B
		CVertexBuffer		m_vertexBuffer;		//!<���_�o�b�t�@�B
		CIndexBuffer		m_indexBuffer;		//!<�C���f�b�N�X�o�b�t�@�B
		//�v���~�e�B�u�^�C�v
		EType				m_type;			
		D3DPRIMITIVETYPE	m_d3dPrimitiveType;	
	};
}