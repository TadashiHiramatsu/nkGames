#pragma once

namespace nkEngine
{
	typedef unsigned char GOPriority; //unsigned char

	//ゲームオブジェクトマネージャに登録する基底クラス
	class IGameObject
	{
	public:

		//コンストラクタ
		IGameObject();
		//デストラクタ
		virtual ~IGameObject();

	public:
		//メンバ関数

		//コンストラクタの後に呼ばれる初期化
		virtual void Awake() {}
		//初期化
		virtual void Start() {}
		//Updateの前に呼ばれる更新
		virtual void PreUpdate() {}
		//更新
		virtual void Update() {}
		//Updateの後に呼ばれる更新
		virtual void PostUpdate() {}
		//Renderの前に呼ばれる描画
		virtual void PreRender() {}
		//描画
		virtual void Render() {}
		//ポストエフェクトの後に呼ばれる描画
		virtual void PostRender() {}
		//デストラクタの前に呼ばれる解放
		virtual void Release() {}

	public:
		//ラッパー
		//継承先のクラスでif分を削減できる

		//コンストラクタの後に呼ばれる初期化
		virtual void AwakeWrapper()
		{
			if (isStart && isActive)
			{
				Awake();
			}
		}

		//初期化
		virtual void StartWrapper()
		{
			if (!isStart && isActive)
			{
				Start();
				isStart = true;
			}
		}

		//Updateの前に呼ばれる更新
		virtual void PreUpdateWrapper()
		{
			if (isStart && isActive)
			{
				PreUpdate();
			}
		}

		//更新
		virtual void UpdateWrapper()
		{
			if (isStart && isActive)
			{
				Update();
			}
		}

		//Updateの後に呼ばれる更新
		virtual void PostUpdateWrapper()
		{
			if (isStart && isActive)
			{
				PostUpdate();
			}
		}

		//Renderの前に呼ばれる描画
		virtual void PreRenderWrapper()
		{
			if (isStart && isActive)
			{
				PreRender();
			}
		}

		//描画
		virtual void RenderWrapper()
		{
			if (isStart && isActive)
			{
				Render();
			}
		}

		//ポストエフェクトの後に呼ばれる描画
		virtual void PostRenderWrapper()
		{
			if (isStart && isActive)
			{
				PostRender();
			}
		}

	public:
		//ゲッタ、セッタ

		//ゲームオブジェクトのisActiveを取得
		bool GetActive() const
		{
			return isActive;
		}
		//ゲームオブジェクトをアクティブ / 非アクティブにします
		void SetActive(bool _value)
		{
			isActive = _value;
		}

		//優先度を取得
		GOPriority GetPriority() const
		{
			return priority;
		}

	public:
		//メンバ変数(外部から見える)
		
		//コンポーネント
		Transform transform; //トランスフォーム

		GOPriority priority; //優先度
		bool isActive; //アクティブフラグ
		bool isStart; //Startが呼ばれているかフラグ
	};
}