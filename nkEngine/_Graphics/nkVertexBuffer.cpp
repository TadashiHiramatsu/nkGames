#include"nkEngine/nkstdafx.h"
#include"nkVertexBuffer.h"

namespace nkEngine
{
	CVertexBuffer::CVertexBuffer() :
		m_pVB(nullptr),
		m_stride(0),
		m_numVertex(0),
		m_size(0)
	{
	}

	CVertexBuffer::~CVertexBuffer()
	{
		Release();
	}

	void CVertexBuffer::Create(
		int numVertex,
		int stride,
		const D3DVERTEXELEMENT9 * VertexLayout,
		const void * pSrcVertexBuffer)
	{
		Release();

		m_numVertex = numVertex;
		m_stride = stride;
		m_size = m_numVertex * m_stride;

		IDirect3DDevice9* d3dDevice = Engine().GetDevice();

		HRESULT hr = d3dDevice->CreateVertexBuffer(
			m_size,
			0,
			0,
			D3DPOOL_DEFAULT,
			&m_pVB,
			NULL
		);

		NK_ASSERT(SUCCEEDED(hr), "頂点バッファ作成に失敗しました");

		if (pSrcVertexBuffer != nullptr)
		{
			//ソースが指定されている
			//頂点バッファをロックしてコピー
			Update(pSrcVertexBuffer);
		}

		//頂点定義を作成
		d3dDevice->CreateVertexDeclaration(VertexLayout, &m_pVertexDecl);

	}

	void CVertexBuffer::Release()
	{
		SAFE_RELEASE(m_pVB);
	}

	void CVertexBuffer::Update(const void * data)
	{
		void* pDstVertexBuffer;

		HRESULT hr = m_pVB->Lock(0, 0, &pDstVertexBuffer, D3DLOCK_DISCARD);
		NK_ASSERT(SUCCEEDED(hr), "頂点バッファをロックできませんでした");

		//まるっとコピー
		memcpy(pDstVertexBuffer, data, m_size);
		
		m_pVB->Unlock();
	}

}