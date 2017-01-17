/**
 * @file _Graphics\nkVertexBuffer.h
 *
 * ���_�o�b�t�@�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ���_�o�b�t�@�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class VertexBuffer
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		VertexBuffer();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~VertexBuffer();

		/**
		 * ���_�o�b�t�@�̍쐬. 
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param numVertex		   ���_��.
		 * @param stride		   ���_�X�g���C�h.
		 * @param vertexLayout	   ���_���C�A�E�g.
		 * @param srcVertexBuffer �\�[�X���_�o�b�t�@�B�쐬���ꂽ���_�o�b�t�@�ɃR�s�[����܂��BNULL�w��\.
		 */
		void Create(int numVertex, int stride, const D3DVERTEXELEMENT9* vertexLayout, const void* srcVertexBuffer);

		/**
		 * ���_�o�b�t�@�̊J��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * ���_�o�b�t�@���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the body.
		 */
		IDirect3DVertexBuffer9* GetBody()
		{
			return D3DVertexBuffer_;
		}

		/**
		 * ���_�X�g���C�h���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The stride.
		 */
		int GetStride() const
		{
			return Stride_;
		}

		/**
		 * ���_��`���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the vertex declaration.
		 */
		IDirect3DVertexDeclaration9* GetVertexDecl()
		{
			return D3DVertexDecl_;
		}

		/**
		 * ���_�o�b�t�@���X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param data �\�[�X���_�o�b�t�@.
		 */
		void Update(const void* data);

	private:

		/** ���_�o�b�t�@. */
		IDirect3DVertexBuffer9* D3DVertexBuffer_;
		/** ���_��`. */
		IDirect3DVertexDeclaration9* D3DVertexDecl_;
		/** ���_�X�g���C�h. */
		int Stride_;
		/** ���_��. */
		int numVertex_;
		/** �o�b�t�@�T�C�Y. */
		int Size_;
	};

}// namespace nkEngine