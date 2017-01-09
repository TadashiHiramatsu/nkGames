/**
 * @file	_Physics\nkCapsuleCollider.cpp
 *
 * カプセルコライダークラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkCapsuleCollider.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	CapsuleCollider::CapsuleCollider():
		Shape_(nullptr)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	CapsuleCollider::~CapsuleCollider()
	{
		delete Shape_;
	}
	
}// namespace nkEngine