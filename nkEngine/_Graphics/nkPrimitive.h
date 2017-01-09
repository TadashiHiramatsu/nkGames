/**
 * @file	_Graphics\nkPrimitive.h
 *
 * プリミティブクラスの定義
 */
#pragma once

#include"nkVertexBuffer.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{

	/**
	 * プリミティブクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class Primitive
	{
	public:

		/** プリミティブタイプ. */
		enum TypeE {
			TriangleList,	//!< トライアングルリスト。
			TriangleStrip,  //!< トライアングルストリップ。
		    TypeNum,		//!< タイプの数
		};

	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		Primitive();

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~Primitive();

		/**
		 * 作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/07
		 *
		 * @param 		   primitiveType   プリミティブタイプ.
		 * @param 		   numVertex	   頂点数.
		 * @param 		   vertexStride    頂点ストライド.
		 * @param 		   vertexLayout    頂点レイアウト.
		 * @param [in,out] srcVertexBuffer ソース頂点バッファ.
		 * @param 		   numIndex		   インデックスの数.
		 * @param 		   indexFormat	   インデックスバッファのフォーマット.
		 * @param [in,out] srcIndexbuffer  ソースインデックスバッファ.
		 */
		void Create(
			TypeE 						primitiveType,
			int 						numVertex,
			int 						vertexStride,
			const D3DVERTEXELEMENT9*	vertexLayout,
			void*						srcVertexBuffer,
			int 						numIndex,
			IndexFormatE				indexFormat,
			void*						srcIndexbuffer
		);
		
		/**
		 * 解放.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Release();
		
		/**
		 * 頂点バッファを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the vertex buffer.
		 */
		VertexBuffer* GetVertexBuffer()
		{
			return &VertexBuffer_;
		}
		
		/**
		 * インデックスバッファを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the index buffer.
		 */
		IndexBuffer*  GetIndexBuffer()
		{
			return &IndexBuffer_;
		}
		
		/**
		 * プリミティブタイプを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The d 3D primitive type.
		 */
		D3DPRIMITIVETYPE GetD3DPrimitiveType() const
		{
			return D3DPrimitiveType_;
		}
		
		/**
		 * 頂点数を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The number vertex.
		 */
		int GetNumVertex() const
		{
			return numVertex_;
		}
		
		/**
		 * ポリゴン数を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The number polygon.
		 */
		int GetNumPolygon() const
		{
			return numPolygon_;
		}
		
		/**
		 * 頂点定義を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the vertex declaration.
		 */
		IDirect3DVertexDeclaration9* GetVertexDecl()
		{
			return VertexBuffer_.GetVertexDecl();
		}

	private:
		
		/** 頂点数. */
		int	numVertex_;
		/** 頂点ストライド. */
		int	VertexStride_;
		/** インデックス数. */
		int	numIndex_;
		/** ポリゴンの数. */
		int	numPolygon_;
		/** 頂点バッファ. */
		VertexBuffer VertexBuffer_;
		/** インデックスバッファ. */
		IndexBuffer IndexBuffer_;
		/** プリミティブタイプ. */
		TypeE Type_;			
		/** Type of the 3D primitive. */
		D3DPRIMITIVETYPE D3DPrimitiveType_;	

	};

}// namespace nkEngine