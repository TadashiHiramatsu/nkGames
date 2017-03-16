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
	* カプセルコライダー作成.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*
	* @param	radius	The radius.
	* @param	height	The height.
	*/
	void CapsuleCollider::Create(float radius, float height)
	{
		Shape_ = new btCapsuleShape(radius, height);
	}

}// namespace nkEngine