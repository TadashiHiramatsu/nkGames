/**
 * @file	_Physics\nkBoxCollider.h
 *
 * ボックスコライダークラスの定義.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * ボックスコライダークラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class BoxCollider : public ICollider
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		BoxCollider()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~BoxCollider()
		{
		}

		/**
		 * ボックスコライダー作成.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	size	サイズ.
		 */
		void Create(const D3DXVECTOR3& size);

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

		void Release()override
		{
			SAFE_DELETE(Shape_);
		}

	private:

		/** ボックス形状. */
		btBoxShape* Shape_;
	
	};

}// namespace nkEngine