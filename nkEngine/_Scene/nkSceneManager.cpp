/**
 * @file	_Scene\nkSceneManager.cpp
 *
 * シーンマネージャクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSceneManager.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	CSceneManager::CSceneManager() :
		NowScene_(nullptr)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	CSceneManager::~CSceneManager()
	{
	}

}// namespace nkEngine