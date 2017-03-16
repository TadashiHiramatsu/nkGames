/**
 * @file _Graphics\nkPrimitive.cpp
 *
 * プリミティブクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkPrimitive.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
    Primitive::Primitive() :
		numVertex_(0),
		numIndex_(0),
		VertexStride_(0),
		Type_(TypeE::TriangleList),
		D3DPrimitiveType_(D3DPT_TRIANGLELIST)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Primitive::~Primitive()
	{
		Release();
	}

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
	void Primitive::Create(
		TypeE 						primitiveType,
		int 						numVertex,
		int 						vertexStride,
		const D3DVERTEXELEMENT9*	vertexLayout,
		void*						srcVertexBuffer,
		int 						numIndex,
		IndexFormatE				indexFormat,
		void*						srcIndexbuffer
	)
	{

		NK_ASSERT(primitiveType < TypeE::TypeNum, "primitiveType is invalid");
		NK_ASSERT(numVertex != 0, "numVertex is zero");
		NK_ASSERT(vertexStride != 0, "vertexStrid is zero");
		NK_ASSERT(numIndex != 0, "numIndex is zero");

		//タイプをコピー
		Type_ = primitiveType;
		//頂点数をコピー
		numVertex_ = numVertex;
		//頂点ストライドをコピー
		VertexStride_ = vertexStride;
		//インデックスの数をコピー
		numIndex_ = numIndex;

		//解放
		Release();
		
		//頂点バッファを作成
		VertexBuffer_.Create(numVertex_, VertexStride_, vertexLayout, srcVertexBuffer);

		//インデックスバッファを作成
		IndexBuffer_.Create(numIndex_, indexFormat, srcIndexbuffer);

		if (Type_ == TypeE::TriangleList)
		{
			numPolygon_ = numIndex / 3;
			D3DPrimitiveType_ = D3DPT_TRIANGLELIST;
		}
		else if (Type_ == TypeE::TriangleStrip)
		{
			numPolygon_ = numIndex - 2;
			D3DPrimitiveType_ = D3DPT_TRIANGLESTRIP;
		}

	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Primitive::Release()
	{
		VertexBuffer_.Release();
		IndexBuffer_.Release();
	}

}// namespace nkEngine