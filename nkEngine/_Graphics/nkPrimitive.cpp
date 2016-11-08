#include"nkEngine/nkstdafx.h"
#include"nkPrimitive.h"

namespace nkEngine
{
	CPrimitive::CPrimitive() :
		m_numVertex(0),
		m_numIndex(0),
		m_vertexStride(0),
		m_type(eTriangleList),
		m_d3dPrimitiveType(D3DPT_TRIANGLELIST)
	{
	}

	CPrimitive::~CPrimitive()
	{
		Release();
	}

	void CPrimitive::Create(
		EType _PrimitiveType,
		int _NumVertex, 
		int _VertexStride, 
		const D3DVERTEXELEMENT9 * _VertexLayout, 
		void * _pSrcVertexBuffer, 
		int _NumIndex, 
		EIndexFormat _IndexFormat,
		void * _pSrcIndexbuffer)
	{
		NK_ASSERT(_PrimitiveType < eTypeNum, "primitiveType is invalid");
		NK_ASSERT(_NumVertex != 0, "numVertex is zero");
		NK_ASSERT(_VertexStride != 0, "vertexStrid is zero");
		NK_ASSERT(_NumIndex != 0, "numIndex is zero");
		m_type = _PrimitiveType;
		m_numVertex = _NumVertex;
		m_vertexStride = _VertexStride;
		m_numIndex = _NumIndex;

		Release();
		
		m_vertexBuffer.Create(_NumVertex, _VertexStride, _VertexLayout, _pSrcVertexBuffer);
		m_indexBuffer.Create(_NumIndex, _IndexFormat, _pSrcIndexbuffer);

		if (m_type == eTriangleList) {
			m_numPolygon = _NumIndex / 3;
			m_d3dPrimitiveType = D3DPT_TRIANGLELIST;
		}
		else if (m_type == eTriangleStrip) {
			m_numPolygon = _NumIndex - 2;
			m_d3dPrimitiveType = D3DPT_TRIANGLESTRIP;
		}
	}

	void CPrimitive::Release()
	{
		m_vertexBuffer.Release();
		m_indexBuffer.Release();
	}
}