/**
 * @file	_Graphics\_Particle\nkParticle.cpp
 *
 * パーティクルクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkParticle.h"
#include"nkParticleEmitter.h"
#include"../_Shape/nkShapeVertex.h"

namespace nkEngine
{

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param [in,out] camera	    If non-null, the camera.
	 * @param 		   param	    The parameter.
	 * @param [in,out] emitPosition If non-null, the emit position.
	 */
	void Particle::Start(const Camera* camera, const ParticleParameterS& param, const Vector3& emitPosition,char* filepath)
	{

		//パーティクルの幅の中心値を計算
		float halfW = param.W_ * 0.5f;
		float halfH = param.H_ * 0.5f;

		NK_ASSERT(param.UVTableSize_ <= ARRAYSIZE(param.UVTable_), "uvTable size over!!!");

		//UV値を計算
		Vector4 uv;
		if (param.UVTableSize_ > 0) 
		{
			uv = param.UVTable_[Random().Range(0, param.UVTableSize_ -1)];
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
		short ib[] = 
		{
			0,1,2,3
		};
		
		//プリミティブ作成
		Primitive_.Create(
			Primitive::TypeE::TriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			IndexFormatE::IndexFormat16,
			ib
		);

		//エフェクトのロード
		Effect_ = EffectManager().LoadEffect("Particle.fx");

		Scale_ = Vector3(param.W_, param.H_, 1);

		//スケール行列の計算
		ScaleMatrix_.MakeScaling(Scale_);

		Camera_ = camera;
		
		//生存時間の設定
		Life_ = param.Life_;
		Velocity_ = param.InitVelocity_;

		//初速度に乱数を加える。
		Velocity_.x += (((float)Random().value() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.x;
		Velocity_.y += (((float)Random().value() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.y;
		Velocity_.z += (((float)Random().value() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.z;

		//ポジション設定
		Position_ = emitPosition;
		Position_.x += (((float)Random().value() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.x;
		Position_.y += (((float)Random().value() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.y;
		Position_.z += (((float)Random().value() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.z;

		AddVelocityRandomMargih_ = param.AddVelocityRandomMargih_;
		
		//重力設定
		Gravity_ = param.Gravity_;

		//フェードアウト設定
		isFade_ = param.isFade_;

		//ステート設定
		State_ = StateCodeE::Run;

		//アルファ値設定
		InitAlpha_ = param.InitAlpha_;
		Alpha_ = InitAlpha_;

		//フェードタイム設定
		FadeTime_ = param.FadeTime_;

		isBillboard_ = param.isBillboard_;
		Brightness_ = param.Brightness_;
		AlphaBlendMode_ = param.AlphaBlendMode_;
		RotateZ_ = PI * 2.0f * (float)Random().value();
		
		Texture_.Load(filepath, true);
	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Particle::Update()
	{
		WorldMatrix_ = Matrix::Identity;

		//デルタタイム取得
		float deltaTime = Time().DeltaTime();

		Vector3 addGrafity = Gravity_;
		addGrafity.Scale(deltaTime);
		Velocity_.Add(addGrafity);

		Vector3 force = ApplyForce_;
		force.x += (((float)Random().value() - 0.5f) * 2.0f) * AddVelocityRandomMargih_.x;
		force.y += (((float)Random().value() - 0.5f) * 2.0f) * AddVelocityRandomMargih_.y;
		force.z += (((float)Random().value() - 0.5f) * 2.0f) * AddVelocityRandomMargih_.z;
		force.Scale(deltaTime);
		Velocity_.Add(force);
		Vector3 addPos = Velocity_;
		addPos.Scale(deltaTime);
		ApplyForce_ = Vector3::Zero;

		Position_.Add(addPos);

		Matrix mTrans = Matrix::Identity;
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
			Matrix rot = Camera_->GetRotationMatrix();
			
			//クォータニオン
			Quaternion qRot;
			
			float s;
			s = sin(RotateZ_);
			qRot.x = rot.m[2][0] * s;
			qRot.y = rot.m[2][1] * s;
			qRot.z = rot.m[2][2] * s;
			qRot.w = cos(RotateZ_);

			//行列を回転.
			Matrix rota;
			rota.MakeRotationQuaternion(qRot);
			
			rot.Mul(rot, rota);

			//ワールド行列を計算.
			WorldMatrix_.Mul(ScaleMatrix_, rot);
			WorldMatrix_.Mul(WorldMatrix_, mTrans);

		}
		else
		{
			WorldMatrix_.Mul(ScaleMatrix_,mTrans);
		}

		//タイム計算
		Timer_ += deltaTime;
		
		switch (State_)
		{
		case StateCodeE::Run:
		{
			if (Timer_ >= Life_)
			{
				//生存終了
				if (isFade_)
				{
					//フェードアウト開始
					State_ = StateCodeE::FadeOut;
					Timer_ = 0.0f;
				}
				else
				{
					//即死
					State_ = StateCodeE::Dead;
				}
			}
		}
		break;
		case StateCodeE::FadeOut:
		{
			//フェード時間計算
			float t = Timer_ / FadeTime_;
			Timer_ += deltaTime;

			//アルファ計算
			Alpha_ = InitAlpha_ + (-InitAlpha_) * t;

			if (Alpha_ <= 0.0f)
			{
				Alpha_ = 0.0f;
				State_ = StateCodeE::Dead;	//死亡
			}
		}
		break;
		case StateCodeE::Dead:
		{
			isDead_ = true;
			DeleteGO(this);
		}
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
	void Particle::Render()
	{

		//ワールドビュープロジェクション行列の計算

		//ワールドビュープロジェクション行列
		Matrix mWVP = Matrix::Identity;
		mWVP.Mul(WorldMatrix_, Camera_->GetViewMatrix());
		mWVP.Mul(mWVP, Camera_->GetProjectionMatrix());

		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		//アルファブレンディング
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

		//ワールドビュープロジェクション行列を設定.
		Effect_->SetValue("g_mWVP", &mWVP, sizeof(D3DXMATRIX));
		//アルファ値を設定.
		Effect_->SetValue("g_alpha", &Alpha_, sizeof(Alpha_));
		//輝度を設定.
		Effect_->SetValue("g_brightness", &Brightness_, sizeof(Brightness_));

		//テクスチャを設定.
		Effect_->SetTexture("g_texture", &Texture_);

		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();

		//レンダリングステートを戻す.
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);
		Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	}

}// namespace nkEngine