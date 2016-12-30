#pragma once

#include"IItem.h"

class DropItem : public IGameObject
{
public:
	DropItem();
	~DropItem();
	void Start()override;
	void Update()override;
	void Render()override;

	void SetTransform(const Transform& _tf)
	{
		transform = _tf;
	}

private:
	CSkinModelDataHandle SkinModelData;
	CModelRender Model;
	CLight Light;

	//è¡ñ≈éûä‘
	float DeleteTime;
	float LocalTime = 0;
};