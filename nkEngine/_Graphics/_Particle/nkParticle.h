/**
 * @file _Graphics\_Particle\nkParticle.h
 *
 * パーティクルクラスの定義.
 */
#pragma once

namespace nkEngine
{
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

		/** Values that represent states. */
		enum StateE 
		{
			StateRun = 0,	//!< 生存.
			StateFadeOut,	//!< フェードアウト.
			StateDead,		//!< 死.
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
		void Start(Camera* camera, const ParticleParameterS& param, D3DXVECTOR3& emitPosition, char* filepath);

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
		void AddForce(const D3DXVECTOR3 addForce)
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
		bool GetDead() 
		{
			return isDead_;
		}

	private:

		/** プリミティブ. */
		Primitive Primitive_; 
		/** エフェクト. */
		Effect* Effect_;
		/** カメラ. */
		Camera* Camera_;

		/** The texture. */
		Texture Texture_;

		/** ワールド行列. */
		D3DXMATRIX WorldMatrix_;
		/** スケール行列. */
		D3DXMATRIX ScaleMatrix_;
		/** The scale. */
		D3DXVECTOR3	Scale_;
	
		/** ライフ. */
		float Life_ = 0.0f;
		/** タイマー. */
		float Timer_ = 0.0f;
		/** 速度. */
		D3DXVECTOR3 Velocity_ = D3DXVECTOR3(0, 0, 0);
		/** 座標. */
		D3DXVECTOR3	Position_ = D3DXVECTOR3(0, 0, 0);
		/** 重力. */
		D3DXVECTOR3	Gravity_ = D3DXVECTOR3(0, 0, 0);
		/** Z軸周りの回転. */
		float RotateZ_ = 0;
		/** 速度の積分のときのランダム幅. */
		D3DXVECTOR3 AddVelocityRandomMargih_ = D3DXVECTOR3(0, 0, 0);
		/** 死亡フラグ. */
		bool isDead_ = false;
		/** 死ぬときにフェードアウトする？. */
		bool isFade_ = false;
		/** フェードの時間. */
		float FadeTime_ = 0.0f;
		/** 状態. */
		StateE State_;
		/** 初期アルファ. */
		float InitAlpha_ = 1.0f;
		/** アルファ. */
		float Alpha_ = 1.0f;
		/** ビルボード？. */
		bool isBillboard_ = false;
		/** 外部から加わる力. */
		D3DXVECTOR3 ApplyForce_ = D3DXVECTOR3(0, 0, 0);
		/** 輝度。ブルームが有効になっているとこれを強くすると光が溢れます. */
		float Brightness_ = 0.0f;
		/** 0半透明合成、1加算合成. */
		int	AlphaBlendMode_ = 0;

	};

}// namespace nkEngine