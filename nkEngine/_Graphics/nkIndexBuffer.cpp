#include"nkEngine/nkstdafx.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{
	CIndexBuffer::CIndexBuffer():
		pIndexBuffer(nullptr)
	{
	}

	CIndexBuffer::~CIndexBuffer()
	{
		Release();
	}

	void CIndexBuffer::Create(int _IndexNum, EIndexFormat _Format, const void * _pSrcIndexBuffer)
	{
		Release();

		int size = 0;
		D3DFORMAT d3dFormat;
		if (_Format == eIndexFormat16)
		{
			d3dFormat = D3DFMT_INDEX16;
			size = _IndexNum * 2;
		}
		else if (_Format == eIndexFormat32)
		{
			d3dFormat = D3DFMT_INDEX32;
			size = _IndexNum * 4;
		}

		LPDIRECT3DDEVICE9 Device = Engine().GetDevice();

		HRESULT hr = Device->CreateIndexBuffer(
			size,
			0,
			(D3DFORMAT)d3dFormat,
			D3DPOOL_DEFAULT,
			&pIndexBuffer,
			nullptr
		);

		NK_ASSERT(SUCCEEDED(hr), "Failed CreateIndexBuffer!!");

		if (_pSrcIndexBuffer != nullptr)
		{
			//ソースが指定されている
			//インデックスバッファをロックしてコピー
			void* pDstIndexBuffer;
			hr = pIndexBuffer->Lock(0, 0, &pDstIndexBuffer, D3DLOCK_DISCARD);
			NK_ASSERT(SUCCEEDED(hr), "Failed IndexBuffer Lock!!");
			//コピー
			memcpy(pDstIndexBuffer, _pSrcIndexBuffer, size);
			pIndexBuffer->Unlock();
		}
	}

	void CIndexBuffer::Release()
	{
		SAFE_RELEASE(pIndexBuffer);
	}
}