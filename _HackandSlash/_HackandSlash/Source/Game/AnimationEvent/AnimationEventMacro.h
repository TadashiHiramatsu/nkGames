/**
 * @file Source\Game\AnimationEvent\AnimationEventMacro.h
 *
 * アニメーションイベントのマクロを定義.
 */
#pragma once

/**
 * アニメーションイベントの終端.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
#define END_ANIMATION_EVENT()													\
	AnimationEventS(															\
		Invalid,																\
		0.0f,																	\
		0.0f, 0.0f, 0.0f, 0.0f, 												\
		0, 0, 0, 0, 															\
		NULL, NULL, NULL, NULL, 												\
		Vector3::Zero,Vector3::Zero, Vector3::Zero,Vector3::Zero)

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/**
 * 敵にダメージを与える	コリジョン発生イベント.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 *
 * @param invokeTime	    コリジョンが発生する時間。該当するアニメーションが再生されてから経過時間です。単位は秒.
 * @param life			    コリジョンが発生している時間。単位は秒.
 * @param radius		    コリジョンの半径.
 * @param damage		    ダメージ量.
 * @param boneName		    ボーン名.
 * @param offsetLocalVector ボーンからのオフセット座標.
 * @param groupID		    グループＩＤ.
 */
#define EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(invokeTime, life, radius, damage, boneName, offsetLocalVector, groupID)		\
	AnimationEventS(																			\
		EmitDamageToEnemyCollision,																\
		(invokeTime),																			\
		(life), (radius), 0.0f, 0.0f,															\
		damage,groupID,0,0,																		\
		boneName, NULL, NULL, NULL,																\
		offsetLocalVector,Vector3::Zero,Vector3::Zero,Vector3::Zero									\
	)

 /*-----------------------------------------------------------------------------------------------------------------------------------*/

/**
 * プレイヤにダメージを与える	コリジョン発生イベント.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 *
 * @param invokeTime	    コリジョンが発生する時間。該当するアニメーションが再生されてから経過時間です。単位は秒.
 * @param life			    コリジョンが発生している時間。単位は秒.
 * @param radius		    コリジョンの半径.
 * @param damage		    ダメージ量.
 * @param boneName		    ボーン名.
 * @param offsetLocalVector ボーンからのオフセット座標.
 * @param groupID		    グループＩＤ.
 */
#define EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(invokeTime, life, radius, damage, boneName, offsetLocalVector, groupID)		\
	AnimationEventS(																				\
		EmitDamageToPlayerCollision,															\
		(invokeTime),																			\
		(life), (radius), 0.0f, 0.0f,															\
		damage,groupID,0,0,																		\
		boneName, NULL, NULL, NULL,																\
		offsetLocalVector,Vector3::Zero,Vector3::Zero,Vector3::Zero									\
	)

/*-----------------------------------------------------------------------------------------------------------------------------------*/