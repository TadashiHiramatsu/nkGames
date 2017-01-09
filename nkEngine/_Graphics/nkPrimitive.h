/**
 * @file	_Graphics\nkPrimitive.h
 *
 * �v���~�e�B�u�N���X�̒�`
 */
#pragma once

#include"nkVertexBuffer.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{

	/**
	 * �v���~�e�B�u�N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class Primitive
	{
	public:

		/** �v���~�e�B�u�^�C�v. */
		enum TypeE {
			TriangleList,	//!< �g���C�A���O�����X�g�B
			TriangleStrip,  //!< �g���C�A���O���X�g���b�v�B
		    TypeNum,		//!< �^�C�v�̐�
		};

	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		Primitive();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~Primitive();

		/**
		 * �쐬.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/07
		 *
		 * @param 		   primitiveType   �v���~�e�B�u�^�C�v.
		 * @param 		   numVertex	   ���_��.
		 * @param 		   vertexStride    ���_�X�g���C�h.
		 * @param 		   vertexLayout    ���_���C�A�E�g.
		 * @param [in,out] srcVertexBuffer �\�[�X���_�o�b�t�@.
		 * @param 		   numIndex		   �C���f�b�N�X�̐�.
		 * @param 		   indexFormat	   �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g.
		 * @param [in,out] srcIndexbuffer  �\�[�X�C���f�b�N�X�o�b�t�@.
		 */
		void Create(
			TypeE 						primitiveType,
			int 						numVertex,
			int 						vertexStride,
			const D3DVERTEXELEMENT9*	vertexLayout,
			void*						srcVertexBuffer,
			int 						numIndex,
			IndexFormatE				indexFormat,
			void*						srcIndexbuffer
		);
		
		/**
		 * ���.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Release();
		
		/**
		 * ���_�o�b�t�@���擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the vertex buffer.
		 */
		VertexBuffer* GetVertexBuffer()
		{
			return &VertexBuffer_;
		}
		
		/**
		 * �C���f�b�N�X�o�b�t�@���擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the index buffer.
		 */
		IndexBuffer*  GetIndexBuffer()
		{
			return &IndexBuffer_;
		}
		
		/**
		 * �v���~�e�B�u�^�C�v���擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The d 3D primitive type.
		 */
		D3DPRIMITIVETYPE GetD3DPrimitiveType() const
		{
			return D3DPrimitiveType_;
		}
		
		/**
		 * ���_�����擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The number vertex.
		 */
		int GetNumVertex() const
		{
			return numVertex_;
		}
		
		/**
		 * �|���S�������擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The number polygon.
		 */
		int GetNumPolygon() const
		{
			return numPolygon_;
		}
		
		/**
		 * ���_��`���擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the vertex declaration.
		 */
		IDirect3DVertexDeclaration9* GetVertexDecl()
		{
			return VertexBuffer_.GetVertexDecl();
		}

	private:
		
		/** ���_��. */
		int	numVertex_;
		/** ���_�X�g���C�h. */
		int	VertexStride_;
		/** �C���f�b�N�X��. */
		int	numIndex_;
		/** �|���S���̐�. */
		int	numPolygon_;
		/** ���_�o�b�t�@. */
		VertexBuffer VertexBuffer_;
		/** �C���f�b�N�X�o�b�t�@. */
		IndexBuffer IndexBuffer_;
		/** �v���~�e�B�u�^�C�v. */
		TypeE Type_;			
		/** Type of the 3D primitive. */
		D3DPRIMITIVETYPE D3DPrimitiveType_;	

	};

}// namespace nkEngine