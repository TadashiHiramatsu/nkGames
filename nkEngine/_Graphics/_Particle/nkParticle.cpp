/**
 * @file	_Graphics\_Particle\nkParticle.cpp
 *
 * �p�[�e�B�N���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkParticle.h"
#include"nkParticleEmitter.h"
#include"../_Shape/nkShapeVertex.h"

namespace nkEngine
{

	/**
	 * ������.
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

		//�p�[�e�B�N���̕��̒��S�l���v�Z
		float halfW = param.W_ * 0.5f;
		float halfH = param.H_ * 0.5f;

		NK_ASSERT(param.UVTableSize_ <= ARRAYSIZE(param.UVTable_), "uvTable size over!!!");

		//UV�l���v�Z
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
		
		//�v���~�e�B�u�쐬
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

		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("Particle.fx");

		Scale_ = Vector3(param.W_, param.H_, 1);

		//�X�P�[���s��̌v�Z
		ScaleMatrix_.MakeScaling(Scale_);

		Camera_ = camera;
		
		//�������Ԃ̐ݒ�
		Life_ = param.Life_;
		Velocity_ = param.InitVelocity_;

		//�����x�ɗ�����������B
		Velocity_.x += (((float)Random().value() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.x;
		Velocity_.y += (((float)Random().value() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.y;
		Velocity_.z += (((float)Random().value() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.z;

		//�|�W�V�����ݒ�
		Position_ = emitPosition;
		Position_.x += (((float)Random().value() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.x;
		Position_.y += (((float)Random().value() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.y;
		Position_.z += (((float)Random().value() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.z;

		AddVelocityRandomMargih_ = param.AddVelocityRandomMargih_;
		
		//�d�͐ݒ�
		Gravity_ = param.Gravity_;

		//�t�F�[�h�A�E�g�ݒ�
		isFade_ = param.isFade_;

		//�X�e�[�g�ݒ�
		State_ = StateCodeE::Run;

		//�A���t�@�l�ݒ�
		InitAlpha_ = param.InitAlpha_;
		Alpha_ = InitAlpha_;

		//�t�F�[�h�^�C���ݒ�
		FadeTime_ = param.FadeTime_;

		isBillboard_ = param.isBillboard_;
		Brightness_ = param.Brightness_;
		AlphaBlendMode_ = param.AlphaBlendMode_;
		RotateZ_ = PI * 2.0f * (float)Random().value();
		
		Texture_.Load(filepath, true);
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Particle::Update()
	{
		WorldMatrix_ = Matrix::Identity;

		//�f���^�^�C���擾
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
			//�r���{�[�h
			
			//�J�����̉�]�s����擾
			Matrix rot = Camera_->GetRotationMatrix();
			
			//�N�H�[�^�j�I��
			Quaternion qRot;
			
			float s;
			s = sin(RotateZ_);
			qRot.x = rot.m[2][0] * s;
			qRot.y = rot.m[2][1] * s;
			qRot.z = rot.m[2][2] * s;
			qRot.w = cos(RotateZ_);

			//�s�����].
			Matrix rota;
			rota.MakeRotationQuaternion(qRot);
			
			rot.Mul(rot, rota);

			//���[���h�s����v�Z.
			WorldMatrix_.Mul(ScaleMatrix_, rot);
			WorldMatrix_.Mul(WorldMatrix_, mTrans);

		}
		else
		{
			WorldMatrix_.Mul(ScaleMatrix_,mTrans);
		}

		//�^�C���v�Z
		Timer_ += deltaTime;
		
		switch (State_)
		{
		case StateCodeE::Run:
		{
			if (Timer_ >= Life_)
			{
				//�����I��
				if (isFade_)
				{
					//�t�F�[�h�A�E�g�J�n
					State_ = StateCodeE::FadeOut;
					Timer_ = 0.0f;
				}
				else
				{
					//����
					State_ = StateCodeE::Dead;
				}
			}
		}
		break;
		case StateCodeE::FadeOut:
		{
			//�t�F�[�h���Ԍv�Z
			float t = Timer_ / FadeTime_;
			Timer_ += deltaTime;

			//�A���t�@�v�Z
			Alpha_ = InitAlpha_ + (-InitAlpha_) * t;

			if (Alpha_ <= 0.0f)
			{
				Alpha_ = 0.0f;
				State_ = StateCodeE::Dead;	//���S
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
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param [in,out] texture If non-null, the texture.
	 */
	void Particle::Render()
	{

		//���[���h�r���[�v���W�F�N�V�����s��̌v�Z

		//���[���h�r���[�v���W�F�N�V�����s��
		Matrix mWVP = Matrix::Identity;
		mWVP.Mul(WorldMatrix_, Camera_->GetViewMatrix());
		mWVP.Mul(mWVP, Camera_->GetProjectionMatrix());

		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		//�A���t�@�u�����f�B���O
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		switch (AlphaBlendMode_) 
		{
		case 0:
			//�����Z����
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			
			Effect_->SetTechnique("ColorTexPrimTrans");
			break;

		case 1:
			//���Z����
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			
			Effect_->SetTechnique("ColorTexPrimAdd");
			break;
		}

		//Z�e�X�g��L��
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);

		//Z�o�b�t�@�ւ̏������݂𖳌��ɂ���
		Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);

		//���[���h�r���[�v���W�F�N�V�����s���ݒ�.
		Effect_->SetValue("g_mWVP", &mWVP, sizeof(D3DXMATRIX));
		//�A���t�@�l��ݒ�.
		Effect_->SetValue("g_alpha", &Alpha_, sizeof(Alpha_));
		//�P�x��ݒ�.
		Effect_->SetValue("g_brightness", &Brightness_, sizeof(Brightness_));

		//�e�N�X�`����ݒ�.
		Effect_->SetTexture("g_texture", &Texture_);

		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();

		//�����_�����O�X�e�[�g��߂�.
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);
		Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	}

}// namespace nkEngine