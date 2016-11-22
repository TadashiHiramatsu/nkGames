#include"nkEngine/nkstdafx.h"
#include"nkSprite.h"

namespace nkEngine
{
	CSprite::CSprite():
		STransform(nullptr)
	{

	}

	CSprite::~CSprite()
	{
		Release();
	}

	void CSprite::Load(const char * filepass)
	{
		m_pEffect = EffectManager().LoadEffect("2Dshader.fx");

		Texture = new CTexture;
		Texture->Load(filepass);

		NK_ASSERT(Texture != nullptr, "テクスチャが存在しません");

		Init();
	}

	void CSprite::Load()
	{
		m_pEffect = EffectManager().LoadEffect("2Dshader.fx");

		Init();
	}
		
	void CSprite::Init()
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

		D3DXMatrixIdentity(&m_mWorld);
	}

	void CSprite::Update()
	{
		if (STransform != nullptr)
		{
			D3DXMATRIX  mScale, mRot, mTrans;

			int screenBufferW = Engine().GetScreenW();
			int screenBufferH = Engine().GetScreenH();
			int screenBufferHalfW = screenBufferW / 2;
			int screenBufferHalfH = screenBufferH / 2;

			D3DXVECTOR3 scale;
			scale.x = STransform->Size.x / screenBufferW;
			scale.y = STransform->Size.y / screenBufferH;
			scale.z = 1.0f;

			D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.x);

			//移動
			D3DXVECTOR3 trans;
			trans.x = STransform->Position.x / screenBufferHalfW - 1;
			trans.y = STransform->Position.y / screenBufferHalfH - 1;
			trans.z = 0.0f;

			//ピボットの分のオフセットを計算。
			D3DXVECTOR3 pivotOffset;
			pivotOffset.x = (STransform->Size.x * (0.5f - STransform->Pivot.x)) / screenBufferHalfW;
			pivotOffset.y = (STransform->Size.y * (0.5f - STransform->Pivot.y)) / screenBufferHalfH;
			pivotOffset.z = 0.0f;
			trans += pivotOffset;

			D3DXMatrixTranslation(&mTrans, trans.x, trans.y, trans.z);

			D3DXMatrixRotationQuaternion(&mRot, &STransform->Rotation);

			m_mWorld = mScale * mRot * mTrans;
		}
	}

	void CSprite::Render()
	{
		IDirect3DDevice9* Device = Engine().GetDevice();

		//アルファブレンディングを行う
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//透過処理を行う
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pEffect->SetTechnique("Tech");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);

		m_pEffect->SetMatrix("matWorld", &m_mWorld);
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

	void CSprite::Release()
	{

	}
}