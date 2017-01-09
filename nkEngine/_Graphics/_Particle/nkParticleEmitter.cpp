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
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	ParticleEmitter::ParticleEmitter() :
		isCreate_(false)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	ParticleEmitter::~ParticleEmitter()
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
	void ParticleEmitter::Init(Camera* camera, const ParicleParameterS& param, D3DXVECTOR3* emitPosition)
	{
		
		Camera_ = camera;
		Param_ = param;
		EmitPosition_ = emitPosition;

		Timer_ = 0.0f;

		//テクスチャのロード
		Texture_.Load(Param_.TexturePath_);

	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void ParticleEmitter::Update()
	{

		if (Timer_ >= Param_.IntervalTime_ && isCreate_) 
		{
			//パーティクルを生成。
			Particle* p = new Particle();

			//パーティクルの初期化
			p->Init(Camera_, Param_, EmitPosition_);
			
			Timer_ = 0.0f;
			
			//パーティクルの登録
			ParticleList_.push_back(p);

		}

		//タイマー計算
		Timer_ += Time().DeltaTime();

		auto p = ParticleList_.begin();

		//パーティクルが死んでいるならリストから削除
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
	 * 描画.
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