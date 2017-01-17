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
	 * ������. �I�[�o�[���C�h����Ȃ����ߎ����ŌĂԕK�v������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param [in,out] camera	    If non-null, the camera.
	 * @param 		   param	    The parameter.
	 * @param 		   emitPosition The emit position.
	 * @param 		   lifeTime	    The life time.
	 */
	void ParticleEmitter::Start(Camera* camera, const ParticleParameterS& param, D3DXVECTOR3& emitPosition, float lifeTime)
	{
		Camera_ = camera;
		Param_ = param;
		EmitPosition_ = emitPosition;

		LifeTime_ = lifeTime;

		//�t�@�C���p�X�̍쐬
		char* baseDir = "Particle/";
		strcpy(Filepath_, baseDir);
		strcat(Filepath_, param.TexturePath_);
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void ParticleEmitter::Update()
	{
		if (LifeLT_ >= LifeTime_)
		{
			if (ParticleList_.size() == 0)
			{
				DeleteGO(this);
			}
		}
		else
		{
			if (IntervalLT_ >= Param_.IntervalTime_)
			{
				//�������Ԃ��o�߂��Ă���̂Ńp�[�e�B�N���쐬

				//�p�[�e�B�N���𐶐��B
				Particle* p = NewGO<Particle>();

				//�p�[�e�B�N���̏�����
				p->Start(Camera_, Param_, EmitPosition_, Filepath_);

				//�������Ԃ̃��[�J���^�C����������
				IntervalLT_ = 0.0f;

				ParticleList_.push_back(p);
			}

			//�^�C�}�[�v�Z
			IntervalLT_ += Time().DeltaTime();
			LifeLT_ += Time().DeltaTime();
		}

		//remove-erase�C�f�B�I���B
		//�폜������̂����ɂ��߂�
		auto delIt = remove_if(
			ParticleList_.begin(),
			ParticleList_.end(),
			[](Particle* p)->bool { return p->GetDead(); }
		);

		//���߂���[�̃C�e���[�^����I�[�܂ō폜
		ParticleList_.erase(delIt, ParticleList_.end());

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
		for (auto it : ParticleList_) 
		{
			it->AddForce(addForce);
		}
	}

}// namespace nkEngine