#include"nkEngine/nkstdafx.h"
#include"nkGameObject.h"

namespace nkEngine
{
	IGameObject::IGameObject() :
		isActive(true),
		isStart(false)
	{
	}

	IGameObject::~IGameObject()
	{
	}
}