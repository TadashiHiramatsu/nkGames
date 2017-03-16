/**
 * @file Source\Game\AnimationEvent\AnimationEventMacro.h
 *
 * �A�j���[�V�����C�x���g�̃}�N�����`.
 */
#pragma once

/**
 * �A�j���[�V�����C�x���g�̏I�[.
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
 * �G�Ƀ_���[�W��^����	�R���W���������C�x���g.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 *
 * @param invokeTime	    �R���W�������������鎞�ԁB�Y������A�j���[�V�������Đ�����Ă���o�ߎ��Ԃł��B�P�ʂ͕b.
 * @param life			    �R���W�������������Ă��鎞�ԁB�P�ʂ͕b.
 * @param radius		    �R���W�����̔��a.
 * @param damage		    �_���[�W��.
 * @param boneName		    �{�[����.
 * @param offsetLocalVector �{�[������̃I�t�Z�b�g���W.
 * @param groupID		    �O���[�v�h�c.
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
 * �v���C���Ƀ_���[�W��^����	�R���W���������C�x���g.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 *
 * @param invokeTime	    �R���W�������������鎞�ԁB�Y������A�j���[�V�������Đ�����Ă���o�ߎ��Ԃł��B�P�ʂ͕b.
 * @param life			    �R���W�������������Ă��鎞�ԁB�P�ʂ͕b.
 * @param radius		    �R���W�����̔��a.
 * @param damage		    �_���[�W��.
 * @param boneName		    �{�[����.
 * @param offsetLocalVector �{�[������̃I�t�Z�b�g���W.
 * @param groupID		    �O���[�v�h�c.
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