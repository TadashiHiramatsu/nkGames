/**
 * @file _Graphics\_Buffer\nkIndexBuffer.cpp
 *
 * �C���f�b�N�X�o�b�t�@�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	IndexBuffer::IndexBuffer() :
		D3DIndexBuffer_(nullptr)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	IndexBuffer::~IndexBuffer()
	{
		Release();
	}

	/**
	 * �C���f�b�N�X�o�b�t�@�̍쐬.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param indexNum		 �C���f�b�N�X�̐�.
	 * @param format		 �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g.
	 * @param srcIndexBuffer �\�[�X�C���f�b�N�X�o�b�t�@.
	 */
	void IndexBuffer::Create(int indexNum, IndexFormatE format, const void* srcIndexBuffer)
	{
		//���
		Release();

		//�T�C�Y�̍쐬
		int size = 0;

		//�t�H�[�}�b�g�̍쐬
		D3DFORMAT d3dFormat;

		switch (format)
		{
		case IndexFormatE::IndexFormat16:
			d3dFormat = D3DFMT_INDEX16;
			size = indexNum * 2;
			break;
		case IndexFormatE::IndexFormat32:
			d3dFormat = D3DFMT_INDEX32;
			size = indexNum * 4;
			break;
		default:
			break;
		}

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 Device = Engine().GetDevice();

		//�C���f�b�N�X�o�b�t�@�̍쐬
		HRESULT hr = Device->CreateIndexBuffer(
			size,
			0,
			(D3DFORMAT)d3dFormat,
			D3DPOOL_DEFAULT,
			&D3DIndexBuffer_,
			nullptr
		);

		NK_ASSERT(SUCCEEDED(hr), "�C���f�b�N�X�o�b�t�@�̍쐬���s");

		if (srcIndexBuffer != nullptr)
		{
			//�\�[�X���w�肳��Ă���
			//�C���f�b�N�X�o�b�t�@�����b�N���ăR�s�[
			void* pDstIndexBuffer;

			//�C���f�b�N�X�o�b�t�@�����b�N
			hr = D3DIndexBuffer_->Lock(0, 0, &pDstIndexBuffer, D3DLOCK_DISCARD);

			NK_ASSERT(SUCCEEDED(hr), "�C���f�b�N�X�o�b�t�@�̃��b�N�Ɏ��s");

			//�R�s�[
			memcpy(pDstIndexBuffer, srcIndexBuffer, size);

			//�C���f�b�N�X�o�b�t�@���A�����b�N
			D3DIndexBuffer_->Unlock();
		}
	}

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void IndexBuffer::Release()
	{
		SAFE_RELEASE(D3DIndexBuffer_);
	}

}// namespace nkEngine