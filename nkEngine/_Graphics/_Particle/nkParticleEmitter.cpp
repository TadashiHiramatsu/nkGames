/**
 * @file _Graphics\_Particle\nkParticleEmitter.cpp
 *
 * パーティクルエミッタクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkParticleEmitter.h"

namespace nkEngine
{

	/**
	 * 初期化. オーバーライドじゃないため自分で呼ぶ必要がある.
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

		//ファイルパスの作成
		char* baseDir = "Particle/";
		strcpy(Filepath_, baseDir);
		strcat(Filepath_, param.TexturePath_);
	}

	/**
	 * 更新.
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
				//発生時間が経過しているのでパーティクル作成

				//パーティクルを生成。
				Particle* p = NewGO<Particle>();

				//パーティクルの初期化
				p->Start(Camera_, Param_, EmitPosition_, Filepath_);

				//発生時間のローカルタイムを初期化
				IntervalLT_ = 0.0f;

				ParticleList_.push_back(p);
			}

			//タイマー計算
			IntervalLT_ += Time().DeltaTime();
			LifeLT_ += Time().DeltaTime();
		}

		//remove-eraseイディオム。
		//削除するものを後ろにためる
		auto delIt = remove_if(
			ParticleList_.begin(),
			ParticleList_.end(),
			[](Particle* p)->bool { return p->GetDead(); }
		);

		//貯めた先端のイテレータから終端まで削除
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