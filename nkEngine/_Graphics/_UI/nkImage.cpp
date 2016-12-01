#include"nkEngine/nkstdafx.h"
#include"nkImage.h"

namespace nkEngine
{
	Image::Image():
		Transform(nullptr)
	{

	}

	Image::~Image()
	{
		Release();
	}

	void Image::Load(const char * filepass)
	{
		m_pEffect = EffectManager().LoadEffect("2Dshader.fx");

		Texture.reset(new CTexture);
		Texture->Load(filepass);

		Init();
	}

	void Image::Load()
	{
		m_pEffect = EffectManager().LoadEffect("2Dshader.fx");

		Init();
	}
		
	void Image::Init()
	{
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
	}

	void Image::Update()
	{
		
	}

	void Image::Render()
	{
		IDirect3DDevice9* Device = Engine().GetDevice();

		//アルファブレンディングを行う
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//透過処理を行う
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pEffect->SetTechnique("Tech");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);

		m_pEffect->SetMatrix("matWorld", &Transform->mWorld);
		m_pEffect->SetTexture("g_diffuseTexture", Texture->GetTextureDX());
		m_pEffect->CommitChanges();

		Device->SetStreamSource(0, Primitive.GetVertexBuffer()->GetBody(), 0, Primitive.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive.GetD3DPrimitiveType(), 0, 0, Primitive.GetNumVertex(), 0, Primitive.GetNumPolygon());

		m_pEffect->EndPass();
		m_pEffect->End();

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}

	void Image::Release()
	{

	}
}