/**
 * @file _Graphics\nkVertexBuffer.cpp
 *
 * 頂点バッファクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkVertexBuffer.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
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
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	VertexBuffer::~VertexBuffer()
	{
		Release();
	}

	/**
	 * 頂点バッファの作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param numVertex		   頂点数.
	 * @param stride		   頂点ストライド.
	 * @param vertexLayout	   頂点レイアウト.
	 * @param srcVertexBuffer ソース頂点バッファ。作成された頂点バッファにコピーされます。NULL指定可能.
	 */
	void VertexBuffer::Create(
		int numVertex,
		int stride,
		const D3DVERTEXELEMENT9 * vertexLayout,
		const void * srcVertexBuffer)
	{
		Release();

		//頂点数をコピー
		numVertex_ = numVertex;
		
		//頂点ストライドをコピー
		Stride_ = stride;

		//サイズを計算。頂点数 * 頂点ストライド
		Size_ = numVertex_ * Stride_;

		//デバイス取得
		IDirect3DDevice9* d3dDevice = Engine().GetDevice();

		//頂点バッファの作成
		HRESULT hr = d3dDevice->CreateVertexBuffer(
			Size_,
			0,
			0,
			D3DPOOL_DEFAULT,
			&D3DVertexBuffer_,
			NULL
		);

		NK_ASSERT(SUCCEEDED(hr), "頂点バッファ作成に失敗しました");

		//更新
		if (srcVertexBuffer != nullptr)
		{
			//ソースが指定されている
			//頂点バッファをロックしてコピー
			Update(srcVertexBuffer);
		}

		//頂点定義を作成
		d3dDevice->CreateVertexDeclaration(vertexLayout, &D3DVertexDecl_);

	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void VertexBuffer::Release()
	{
		SAFE_RELEASE(D3DVertexBuffer_);
	}

	/**
	 * 頂点バッファを更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param data ソース頂点バッファ.
	 */
	void VertexBuffer::Update(const void * data)
	{
		void* pDstVertexBuffer;
		
		//頂点バッファをロック
		HRESULT hr = D3DVertexBuffer_->Lock(0, 0, &pDstVertexBuffer, D3DLOCK_DISCARD);
		NK_ASSERT(SUCCEEDED(hr), "頂点バッファをロックできませんでした");

		//まるっとコピー
		memcpy(pDstVertexBuffer, data, Size_);
		
		//頂点バッファをアンロック
		D3DVertexBuffer_->Unlock();
	}

}// namespace nkEngine