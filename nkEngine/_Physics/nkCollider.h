/**
 * @file	_Physics\nkCollider.h
 *
 * コライダークラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * コライダークラス.
	 * コライダーの基底クラス.
	 * 剛体の使用するコライダーはこのクラスを継承し作成する.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class ICollider
	{
	public:

		/**
		 * ボディの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		virtual btCollisionShape* GetBody() = 0;

	};

}// namespace nkEngine