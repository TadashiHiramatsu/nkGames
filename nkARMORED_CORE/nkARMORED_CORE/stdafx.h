#pragma once

#include"nkEngine/nkstdafx.h"
using namespace nkEngine;

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include"Source\Graphics\CACModelRender.h"
#include"Source\Armoredcore\CParts.h"

static const float GAME_DELTA_TIME = 1.0f / 60.0f; //1�t���[���̌o�ߎ���(�P��:�b)�B�Œ�FPS

#include"Source\Physics\CPhysics.h"