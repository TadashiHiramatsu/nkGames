/**
 * @file	_Physics\nkSphereCollider.h
 *
 * 球体コライダークラスの定義.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * 球体コライダークラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class SphereCollider : public ICollider
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		SphereCollider()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~SphereCollider()
		{
		}

		/**
		 * 球体コライダー作成.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	radius	半径.
		 */
		void Create(const float radius);

		/**
		 * ボディの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		btCollisionShape* GetBody()override
		{
			return Shape_;
		}

		/**
		* 解放.
		*/
		void Release()override
		{
			SAFE_DELETE(Shape_);
		}

	private:

		/** 球体形状. */
		btSphereShape* Shape_ = nullptr;
	
	};

}