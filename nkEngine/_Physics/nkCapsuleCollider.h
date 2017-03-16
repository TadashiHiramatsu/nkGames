/**
 * @file	_Physics\nkCapsuleCollider.h
 *
 * カプセルコライダークラスの定義.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * カプセルコライダー.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CapsuleCollider : public ICollider
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CapsuleCollider()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CapsuleCollider()
		{
		}

		/**
		 * カプセルコライダー作成.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	radius	The radius.
		 * @param	height	The height.
		 */
		void Create(float radius, float height);

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

		/** カプセル形状. */
		btCapsuleShape* Shape_ = nullptr;
	
	};

}// namespace nkEngine