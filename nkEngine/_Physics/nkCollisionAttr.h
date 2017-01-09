/**
 * @file	_Physics\nkCollisionAttr.h
 *
 * コリジョンの属性を定義.
 */
#pragma once

namespace nkEngine
{

	/** コリジョンの属性. */
	enum ECollisionAttr
	{
		CollisionAttr_Ground,		//!< 地面
		CollisionAttr_Character,	//!< キャラクター
		CollisionAttr_User,			//!< ユーザー定義
	};

}// namespace nkEngine