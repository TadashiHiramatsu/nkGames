/**
 * @file _Graphics\_Particle\nkParticleEmitter.cpp
 *
 * �p�[�e�B�N���G�~�b�^�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkParticleEmitter.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	ParticleEmitter::ParticleEmitter() :
		isCreate_(false)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	ParticleEmitter::~ParticleEmitter()
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
	void ParticleEmitter::Init(Camera* camera, const ParicleParameterS& param, D3DXVECTOR3* emitPosition)
	{
		
		Camera_ = camera;
		Param_ = param;
		EmitPosition_ = emitPosition;

		Timer_ = 0.0f;

		//�e�N�X�`���̃��[�h
		Texture_.Load(Param_.TexturePath_);

	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void ParticleEmitter::Update()
	{

		if (Timer_ >= Param_.IntervalTime_ && isCreate_) 
		{
			//�p�[�e�B�N���𐶐��B
			Particle* p = new Particle();

			//�p�[�e�B�N���̏�����
			p->Init(Camera_, Param_, EmitPosition_);
			
			Timer_ = 0.0f;
			
			//�p�[�e�B�N���̓o�^
			ParticleList_.push_back(p);

		}

		//�^�C�}�[�v�Z
		Timer_ += Time().DeltaTime();

		auto p = ParticleList_.begin();

		//�p�[�e�B�N��������ł���Ȃ烊�X�g����폜
		while (p != ParticleList_.end()) 
		{
			if ((*p)->GetDead()) 
			{
				delete (*p);
				p = ParticleList_.erase(p);
			}
			else
			{
				p++;
			}
		}

		p = ParticleList_.begin();
		
		while (p != ParticleList_.end()) 
		{
			(*p++)->Update();
		}

	}

	/**
	 * Adds a force.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param addForce The add force.
	 */
	void ParticleEmitter::AddForce(const D3DXVECTOR3& addForce)
	{
		for (auto p : ParticleList_) 
		{
			p->AddForce(addForce);
		}
	}

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void ParticleEmitter::Render()
	{
		auto p = ParticleList_.begin();

		while (p != ParticleList_.end()) 
		{
			(*p++)->Render(Texture_.GetTexture());
		}

	}

}// namespace nkEngine