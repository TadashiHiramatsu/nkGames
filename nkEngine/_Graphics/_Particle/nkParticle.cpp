/**
 * @file	_Graphics\_Particle\nkParticle.cpp
 *
 * �p�[�e�B�N���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkParticle.h"
#include"nkParticleEmitter.h"
#include"../_Sharp/nkSharpVertex.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
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
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Particle::~Particle()
	{
	}

	/**
	 * ������.
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
		
		//�p�[�e�B�N���쐬
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

		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("particle.fx");

		Scale_ = D3DXVECTOR3(param.W_, param.H_, 1);

		//�X�P�[���s��̌v�Z
		D3DXMatrixScaling(&ScaleMatrix_, Scale_.x, Scale_.y, Scale_.z);

		Camera_ = camera;
		
		//�������Ԃ̐ݒ�
		Life_ = param.Life_;
		Velocity_ = param.InitVelocity_;

		//�����x�ɗ�����������B
		Velocity_.x += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.x;
		Velocity_.y += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.y;
		Velocity_.z += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitVelocityVelocityRandomMargin_.z;

		//�|�W�V�����ݒ�
		Position_ = *emitPosition;
		Position_.x += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.x;
		Position_.y += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.y;
		Position_.z += (((float)Random().GetRandDouble() - 0.5f) * 2.0f) * param.InitPositionRandomMargin_.z;

		AddVelocityRandomMargih_ = param.AddVelocityRandomMargih_;
		
		//�d�͐ݒ�
		Gravity_ = param.Gravity_;

		//�t�F�[�h�A�E�g�ݒ�
		isFade_ = param.isFade_;

		//�X�e�[�g�ݒ�
		State_ = StateRun;

		//�A���t�@�l�ݒ�
		InitAlpha_ = param.InitAlpha_;
		Alpha_ = InitAlpha_;

		//�t�F�[�h�^�C���ݒ�
		FadeTime_ = param.FadeTime_;

		isBillboard_ = param.isBillboard_;
		Brightness_ = param.Brightness_;
		AlphaBlendMode_ = param.AlphaBlendMode_;
		RotateZ_ = PI * 2.0f * (float)Random().GetRandDouble();

	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Particle::Update()
	{
		D3DXMatrixIdentity(&WorldMatrix_);

		//�f���^�^�C���擾
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
			//�r���{�[�h
			
			//�J�����̉�]�s����擾
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

		//�^�C���v�Z
		Timer_ += deltaTime;
		
		switch (State_)
		{
		case StateRun:
			if (Timer_ >= Life_)
			{
				//�����I��
				if (isFade_)
				{
					//�t�F�[�h�A�E�g�J�n
					State_ = StateFadeOut;
					Timer_ = 0.0f;
				}
				else 
				{
					//����
					State_ = StateDead;
				}
			}
			break;

		case StateFadeOut:
			//�t�F�[�h���Ԍv�Z
			float t = Timer_ / FadeTime_;
			Timer_ += deltaTime;

			//�A���t�@�v�Z
			Alpha_ = InitAlpha_ + (-InitAlpha_) * t;
			
			if (Alpha_ <= 0.0f) 
			{
				Alpha_ = 0.0f;
				State_ = StateDead;	//���S
			}
			break;

		case StateDead:
			isDead_ = true;
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
	void Particle::Render(IDirect3DTexture9* texture)
	{

		//���[���h�r���[�v���W�F�N�V�����s��̌v�Z
		D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		D3DXMatrixMultiply(&m, &WorldMatrix_, &Camera_->GetViewMatrix());
		D3DXMatrixMultiply(&m, &m, &Camera_->GetProjectionMatrix());

		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

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