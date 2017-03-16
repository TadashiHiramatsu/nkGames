#include"stdafx.h"
#include"GameLight.h"

void GameLight::Start()
{
	Vector3 dld = Vector3(5.0f, -5.0f, 5.0f);
	dld.Normalize();

	Light_.SetDiffuseLightDirection(0, dld);
	Light_.SetDiffuseLightColor(0, Vector4(1, 1, 1, 0));
}
