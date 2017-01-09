/**
 * @file _Graphics\nkVertexBuffer.cpp
 *
 * ���_�o�b�t�@�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkVertexBuffer.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	VertexBuffer::VertexBuffer() :
		D3DVertexBuffer_(nullptr),
		Stride_(0),
		numVertex_(0),
		Size_(0)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	VertexBuffer::~VertexBuffer()
	{
		Release();
	}

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
	void VertexBuffer::Create(
		int numVertex,
		int stride,
		const D3DVERTEXELEMENT9 * vertexLayout,
		const void * srcVertexBuffer)
	{
		Release();

		//���_�����R�s�[
		numVertex_ = numVertex;
		
		//���_�X�g���C�h���R�s�[
		Stride_ = stride;

		//�T�C�Y���v�Z�B���_�� * ���_�X�g���C�h
		Size_ = numVertex_ * Stride_;

		//�f�o�C�X�擾
		IDirect3DDevice9* d3dDevice = Engine().GetDevice();

		//���_�o�b�t�@�̍쐬
		HRESULT hr = d3dDevice->CreateVertexBuffer(
			Size_,
			0,
			0,
			D3DPOOL_DEFAULT,
			&D3DVertexBuffer_,
			NULL
		);

		NK_ASSERT(SUCCEEDED(hr), "���_�o�b�t�@�쐬�Ɏ��s���܂���");

		//�X�V
		if (srcVertexBuffer != nullptr)
		{
			//�\�[�X���w�肳��Ă���
			//���_�o�b�t�@�����b�N���ăR�s�[
			Update(srcVertexBuffer);
		}

		//���_��`���쐬
		d3dDevice->CreateVertexDeclaration(vertexLayout, &D3DVertexDecl_);

	}

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void VertexBuffer::Release()
	{
		SAFE_RELEASE(D3DVertexBuffer_);
	}

	/**
	 * ���_�o�b�t�@���X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param data �\�[�X���_�o�b�t�@.
	 */
	void VertexBuffer::Update(const void * data)
	{
		void* pDstVertexBuffer;
		
		//���_�o�b�t�@�����b�N
		HRESULT hr = D3DVertexBuffer_->Lock(0, 0, &pDstVertexBuffer, D3DLOCK_DISCARD);
		NK_ASSERT(SUCCEEDED(hr), "���_�o�b�t�@�����b�N�ł��܂���ł���");

		//�܂���ƃR�s�[
		memcpy(pDstVertexBuffer, data, Size_);
		
		//���_�o�b�t�@���A�����b�N
		D3DVertexBuffer_->Unlock();
	}

}// namespace nkEngine