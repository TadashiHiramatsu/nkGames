/**
 * @file _Graphics\_Particle\nkParticleEmitter.h
 *
 * パーティクルエミッタクラスの定義.
 */
#pragma once

#include"nkParticle.h"

namespace nkEngine
{

	/**
	 * パーティクルパラメータ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	struct ParticleParameterS
	{
	public:

		/** テクスチャのファイルパス. */
		const char* TexturePath_;
		/** 初速度. */
		D3DXVECTOR3	InitVelocity_;
		/** 寿命。単位は秒. */
		float		Life_;
		/** 発生時間。単位は秒. */
		float		IntervalTime_;
		/** パーティクルの幅. */
		float		W_;
		/** パーティクルの高さ. */
		float		H_;
		/** 初期位置のランダム幅. */
		D3DXVECTOR3	InitPositionRandomMargin_;
		/** 初速度のランダム幅. */
		D3DXVECTOR3	InitVelocityVelocityRandomMargin_;
		/** 速度の積分のときのランダム幅. */
		D3DXVECTOR3	AddVelocityRandomMargih_;
		/** UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる. */
		D3DXVECTOR4	UVTable_[4];
		/** UVテーブルのサイズ. */
		int			UVTableSize_;
		/** 重力. */
		D3DXVECTOR3	Gravity_;
		/** 死ぬときにフェードアウトする？. */
		bool		isFade_;
		/** フェードする時間. */
		float		FadeTime_;
		/** 初期アルファ値. */
		float		InitAlpha_;
		/** ビルボード？. */
		bool		isBillboard_;
		/** 輝度。ブルームが有効になっているとこれを強くすると光が溢れます. */
		float		Brightness_;
		/** 0半透明合成、1加算合成. */
		int			AlphaBlendMode_;

	};

	/**
	 * パーティクルエミッタクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class ParticleEmitter : public IGameObject
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		ParticleEmitter()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~ParticleEmitter()
		{
		}

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
		void Start(Camera* camera, const ParticleParameterS& param, D3DXVECTOR3& emitPosition,float lifeTime);

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update()override;

		/**
		 * パーティクルに力を加える.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param force 力.
		 */
		void AddForce(const D3DXVECTOR3& force);

	private:

		/** 発生時間のローカルタイム. */
		float IntervalLT_ = 0.0f;
		/** カメラ. */
		Camera*	Camera_ = nullptr;
		/** パラメータ. */
		ParticleParameterS Param_;
		/** エミッターの座標. */
		D3DXVECTOR3 EmitPosition_;
		/** パーティクルのリスト. */
		list<Particle*>	ParticleList_;

		/** エミッタの寿命. */
		float LifeTime_ = 0.0f;
		/** エミッタの寿命のローカルタイム. */
		float LifeLT_ = 0.0f;

		/** ファイルパス. */
		char Filepath_[64];

	};
}