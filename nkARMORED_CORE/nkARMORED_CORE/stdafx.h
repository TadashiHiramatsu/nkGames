#pragma once

#include"nkEngine/nkstdafx.h"
using namespace nkEngine;

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include"Source\Graphics\CACModelRender.h"
#include"Source\Armoredcore\CParts.h"

static const float GAME_DELTA_TIME = 1.0f / 60.0f; //1フレームの経過時間(単位:秒)。固定FPS

#include"Source\Physics\CPhysics.h"