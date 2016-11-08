#pragma once

#include"nkParticle.h"

namespace nkEngine
{
	struct SParicleEmitParameter {
		//初期化。
		void Init()
		{
			memset(this, 0, sizeof(SParicleEmitParameter));
			initAlpha = 1.0f;
			brightness = 1.0f;
			isBillboard = true;
		}
		const char* texturePath;						//!<テクスチャのファイルパス。
		D3DXVECTOR3	initVelocity;						//!<初速度。
		float		life;								//!<寿命。単位は秒。
		float		intervalTime;						//!<発生時間。単位は秒。
		float		w;									//!<パーティクルの幅。
		float		h;									//!<パーティクルの高さ。
		D3DXVECTOR3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		D3DXVECTOR3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		D3DXVECTOR4	uvTable[4];							//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
		int			uvTableSize;						//!<UVテーブルのサイズ。
		D3DXVECTOR3	gravity;							//!<重力。
		bool		isFade;								//!<死ぬときにフェードアウトする？
		float		fadeTime;							//!<フェードする時間。
		float		initAlpha;							//!<初期アルファ値。
		bool		isBillboard;						//!<ビルボード？
		float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		int			alphaBlendMode;						//!<0半透明合成、1加算合成。
	};

	//パーティクルエミッタ
	class CParticleEmitter
	{
	public:
		//コンストラクタ
		CParticleEmitter();

		//デストラクタ
		~CParticleEmitter();

		//初期化
		void Init(CCamera* _Camera, const SParicleEmitParameter& _Param, D3DXVECTOR3* _EmitPosition);

		//更新
		void Update();

		//描画
		void Render();

		//パーティクルに力を加える
		void AddForce(const D3DXVECTOR3& _AddForce);

		//解放
		void Release()
		{
			std::list<CParticle*>::iterator p = particleList.begin();
			while (p != particleList.end()) {
				p = particleList.erase(p);
			}
			particleList.clear();
		}

		void SetCreate(bool _is)
		{
			isCreate = _is;
		}

	private:
		float					timer;			//!<タイマー
		CCamera*				camera;			//!<カメラ。
		SParicleEmitParameter	param;			//!<パラメータ。
		D3DXVECTOR3*			EmitPosition;	//エミッターの座標。
		std::list<CParticle*>	particleList;	//!<パーティクルのリスト。
		CTexture m_pTextures;
		bool isCreate;
	};
}