#include"nkEngine/nkstdafx.h"
#include"nkSprite.h"

namespace nkEngine
{
	CSprite::CSprite():
		m_pTex(nullptr),
		m_pEffect(nullptr),
		m_pVB(nullptr)
	{

	}

	CSprite::~CSprite()
	{
		this->Release();
	}

	void CSprite::Load(const char * filepass)
	{
		LPD3DXBUFFER  compileErrorBuffer = NULL;
		HRESULT hr = D3DXCreateEffectFromFile(
			Engine().GetDevice(),
			"shader\\2Dshader.fx",
			NULL,
			NULL,
			D3DXSHADER_DEBUG,
			NULL,
			&m_pEffect,
			&compileErrorBuffer
		);

		if (FAILED(hr)) {
			MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			abort();
		}

		D3DXCreateTextureFromFile(Engine().GetDevice(), filepass, &m_pTex);

		NK_ASSERT(m_pTex != nullptr, "テクスチャが存在しません");
	}

	void CSprite::Load()
	{
		LPD3DXBUFFER  compileErrorBuffer = NULL;
		m_pEffect = EffectManager().LoadEffect("2Dshader.fx");

	}

	void CSprite::Init()
	{
		SVertex vertices[] = {
			{ -1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f, },
			{ -1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f, },
			{ 1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f, },
			{ 1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f, },
			{ -1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f, },
			{ 1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f, },
		};
		Engine().GetDevice()->CreateVertexBuffer(6 * sizeof(SVertex), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);
		VOID* pVertices;
		m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
		memcpy(pVertices, vertices, sizeof(vertices));
		m_pVB->Unlock();

		isLuminance = false;
		Luminance = 0.0f;

		D3DXMatrixIdentity(&m_mWorld);

	}
	void CSprite::Update(D3DXVECTOR3 vec3Trans, D3DXVECTOR3 vec3Scale, float angle)
	{
		vec3Scale.x = vec3Scale.x / Engine().GetFrameW();
		vec3Scale.y = vec3Scale.y / Engine().GetFrameH();
		D3DXVECTOR3 t;
		t.x = vec3Trans.x / Engine().GetFrameW();
		t.y = vec3Trans.y / Engine().GetFrameH();
		vec3Trans.x = -1.0f + t.x * 2.0f;
		vec3Trans.y = 1.0f - t.y * 2.0f;
		D3DXMatrixScaling(&m_mScale, vec3Scale.x, vec3Scale.y, vec3Scale.z);
		D3DXMatrixTranslation(&m_mTrans, vec3Trans.x, vec3Trans.y, vec3Trans.z);
		D3DXMatrixRotationZ(&m_mRot, D3DXToRadian(angle));
		m_mWorld = m_mScale * m_mRot * m_mTrans;
	}
	void CSprite::Render()
	{
		m_pEffect->SetTechnique("Tech");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);

		m_pEffect->SetMatrix("matWorld", &m_mWorld);
		m_pEffect->SetTexture("g_diffuseTexture", m_pTex);
		m_pEffect->SetBool("isLuminance", isLuminance);
		m_pEffect->SetFloat("g_luminance", Luminance);
		m_pEffect->CommitChanges();

		DrawPrimitiveOnly();

		m_pEffect->EndPass();
		m_pEffect->End();
	}
	void CSprite::Release()
	{
		SAFE_RELEASE(m_pTex);
		SAFE_RELEASE(m_pVB);
	}
	void CSprite::DrawPrimitiveOnly()
	{
		Engine().GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(SVertex));
		Engine().GetDevice()->SetFVF(D3DFVF_CUSTOMVERTEX);
		Engine().GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	}
}