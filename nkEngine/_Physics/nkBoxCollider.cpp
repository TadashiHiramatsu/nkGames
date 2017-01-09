/**
 * @file	_Physics\nkBoxCollider.cpp
 *
 * ボックスコライダークラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkBoxCollider.h"

namespace nkEngine
{

	/**
	* コンストラクタ.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*/
	BoxCollider::BoxCollider() :
		Shape_(nullptr)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	BoxCollider::~BoxCollider()
	{
		SAFE_DELETE(Shape_);
	}

	/**
	 * ボックス形状の作成.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param	size	サイズ.
	 */
	void BoxCollider::Create(const D3DXVECTOR3 & size)
	{
		Shape_ = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
	}

}// namespace nkEngine