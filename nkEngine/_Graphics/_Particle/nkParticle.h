//パーティクル本体
#pragma once

#define PI 3.14159265358979323846f

namespace nkEngine
{
	struct SParicleEmitParameter;

	class CParticle
	{
	public:
		enum eState {
			eStateRun,
			eStateFadeOut,
			eStateDead,
		};
	public:
		//コンストラクタ
		CParticle();
		//デストラクタ
		~CParticle();
		
		//初期化
		void Init(CCamera* camera, const SParicleEmitParameter& param,D3DXVECTOR3* emitPosition);
		
		//更新
		void Update();

		//描画
		void Render(IDirect3DTexture9* _pTextures);


		void AddForce(const D3DXVECTOR3 _AddForce)
		{
			this->applyForce = _AddForce;
		}

		bool GetDead() { return isDead; }
	private:
		//プリミティブ
		CPrimitive primitive; 
		//シェーダーエフェクト
		ID3DXEffect* Effect;
		CCamera* camera;

		D3DXMATRIX		mWorld;	//ワールド行列。
		D3DXVECTOR3		vScale;
		D3DXMATRIX		mScale;	//スケール行列

		float			life;						//!<ライフ。
		float			timer;						//!<タイマー。
		D3DXVECTOR3		velocity;					//!<速度。
		D3DXVECTOR3		position;					//!<座標。
		D3DXVECTOR3		gravity;					//!<重力。
		float			rotateZ;					//!<Z軸周りの回転。
		D3DXVECTOR3		addVelocityRandomMargih;	//!<速度の積分のときのランダム幅。
		bool			isDead;						//!<死亡フラグ。
		bool			isFade;						//!<死ぬときにフェードアウトする？
		float			fadeTIme;					//!<フェードの時間。
		eState			state;						//!<状態。
		float			initAlpha;					//!<初期アルファ。
		float			alpha;						//!<アルファ。
		bool			isBillboard;				//!<ビルボード？
		D3DXVECTOR3		applyForce;					//!<外部から加わる力。
		float			brightness;					//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		int				alphaBlendMode;				//!<0半透明合成、1加算合成。
	};

}