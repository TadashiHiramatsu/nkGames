#include"nkEngine/nkstdafx.h"
#include"nkParticle.h"
#include"nkParticleEmitter.h"

namespace nkEngine
{

	CParticle::CParticle()
	{
		isDead = false;
		applyForce = D3DXVECTOR3(0, 0, 0);
		timer = 0;
	}

	CParticle::~CParticle()
	{

	}

	void CParticle::Init(CCamera* camera, const SParicleEmitParameter& param, D3DXVECTOR3* emitPosition)
	{
		float halfW = param.w * 0.5f;
		float halfH = param.h * 0.5f;

		NK_ASSERT(param.uvTableSize <= ARRAYSIZE(param.uvTable), "uvTable size over!!!");
		D3DXVECTOR4 uv;
		if (param.uvTableSize > 0) {
			uv = param.uvTable[Random().GetRandInt() % param.uvTableSize];
		}
		else {
			uv = param.uvTable[0];
		}

		SShapeVertex_PT vb[] = {
			{
				-halfW, halfH, 0.0f, 1.0f,
				uv.x, uv.y
			},
			{
				halfW, halfH, 0.0f, 1.0f,
				uv.z, uv.y
			},
			{
				-halfW, -halfH, 0.0f, 1.0f,
				uv.x, uv.w
			},
			{
				halfW, -halfH, 0.0f, 1.0f,
				uv.z, uv.w
			},

		};
		short index[]{
			0,1,2,3
		};
		static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
			{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
			{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
			D3DDECL_END()
		};
		primitive.Create(
			CPrimitive::eTriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			eIndexFormat16,
			index
		);

		Effect = EffectManager().LoadEffect("particle.fx");

		vScale = D3DXVECTOR3(param.w, param.h, 1);
		D3DXMatrixScaling(&mScale, vScale.x, vScale.y, vScale.z);

		this->camera = camera;
		life = param.life;
		velocity = param.initVelocity;
		//初速度に乱数を加える。
		velocity.x += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.x;
		velocity.y += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.y;
		velocity.z += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.z;
		position = *emitPosition;
		position.x += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.x;
		position.y += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.y;
		position.z += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.z;
		addVelocityRandomMargih = param.addVelocityRandomMargih;
		gravity = param.gravity;
		isFade = param.isFade;
		state = eStateRun;
		initAlpha = param.initAlpha;
		alpha = initAlpha;
		fadeTIme = param.fadeTime;
		isBillboard = param.isBillboard;
		brightness = param.brightness;
		alphaBlendMode = param.alphaBlendMode;
		rotateZ = PI * 2.0f * (float)Random().GetRandDouble();
	}
	void CParticle::Update()
	{
		D3DXMatrixIdentity(&mWorld);

		float deltaTime = Time().DeltaTime();
		D3DXVECTOR3 addGrafity = gravity;
		addGrafity *= deltaTime;
		velocity += addGrafity;
		D3DXVECTOR3 force = applyForce;
		force.x += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.x;
		force.y += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.y;
		force.z += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.z;
		force *= deltaTime;
		velocity += force;
		D3DXVECTOR3 addPos = velocity;
		addPos *= deltaTime;
		applyForce = D3DXVECTOR3(0, 0, 0);

		position += addPos;
		D3DXMATRIX mTrans;
		D3DXMatrixIdentity(&mTrans);
		mTrans.m[0][0] = 1.0f;
		mTrans.m[1][1] = 1.0f;
		mTrans.m[2][2] = 1.0f;
		mTrans.m[3][3] = 1.0f;

		mTrans.m[3][0] = position.x;
		mTrans.m[3][1] = position.y;
		mTrans.m[3][2] = position.z;

		if (isBillboard) {
			//ビルボード
			D3DXMATRIX rot = camera->GetRotationMatrix();
			D3DXQUATERNION qRot;
			float s;
			s = sin(rotateZ);
			qRot.x = rot.m[2][0] * s;
			qRot.y = rot.m[2][1] * s;
			qRot.z = rot.m[2][2] * s;
			qRot.w = cos(rotateZ);

			D3DXMATRIX rota;
			D3DXMatrixRotationQuaternion(&rota, &qRot);
			D3DXMatrixMultiply(&rot, &rot, &rota);

			
			mWorld *= mScale * rot * mTrans;
		}
		else {
			mWorld = mScale *  mTrans;
		}
		timer += deltaTime;
		switch (state) {
		case eStateRun:
			if (timer >= life) {
				if (isFade) {
					state = eStateFadeOut;
					timer = 0.0f;
				}
				else {
					state = eStateDead;
				}
			}
			break;
		case eStateFadeOut: {
			float t = timer / fadeTIme;
			timer += deltaTime;
			alpha = initAlpha + (-initAlpha)*t;
			if (alpha <= 0.0f) {
				alpha = 0.0f;
				state = eStateDead;	//死亡。
			}
		}break;
		case eStateDead:
			isDead = true;
			break;
		}
	}

	void CParticle::Render(IDirect3DTexture9* _pTextures)
	{
		D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		D3DXMatrixMultiply(&m, &mWorld, &camera->GetViewMatrix());
		D3DXMatrixMultiply(&m, &m, &camera->GetProjectionMatrix());

		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		switch (alphaBlendMode) {
		case 0:
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			Effect->SetTechnique("ColorTexPrimTrans");
			break;
		case 1:
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			Effect->SetTechnique("ColorTexPrimAdd");
			break;
		}

		//Zテストを有効
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);

		//Zバッファへの書き込みを無効にする
		Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		Effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect->BeginPass(0);
		Effect->SetValue("g_mWVP", &m, sizeof(D3DXMATRIX));
		Effect->SetValue("g_alpha", &alpha, sizeof(alpha));
		Effect->SetValue("g_brightness", &brightness, sizeof(brightness));
		if (_pTextures) 
		{
			Effect->SetTexture("g_texture", _pTextures);
		}
		Effect->CommitChanges();

		Device->SetStreamSource(0, primitive.GetVertexBuffer()->GetBody(), 0, primitive.GetVertexBuffer()->GetStride());
		Device->SetIndices(primitive.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(primitive.GetVertexDecl());
		Device->DrawIndexedPrimitive(primitive.GetD3DPrimitiveType(), 0, 0, primitive.GetNumVertex(), 0, primitive.GetNumPolygon());

		Effect->EndPass();
		Effect->End();

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);
		Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	}

}