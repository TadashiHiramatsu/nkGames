#pragma once

class Monster_01 : public CGameObject
{
public:
	Monster_01();
	~Monster_01();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;
private:
	CTransform Transform;
	CLight Light;
	CModelRender Model;
	CAnimation Animation;
};