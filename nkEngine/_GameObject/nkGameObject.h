/**
 * @file _GameObject\nkGameObject.h
 *
 * ゲームオブジェクトクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/** 優先度. */
	typedef unsigned char GOPriorityT;

	/**
	 * ゲームオブジェクトマネージャに登録する基底クラス.
	 * ゲーム開発では基本このクラスを継承させる.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class IGameObject : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		IGameObject()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual ~IGameObject()
		{
		}

	public:

		/**
		 * コンストラクタの後に呼ばれる初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Awake() 
		{
		}

		/**
		 * 初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Start() 
		{
		}

		/**
		 * Updateの前に呼ばれる更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PreUpdate()
		{
		}

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Update() 
		{
		}

		/**
		 * Updateの後に呼ばれる更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PostUpdate() 
		{
		}

		/**
		 * Renderの前に呼ばれる描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PreRender() 
		{
		}

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Render() 
		{
		}

		/**
		 * ポストエフェクトの後に呼ばれる描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PostRender() 
		{
		}

		/**
		 * デストラクタの前に呼ばれる解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Release() 
		{
		}

		/**
		* データのセーブを行う.
		*/
		virtual void Save()
		{
		}

	public:

		/**
		 * コンストラクタの後に呼ばれる初期化.
		 * ラッパー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void AwakeWrapper()
		{
			if (!isStart_ && isActive_)
			{
				Awake();
			}
		}

		/**
		 * 初期化.
		 * ラッパー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void StartWrapper()
		{
			if (!isStart_ && isActive_)
			{
				Start();
				isStart_ = true;
			}
		}

		/**
		 * Updateの前に呼ばれる更新.
		 * ラッパー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PreUpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				PreUpdate();
			}
		}

		/**
		 * 更新.
		 * ラッパー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void UpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				Update();
			}
		}

		/**
		 * Updateの後に呼ばれる更新.
		 * ラッパー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PostUpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				PostUpdate();
			}
		}

		/**
		 * Renderの前に呼ばれる描画.
		 * ラッパー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PreRenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				PreRender();
			}
		}

		/**
		 * 描画.
		 * ラッパー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void RenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				Render();
			}
		}

		/**
		 * ポストエフェクトの後に呼ばれる描画.
		 * ラッパー.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PostRenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				PostRender();
			}
		}

	public:

		/**
		 * ゲームオブジェクトのisActiveを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool GetActive() const
		{
			return isActive_;
		}

		/**
		 * ゲームオブジェクトをアクティブ / 非アクティブにします.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param value True to value.
		 */
		void SetActive(bool value)
		{
			isActive_ = value;
		}

		/**
		 * 優先度を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The priority.
		 */
		GOPriorityT GetPriority() const
		{
			return Priority_;
		}

		/**
		* スタティックフラグを設定する.
		*
		* @param value	値.
		*/
		void SetStatic(bool value)
		{
			isStatic_ = value;
		}

		/**
		* スタティックフラグを取得する.
		*
		* @return 値.
		*/
		bool GetStatic()
		{
			return isStatic_;
		}

	public:

		/** トランスフォーム. */
		Transform Transform_;
		/** 優先度. */
		GOPriorityT Priority_ = 0;
		/** アクティブフラグ. */
		bool isActive_ = true;
		/** Startが呼ばれているかフラグ. */
		bool isStart_ = false;
		/** 
		* スタティックフラグ. 
		* trueの場合シーン遷移で削除されない.
		*/
		bool isStatic_ = false;

	};

}// namespace nkEngine