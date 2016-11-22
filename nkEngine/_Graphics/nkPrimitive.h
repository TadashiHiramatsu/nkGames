#pragma once

#include"nkVertexBuffer.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{
	struct SShapeVertex_PT {
		float		pos[4];
		float		uv[2];
	};

	//プリミティブ
	class CPrimitive {
	public:
		//	プリミティブタイプ。
		//プリミティブタイプ
		enum EType {
			eTriangleList,		//トライアングルリスト。
			eTriangleStrip,		//トライアングルストリップ。
			eTypeNum,
		};

	public:
		//コンストラクタ
		CPrimitive();
		//デストラクタ
		~CPrimitive();
		
		// プリミティブの作成。
		// param[in] プリミティブタイプ。
		// param[in] 頂点数
		// param[in] 頂点ストライド
		// param[in] 頂点レイアウト。
		// param[in] ソース頂点バッファ。
		// param[in] インデックスの数
		// param[in] インデックスバッファのフォーマット。
		// param[in] ソースインデックスバッファ。
		void Create(
			EType 					_PrimitiveType,
			int 					_NumVertex,
			int 					_VertexStride,
			const D3DVERTEXELEMENT9*	_VertexLayout,
			void*					_pSrcVertexBuffer,
			int 					_NumIndex,
			EIndexFormat			_IndexFormat,
			void*					_pSrcIndexbuffer);
		
		//解放
		void Release();
		
		//頂点バッファを取得
		CVertexBuffer* GetVertexBuffer()
		{
			return &m_vertexBuffer;
		}
		
		//インデックスバッファを取得
		CIndexBuffer*  GetIndexBuffer()
		{
			return &m_indexBuffer;
		}
		
		//プリミティブタイプを取得
		D3DPRIMITIVETYPE GetD3DPrimitiveType() const
		{
			return m_d3dPrimitiveType;
		}
		
		//頂点数を取得
		int GetNumVertex() const
		{
			return m_numVertex;
		}
		
		//ポリゴン数を取得
		int GetNumPolygon() const
		{
			return m_numPolygon;
		}
		
		//頂点定義を取得
		IDirect3DVertexDeclaration9* GetVertexDecl()
		{
			return m_vertexBuffer.GetVertexDecl();
		}

	private:
		int					m_numVertex;		//!<頂点数。
		int					m_vertexStride;		//!<頂点ストライド。
		int					m_numIndex;			//!<インデックス数。
		int					m_numPolygon;		//!<ポリゴンの数。
		CVertexBuffer		m_vertexBuffer;		//!<頂点バッファ。
		CIndexBuffer		m_indexBuffer;		//!<インデックスバッファ。
		//プリミティブタイプ
		EType				m_type;			
		D3DPRIMITIVETYPE	m_d3dPrimitiveType;	
	};
}