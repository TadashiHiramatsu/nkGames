/**
 * @file _GameObject\nkGameObject.cpp
 *
 * ゲームオブジェクトクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkGameObject.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	IGameObject::IGameObject() :
		isActive_(true),
		isStart_(false)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	IGameObject::~IGameObject()
	{
	}

}// namespace nkEngine