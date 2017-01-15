#pragma once
#include"DXCommon.h"

class CSphereCollision
{
public:
	bool isCollision(D3DXVECTOR3 APos, float ARadius, D3DXVECTOR3 BPos, float BRadius)
	{
		float xpos = BPos.x - APos.x;
		float ypos = BPos.y - APos.y;
		float zpos = BPos.z - APos.z;
		float Radius = ARadius + BRadius;
		if ((xpos*xpos) + (ypos*ypos) + (zpos*zpos) <= Radius*Radius)
		{
			return true;
		}
		return false;
	}
};