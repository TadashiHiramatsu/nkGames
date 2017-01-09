/**
 * @file	_Graphics\_Sharp\nkSharpVertex.h
 *
 * Declares the nk sharp vertex class.
 */
#pragma once

namespace nkEngine
{
	/**
	 * 座標とUV座標.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct SShapeVertex_PT
	{
		float pos[4];
		float uv[2];
	};
	/**
	* 座標とUV座標.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*/
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[]
	{
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};

	/**
	 * 座標とカラー
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct SShapeVertex_PC {
		float		pos[4];
		int		color;
	};
	/**
	* 座標とカラー
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*/
	static const D3DVERTEXELEMENT9 scShapeVertex_PC_Element[] = {
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		{ 0, 16 ,  D3DDECLTYPE_D3DCOLOR		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR	, 0 },
		D3DDECL_END()
	};

	/**
	* 座標と法線とカラー
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*/
	struct SShapeVertex_PNC {
		float		pos[4];
		float		normal[4];
		int		color;
	};
	/**
	* 座標と法線とカラー
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*/
	static const D3DVERTEXELEMENT9 scShapeVertex_PNC_Element[] = {
		{ 0, 0 ,  D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		{ 0, 16 ,  D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL	, 0 },
		{ 0, 32 ,  D3DDECLTYPE_D3DCOLOR		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR	, 0 },
		D3DDECL_END()
	};

}// namespace nkEngine