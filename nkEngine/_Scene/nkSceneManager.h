/**
 * @file	_Scene\nkSceneManager.h
 *
 * シーンマネージャクラスの定義.
 */
#pragma once

#include"nkScene.h"

namespace nkEngine
{

	/**
	 * シーンマネージャクラス.
	 * シングルトンクラス.
	 * このクラスにISceneクラスを継承したクラスを登録する.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CSceneManager
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CSceneManager()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CSceneManager()
		{
		}

	public:

		/**
		 * インスタンスの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The instance.
		 */
		static CSceneManager& GetInstance()
		{
			static CSceneManager instance;
			return instance;
		}

		/**
		 * ISceneクラス継承クラスの初期化を呼び出して 
		 * GameObjectManagerクラスを初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @tparam	TScene	ISceneクラスを継承したクラス.
		 */
		template <class TScene>
		void ChangeScene()
		{
			SAFE_DELETE(NowScene_);

			//シーンクラスの作成
			TScene* scene = new TScene;

			//ナウシーンに設定
			NowScene_ = scene;

			//登録されているゲームオブジェクトを全削除
			GameObjectManager().AllDelete();
			
			//シーンクラスの初期化
			NowScene_->Start();
			
			//グラフィックの初期化
			ScreenRender().StartGraphic(NowScene_->GetGraphicsConfig());

		}

	private:

		/** シーンクラス. */
		IScene* NowScene_ = nullptr;

	};

	/**
	 * シーンマネージャーの取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to a CSceneManager.
	 */
	inline CSceneManager& SceneManager()
	{
		return CSceneManager::GetInstance();
	}

}// namespace nkEngine