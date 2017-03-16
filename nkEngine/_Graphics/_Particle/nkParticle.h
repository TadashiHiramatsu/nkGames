/**
 * @file _Graphics\_Particle\nkParticle.h
 *
 * パーティクルクラスの定義.
 */
#pragma once

namespace nkEngine
{
	/** パーティクルのパラメータ. */
	struct ParticleParameterS;

	/**
	 * パーティクルクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Particle : public IGameObject
	{
	public:

		/** 状態. */
		enum class StateCodeE 
		{
			Run = 0,	//!< 生存.
			FadeOut,	//!< フェードアウト.
			Dead,		//!< 死.
		};

	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Particle()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Particle()
		{
		}

		/**
		 * 初期化. オーバーライドしていないので自分で呼ぶ必要あり.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param [in,out] camera	    If non-null, the camera.
		 * @param 		   param	    The parameter.
		 * @param [in,out] emitPosition If non-null, the emit position.
		 * @param [in,out] filepath	    If non-null, the filepath.
		 */
		void Start(const Camera* camera, const ParticleParameterS& param, const Vector3& emitPosition, char* filepath);

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update()override;

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] texture If non-null, the texture.
		 */
		void Render()override;

		/**
		 * Adds a force.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param addForce The add force.
		 */
		void AddForce(const Vector3 addForce)
		{
			ApplyForce_ = addForce;
		}

		/**
		 * Gets the dead.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool GetDead() const
		{
			return isDead_;
		}

	private:

		/** プリミティブ. */
		Primitive Primitive_; 
		/** エフェクト. */
		Effect* Effect_;
		/** カメラ. */
		const Camera* Camera_;

		/** The texture. */
		Texture Texture_;

		/** ワールド行列. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** スケール行列. */
		Matrix ScaleMatrix_ = Matrix::Identity;
		/** The scale. */
		Vector3	Scale_ = Vector3::One;
	
		/** ライフ. */
		float Life_ = 0.0f;
		/** タイマー. */
		float Timer_ = 0.0f;
		/** 速度. */
		Vector3 Velocity_ = Vector3::Zero;
		/** 座標. */
		Vector3	Position_ = Vector3::Zero;
		/** 重力. */
		Vector3	Gravity_ = Vector3::Zero;
		/** Z軸周りの回転. */
		float RotateZ_ = 0;
		/** 速度の積分のときのランダム幅. */
		Vector3 AddVelocityRandomMargih_ = Vector3::Zero;
		/** 死亡フラグ. */
		bool isDead_ = false;
		/** 死ぬときにフェードアウトする？. */
		bool isFade_ = false;
		/** フェードの時間. */
		float FadeTime_ = 0.0f;
		/** 状態. */
		StateCodeE State_;
		/** 初期アルファ. */
		float InitAlpha_ = 1.0f;
		/** アルファ. */
		float Alpha_ = 1.0f;
		/** ビルボード？. */
		bool isBillboard_ = false;
		/** 外部から加わる力. */
		Vector3 ApplyForce_ = Vector3::Zero;
		/** 輝度。ブルームが有効になっているとこれを強くすると光が溢れます. */
		float Brightness_ = 0.0f;
		/** 0半透明合成、1加算合成. */
		int	AlphaBlendMode_ = 0;

	};

}// namespace nkEngine