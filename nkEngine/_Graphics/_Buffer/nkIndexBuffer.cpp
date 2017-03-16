/**
 * @file _Graphics\_Buffer\nkIndexBuffer.cpp
 *
 * インデックスバッファクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	IndexBuffer::IndexBuffer() :
		D3DIndexBuffer_(nullptr)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	IndexBuffer::~IndexBuffer()
	{
		Release();
	}

	/**
	 * インデックスバッファの作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param indexNum		 インデックスの数.
	 * @param format		 インデックスバッファのフォーマット.
	 * @param srcIndexBuffer ソースインデックスバッファ.
	 */
	void IndexBuffer::Create(int indexNum, IndexFormatE format, const void* srcIndexBuffer)
	{
		//解放
		Release();

		//サイズの作成
		int size = 0;

		//フォーマットの作成
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

		//デバイスの取得
		LPDIRECT3DDEVICE9 Device = Engine().GetDevice();

		//インデックスバッファの作成
		HRESULT hr = Device->CreateIndexBuffer(
			size,
			0,
			(D3DFORMAT)d3dFormat,
			D3DPOOL_DEFAULT,
			&D3DIndexBuffer_,
			nullptr
		);

		NK_ASSERT(SUCCEEDED(hr), "インデックスバッファの作成失敗");

		if (srcIndexBuffer != nullptr)
		{
			//ソースが指定されている
			//インデックスバッファをロックしてコピー
			void* pDstIndexBuffer;

			//インデックスバッファをロック
			hr = D3DIndexBuffer_->Lock(0, 0, &pDstIndexBuffer, D3DLOCK_DISCARD);

			NK_ASSERT(SUCCEEDED(hr), "インデックスバッファのロックに失敗");

			//コピー
			memcpy(pDstIndexBuffer, srcIndexBuffer, size);

			//インデックスバッファをアンロック
			D3DIndexBuffer_->Unlock();
		}
	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void IndexBuffer::Release()
	{
		SAFE_RELEASE(D3DIndexBuffer_);
	}

}// namespace nkEngine