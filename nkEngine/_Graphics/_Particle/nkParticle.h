/**
 * @file _Graphics\_Particle\nkParticle.h
 *
 * パーティクルクラスの定義.
 */
#pragma once

namespace nkEngine
{
	struct ParicleParameterS;

	/**
	 * パーティクルクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Particle
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
		Particle();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Particle();

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
		void Init(Camera* camera, const ParicleParameterS& param, D3DXVECTOR3* emitPosition);

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] texture If non-null, the texture.
		 */
		void Render(IDirect3DTexture9* texture);

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
		ID3DXEffect* Effect_;
		/** カメラ. */
		Camera* Camera_;

		/** ワールド行列. */
		D3DXMATRIX WorldMatrix_;
		/** スケール行列. */
		D3DXMATRIX ScaleMatrix_;
		/** The scale. */
		D3DXVECTOR3	Scale_;
	
		/** ライフ. */
		float Life_;
		/** タイマー. */
		float Timer_;
		/** 速度. */
		D3DXVECTOR3 Velocity_;
		/** 座標. */
		D3DXVECTOR3	Position_;
		/** 重力. */
		D3DXVECTOR3	Gravity_;
		/** Z軸周りの回転. */
		float RotateZ_;
		/** 速度の積分のときのランダム幅. */
		D3DXVECTOR3 AddVelocityRandomMargih_;
		/** 死亡フラグ. */
		bool isDead_;
		/** 死ぬときにフェードアウトする？. */
		bool isFade_;
		/** フェードの時間. */
		float FadeTime_;
		/** 状態. */
		StateE State_;
		/** 初期アルファ. */
		float InitAlpha_;
		/** アルファ. */
		float Alpha_;
		/** ビルボード？. */
		bool isBillboard_;
		/** 外部から加わる力. */
		D3DXVECTOR3 ApplyForce_;
		/** 輝度。ブルームが有効になっているとこれを強くすると光が溢れます. */
		float Brightness_;
		/** 0半透明合成、1加算合成. */
		int	AlphaBlendMode_;

	};

}// namespace nkEngine