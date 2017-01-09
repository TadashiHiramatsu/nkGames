/**
 * @file	_Graphics\_Particle\nkParticle.cpp
 *
 * パーティクルクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkParticle.h"
#include"nkParticleEmitter.h"
#include"../_Sharp/nkSharpVertex.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Particle::Particle() :
		isDead_(false),
		Timer_(0),
		ApplyForce_(D3DXVECTOR3(0, 0, 0))
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Particle::~Particle()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param [in,out] camera	    If non-null, the camera.
	 * @param 		   param	    The parameter.
	 * @param [in,out] emitPosition If non-null, the emit position.
	 */
	void Particle::Init(Camera* camera, const ParicleParameterS& param, D3DXVECTOR3* emitPosition)
	{

		float halfW = param.W_ * 0.5f;
		float halfH = param.H_ * 0.5f;

		NK_ASSERT(param.UVTableSize_ <= ARRAYSIZE(param.UVTable_), "uvTable size over!!!");

		D3DXVECTOR4 uv;

		if (param.UVTableSize_ > 0) 
		{
			uv = param.UVTable_[Random().GetRandInt() % param.UVTableSize_];
		}
		else 
		{
			uv = param.UVTable_[0];
		}

		SShapeVertex_PT vb[] = 
		{
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
		short index[] = 
		{
			0,1,2,3
		};
		
		//パーティクル作成
		Primitive_.Create(
			Primitive::TriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			IndexFormat16,
			index
		);

		//エフェクトのロード
		Effect_ = EffectManager().LoadEffect("particle.fx");

		Scale_ = D3DXVECTOR3(param.W_, param.H_, 1);

		//スケール行列の計算
		D3DXMatrixScaling(&ScaleMatrix_, Scale_.x, Scale_.y, Scale_.z);

		Camera_ = camera;
		
		//生存時間の設定
		Life_ = param.Life_;
		Velocity_ = param.InitVelocity_;

		//初速度に乱数を加える。
		Velocity_.x += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.x;
		Velocity_.y += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.y;
		Velocity_.z += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.z;

		//ポジション設定
		Position_ = *emitPosition;
		Position_.x += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.x;
		Position_.y += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.y;
		Position_.z += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.z;

		AddVelocityRandomMargih_ = param.AddVelocityRandomMargih_;
		
		//重力設定
		Gravity_ = param.Gravity_;

		//フェードアウト設定
		isFade_ = param.isFade_;

		//ステート設定
		State_ = StateRun;

		//アルファ値設定
		InitAlpha_ = param.InitAlpha_;
		Alpha_ = InitAlpha_;

		//フェードタイム設定
		FadeTime_ = param.FadeTime_;

		isBillboard_ = param.isBillboard_;
		Brightness_ = param.Brightness_;
		AlphaBlendMode_ = param.AlphaBlendMode_;
		RotateZ_ = PI * 2.0f * (float)Random().GetRandDouble();

	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Particle::Update()
	{
		D3DXMatrixIdentity(&WorldMatrix_);

		//デルタタイム取得
		float deltaTime = Time().DeltaTime();

		D3DXVECTOR3 addGrafity = Gravity_;
		addGrafity *= deltaTime;
		Velocity_ += addGrafity;
		D3DXVECTOR3 force = ApplyForce_;
		force.x += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * AddVelocityRandomMargih_.x;
		force.y += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * AddVelocityRandomMargih_.y;
		force.z += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * AddVelocityRandomMargih_.z;
		force *= deltaTime;
		Velocity_ += force;
		D3DXVECTOR3 addPos = Velocity_;
		addPos *= deltaTime;
		ApplyForce_ = D3DXVECTOR3(0, 0, 0);

		Position_ += addPos;

		D3DXMATRIX mTrans;
		D3DXMatrixIdentity(&mTrans);
		mTrans.m[0][0] = 1.0f;
		mTrans.m[1][1] = 1.0f;
		mTrans.m[2][2] = 1.0f;
		mTrans.m[3][3] = 1.0f;

		mTrans.m[3][0] = Position_.x;
		mTrans.m[3][1] = Position_.y;
		mTrans.m[3][2] = Position_.z;

		if (isBillboard_) 
		{
			//ビルボード
			
			//カメラの回転行列を取得
			D3DXMATRIX rot = Camera_->GetRotationMatrix();
			
			D3DXQUATERNION qRot;
			
			float s;
			s = sin(RotateZ_);
			qRot.x = rot.m[2][0] * s;
			qRot.y = rot.m[2][1] * s;
			qRot.z = rot.m[2][2] * s;
			qRot.w = cos(RotateZ_);

			D3DXMATRIX rota;
			D3DXMatrixRotationQuaternion(&rota, &qRot);
			D3DXMatrixMultiply(&rot, &rot, &rota);

			
			WorldMatrix_ *= ScaleMatrix_ * rot * mTrans;

		}
		else
		{
			WorldMatrix_ = ScaleMatrix_ * mTrans;
		}

		//タイム計算
		Timer_ += deltaTime;
		
		switch (State_)
		{
		case StateRun:
			if (Timer_ >= Life_)
			{
				//生存終了
				if (isFade_)
				{
					//フェードアウト開始
					State_ = StateFadeOut;
					Timer_ = 0.0f;
				}
				else 
				{
					//即死
					State_ = StateDead;
				}
			}
			break;

		case StateFadeOut:
			//フェード時間計算
			float t = Timer_ / FadeTime_;
			Timer_ += deltaTime;

			//アルファ計算
			Alpha_ = InitAlpha_ + (-InitAlpha_) * t;
			
			if (Alpha_ <= 0.0f) 
			{
				Alpha_ = 0.0f;
				State_ = StateDead;	//死亡
			}
			break;

		case StateDead:
			isDead_ = true;
			break;
		}

	}

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param [in,out] texture If non-null, the texture.
	 */
	void Particle::Render(IDirect3DTexture9* texture)
	{

		//ワールドビュープロジェクション行列の計算
		D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		D3DXMatrixMultiply(&m, &WorldMatrix_, &Camera_->GetViewMatrix());
		D3DXMatrixMultiply(&m, &m, &Camera_->GetProjectionMatrix());

		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		switch (AlphaBlendMode_) 
		{
		case 0:
			//半加算合成
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			
			Effect_->SetTechnique("ColorTexPrimTrans");
			break;

		case 1:
			//加算合成
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			
			Effect_->SetTechnique("ColorTexPrimAdd");
			break;
		}

		//Zテストを有効
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);

		//Zバッファへの書き込みを無効にする
		Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);

		Effect_->SetValue("g_mWVP", &m, sizeof(D3DXMATRIX));
		Effect_->SetValue("g_alpha", &Alpha_, sizeof(Alpha_));
		Effect_->SetValue("g_brightness", &Brightness_, sizeof(Brightness_));

		if (texture) 
		{
			Effect_->SetTexture("g_texture", texture);
		}

		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);
		Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	}

}// namespace nkEngine