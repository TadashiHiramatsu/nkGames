#include"nkEngine/nkstdafx.h"
#include"nkImage.h"

namespace nkEngine
{
	Image::Image():
		rectTransform(nullptr),
		pEffect(nullptr)
	{
	}

	Image::~Image()
	{
	}

	void Image::Load(const char * filepass)
	{
		pEffect = EffectManager().LoadEffect("2Dshader.fx");

		Texture.reset(new CTexture);
		Texture->Load(filepass);

		Init();
	}

	void Image::Load(shared_ptr<CTexture>& _tex)
	{
		pEffect = EffectManager().LoadEffect("2Dshader.fx");

		Texture = _tex;

		Init();
	}

	void Image::Load()
	{
		pEffect = EffectManager().LoadEffect("2Dshader.fx");

		Init();
	}

	void Image::Init()
	{
		static SShapeVertex_PT vertex[] =
		{
			{
				-0.5f, 0.5f, 0.0f, 1.0f,
				0.0f, 0.0f
			},
			{
				0.5f, 0.5f, 0.0f, 1.0f,
				1.0f, 0.0f
			},
			{
				-0.5f, -0.5f, 0.0f, 1.0f,
				0.0f, 1.0f
			},
			{
				0.5f, -0.5f, 0.0f, 1.0f,
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

	void Image::Render()
	{
		IDirect3DDevice9* Device = Engine().GetDevice();

		//アルファブレンディングを行う
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//透過処理を行う
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		pEffect->SetTechnique("Tech");
		pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		pEffect->BeginPass(0);

		pEffect->SetMatrix("matWorld", &rectTransform->WorldProjMatrix);
		pEffect->SetTexture("g_diffuseTexture", Texture->GetTextureDX());
		pEffect->CommitChanges();

		Device->SetStreamSource(0, Primitive.GetVertexBuffer()->GetBody(), 0, Primitive.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive.GetD3DPrimitiveType(), 0, 0, Primitive.GetNumVertex(), 0, Primitive.GetNumPolygon());

		pEffect->EndPass();
		pEffect->End();

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}

}