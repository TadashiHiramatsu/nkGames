#include"nkEngine/nkstdafx.h"
#include"nkAntiAliasing.h"

namespace nkEngine
{
	CAntiAliasing::CAntiAliasing():
		m_effect(nullptr),
		m_isEnable(false)
	{
	}

	CAntiAliasing::~CAntiAliasing()
	{
	}

	void CAntiAliasing::Init()
	{
		m_isEnable = true;
		m_effect = EffectManager().LoadEffect("AntiAliasing.fx");

		static SShapeVertex_PT vertex[]{
			{
				-1.0f, 1.0f, 0.0f, 1.0f,
				0.0f, 0.0f
			},
			{
				1.0f, 1.0f, 0.0f, 1.0f,
				1.0f, 0.0f
			},
			{
				-1.0f, -1.0f, 0.0f, 1.0f,
				0.0f, 1.0f
			},
			{
				1.0f, -1.0f, 0.0f, 1.0f,
				1.0f, 1.0f
			},
		};
		static unsigned short index[] = {
			0,1,2,3
		};
		static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
			{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
			{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
			D3DDECL_END()
		};
		Primitive.Create(
			CPrimitive::eTriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vertex,
			4,
			eIndexFormat16,
			index
		);

		texSize[0] = Engine().GetFrameW();
		texSize[1] = Engine().GetFrameH();
	}

	void CAntiAliasing::Render()
	{	
		if (m_isEnable)
		{
			//ƒAƒ“ƒ`—LŒø
			
			m_effect->SetTechnique("FXAA");

			m_effect->Begin(0, D3DXFX_DONOTSAVESTATE);
			m_effect->BeginPass(0);
			m_effect->SetTexture("g_Texture", ScreenRender().GetMainRenderTarget().GetTexture()->GetTextureDX());
			m_effect->SetValue("g_TexSize", texSize, sizeof(texSize));
			m_effect->CommitChanges();
			
			Engine().GetDevice()->SetStreamSource(0, Primitive.GetVertexBuffer()->GetBody(), 0, Primitive.GetVertexBuffer()->GetStride());
			Engine().GetDevice()->SetIndices(Primitive.GetIndexBuffer()->GetBody());
			Engine().GetDevice()->SetVertexDeclaration(Primitive.GetVertexDecl());
			Engine().GetDevice()->DrawIndexedPrimitive(Primitive.GetD3DPrimitiveType(), 0, 0, Primitive.GetNumVertex(), 0, Primitive.GetNumPolygon());

			m_effect->EndPass();
			m_effect->End();
		}
	}

	void CAntiAliasing::Release()
	{
	}
}