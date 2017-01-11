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
	struct ParicleParameterS 
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
	class ParticleEmitter
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		ParticleEmitter();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~ParticleEmitter();

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
		 */
		void Render();

		/**
		 * パーティクルに力を加える.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param addForce The add force.
		 */
		void AddForce(const D3DXVECTOR3& addForce);

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release()
		{
			auto p = ParticleList_.begin();

			while (p != ParticleList_.end())
			{
				p = ParticleList_.erase(p);
			}

			ParticleList_.clear();
		
		}

		/**
		 * Sets a create.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param _is True to is.
		 */
		void SetCreate(bool isCreate)
		{
			isCreate_ = isCreate;
		}

	private:

		/** タイマー. */
		float Timer_;
		/** カメラ. */
		Camera*	Camera_;
		/** パラメータ. */
		ParicleParameterS Param_;
		/** エミッターの座標. */
		D3DXVECTOR3* EmitPosition_;
		/** パーティクルのリスト. */
		list<Particle*>	ParticleList_;
		/** The texture. */
		Texture Texture_;
		/** 作成するか. */
		bool isCreate_;
	
	};
}