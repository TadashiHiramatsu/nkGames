//頂点バッファ
#pragma once

namespace nkEngine
{
	//頂点バッファ
	class CVertexBuffer
	{
	public:
		//コンストラクタ
		CVertexBuffer();
		
		//デストラクタ
		~CVertexBuffer();
		
		//頂点バッファの作成
		//param[in] 頂点数
		//param[in] 頂点ストライド
		//param[in] 頂点レイアウト
		//param[in] ソース頂点バッファ。作成された頂点バッファにコピーされます。NULL指定可能
		void Create(int numVertex, int stride, const D3DVERTEXELEMENT9* VertexLayout, const void* pSrcVertexBuffer);
	
		//頂点バッファの開放
		void Release();

		//IDirect3DVertexBuffer9*を取得
		//return 頂点バッファ
		IDirect3DVertexBuffer9* GetBody()
		{
			return m_pVB;
		}
		
		//頂点ストライドを取得
		//return 頂点ストライド
		int GetStride() const
		{
			return m_stride;
		}

		//頂点定義を取得
		//return 頂点定義
		IDirect3DVertexDeclaration9* GetVertexDecl()
		{
			return m_pVertexDecl;
		}
	
		//頂点バッファを更新
		//param[in] ソース頂点バッファ
		void Update(const void* data);
	private:
		IDirect3DVertexBuffer9* m_pVB; //頂点バッファ
		IDirect3DVertexDeclaration9* m_pVertexDecl; //頂点定義
		int m_stride; //頂点ストライド
		int m_numVertex; //頂点数
		int m_size; //バッファサイズ
	};
}