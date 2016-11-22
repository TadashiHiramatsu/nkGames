#pragma once

#include"IItem.h"

class DropItem : public CGameObject
{
public:
	DropItem();
	~DropItem();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;

	void SetTransform(CTransform& _tf)
	{
		Transform = _tf;
	}
private:
	CModelRender Model;
	CTransform Transform;
	CLight Light;

	//���Ŏ���
	float DeleteTime;
	float LocalTime = 0;
};