#pragma once

//アニメーションイベントの終端
#define END_ANIMATION_EVENT()													\
	AnimationEvent(																\
		eAnimationEventType_Invalid,											\
		0.0f,																	\
		0.0f, 0.0f, 0.0f, 0.0f, 												\
		0, 0, 0, 0, 															\
		NULL, NULL, NULL, NULL, 												\
		D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0))

/*!
* @brief	敵にダメージを与える	コリジョン発生イベント。
*@param[in]	invokeTime			コリジョンが発生する時間。該当するアニメーションが再生されてから経過時間です。単位は秒。
*@param[in]	life				コリジョンが発生している時間。単位は秒。
*@param[in]	radius				コリジョンの半径。
*@param[in]	damage				ダメージ量。
*@param[in]	boneName			ボーン名。
*@param[in]	offsetLocalVector	ボーンからのオフセット座標。
*@param[in]	groupID				グループＩＤ。
*/
#define EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(invokeTime, life, radius, damage, boneName, offsetLocalVector, groupID)		\
	AnimationEvent(																				\
		eAnimationEventType_EmitDamageToEnemyCollision,											\
		(invokeTime),																			\
		(life), (radius), 0.0f, 0.0f,															\
		damage,groupID,0,0,																		\
		boneName, NULL, NULL, NULL,																\
		offsetLocalVector,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0)						\
	)

/*!
* @brief	プレイヤにダメージを与える	コリジョン発生イベント。
*@param[in]	invokeTime			コリジョンが発生する時間。該当するアニメーションが再生されてから経過時間です。単位は秒。
*@param[in]	life				コリジョンが発生している時間。単位は秒。
*@param[in]	radius				コリジョンの半径。
*@param[in]	damage				ダメージ量。
*@param[in]	boneName			ボーン名。
*@param[in]	offsetLocalVector	ボーンからのオフセット座標。
*@param[in]	groupID				グループＩＤ。
*/
#define EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(invokeTime, life, radius, damage, boneName, offsetLocalVector, groupID)		\
	AnimationEvent(																				\
		eAnimationEventType_EmitDamageToPlayerCollision,											\
		(invokeTime),																			\
		(life), (radius), 0.0f, 0.0f,															\
		damage,groupID,0,0,																		\
		boneName, NULL, NULL, NULL,																\
		offsetLocalVector,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0)						\
	)