#include"nkEngine/nkstdafx.h"
#include"nkBloom.h"

namespace nkEngine
{
	CBloom::CBloom()
	{

	}

	CBloom::~CBloom()
	{

	}

	void CBloom::UpdateWeight(float dis)
	{
		float total = 0;
		for (int i = 0; i < NUM_WEIGHTS; i++)
		{
			m_weights[i] = expf(-0.5f*(float)(i*i) / dis);
			if (0 == i)
			{
				total += m_weights[i];
			}
			else
			{
				total += 2.0f*m_weights[i];
			}
		}
		for (int i = 0; i < NUM_WEIGHTS; i++)
		{
			m_weights[i] /= total;
		}
	}

	void CBloom::Render()
	{
		if (m_isEnable)
		{
			IDirect3DDevice9* Device = Engine().GetDevice();

			UpdateWeight(25.0f);

			//ãPìxìEèo
			{
				Device->SetRenderTarget(0, m_luminanceRenderTarget.GetSurface());
				Device->SetDepthStencilSurface(m_luminanceRenderTarget.GetDepthSurface());
				Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
				m_pEffect->SetTechnique("SamplingLuminance");
				m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
				m_pEffect->BeginPass(0);
				m_pEffect->SetTexture("g_Scene", ScreenRender().GetMainRenderTarget().GetTexture()->GetTextureDX());
				m_pEffect->CommitChanges();

				Device->SetStreamSource(0, Primitive.GetVertexBuffer()->GetBody(), 0, Primitive.GetVertexBuffer()->GetStride());
				Device->SetIndices(Primitive.GetIndexBuffer()->GetBody());
				Device->SetVertexDeclaration(Primitive.GetVertexDecl());
				Device->DrawIndexedPrimitive(Primitive.GetD3DPrimitiveType(), 0, 0, Primitive.GetNumVertex(), 0, Primitive.GetNumPolygon());

				m_pEffect->EndPass();
				m_pEffect->End();
			}

			//ÉuÉâÅ[
			for (int i = 0; i < 2; i++)
			{
				Blur[i].Render();
			}
			
			{
				float offset[] = {
					0.5f / Blur[1].GetSizeW(),
					0.5f / Blur[1].GetSizeH()
				};
		
				Device->SetRenderTarget(0, ScreenRender().GetMainRenderTarget().GetSurface());
				Device->SetDepthStencilSurface(ScreenRender().GetMainRenderTarget().GetDepthSurface());

				//â¡éZçáê¨ÅB
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

				m_pEffect->SetTechnique("Final");
				m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
				m_pEffect->BeginPass(0);
				m_pEffect->SetTexture("g_blur", Blur[1].GetTexture()->GetTextureDX());
				m_pEffect->SetValue("g_offset", offset, sizeof(offset));
				m_pEffect->CommitChanges();

				Device->SetStreamSource(0, Primitive.GetVertexBuffer()->GetBody(), 0, Primitive.GetVertexBuffer()->GetStride());
				Device->SetIndices(Primitive.GetIndexBuffer()->GetBody());
				Device->SetVertexDeclaration(Primitive.GetVertexDecl());
				Device->DrawIndexedPrimitive(Primitive.GetD3DPrimitiveType(), 0, 0, Primitive.GetNumVertex(), 0, Primitive.GetNumPolygon());

				m_pEffect->EndPass();
				m_pEffect->End();

				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}

	}

	void CBloom::Create(bool is)
	{
		if (is)
		{
			int w = Engine().GetFrameW();
			int h = Engine().GetFrameH();

			m_luminanceRenderTarget.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

			Blur[0].Init(w, h, *m_luminanceRenderTarget.GetTexture());
			Blur[1].Init(w, h, *Blur[0].GetTexture());
			
			m_pEffect = EffectManager().LoadEffect("bloom.fx");
			m_isEnable = true;

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
	}
}