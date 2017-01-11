/**
 * @file	_Physics\nkSphereCollider.cpp
 *
 * 球体コライダークラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSphereCollider.h"

namespace nkEngine
{

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	SphereCollider::SphereCollider() :
		Shape_(nullptr)
	{
	}

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	SphereCollider::~SphereCollider()
	{
		SAFE_DELETE(Shape_);
	}

	/**
	 * 球体コライダーの作成.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param	radius	The 半径.
	 */
	void SphereCollider::Create(const float radius)
	{
		Shape_ = new btSphereShape(radius);
	}

}// namespace nkEngine