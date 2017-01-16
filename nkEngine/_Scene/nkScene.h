/**
 * @file	_Scene\nkScene.h
 *
 * シーンクラスの定義.
 */
#pragma once 

#include"..\_Graphics\nkGraphicsConfig.h"

namespace nkEngine
{
	/**
	 * シーンの基底クラス.
	 * このクラスを継承するシーンクラスを作成して
	 * シーンマネージャに登録する必要がある
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class IScene
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		IScene();

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		virtual ~IScene();

	public:

		/**
		 * 初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		virtual void Start() = 0;

		/**
		 * グラフィックコンフィグの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The graphics configuration.
		 */
		const GraphicsConfigS& GetGraphicsConfig() const
		{
			return GraphicsConfig_;
		}

	protected:

		/** グラフィックの設定. */
		GraphicsConfigS GraphicsConfig_;
	
	};
}
