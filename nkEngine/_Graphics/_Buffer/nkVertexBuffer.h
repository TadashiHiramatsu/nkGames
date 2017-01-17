/**
 * @file _Graphics\nkVertexBuffer.h
 *
 * 頂点バッファクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * 頂点バッファクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class VertexBuffer
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		VertexBuffer();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~VertexBuffer();

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
		void Create(int numVertex, int stride, const D3DVERTEXELEMENT9* vertexLayout, const void* srcVertexBuffer);

		/**
		 * 頂点バッファの開放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * 頂点バッファを取得.
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
		 * 頂点ストライドを取得.
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
		 * 頂点定義を取得.
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
		 * 頂点バッファを更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param data ソース頂点バッファ.
		 */
		void Update(const void* data);

	private:

		/** 頂点バッファ. */
		IDirect3DVertexBuffer9* D3DVertexBuffer_;
		/** 頂点定義. */
		IDirect3DVertexDeclaration9* D3DVertexDecl_;
		/** 頂点ストライド. */
		int Stride_;
		/** 頂点数. */
		int numVertex_;
		/** バッファサイズ. */
		int Size_;
	};

}// namespace nkEngine