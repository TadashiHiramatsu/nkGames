#pragma once

#include"nkEngine/_Component/nkCharacterController.h"

class Monster_01 : public CGameObject
{
public:
	enum AnimationCode
	{
		AnimationInvalid = -1,
		AnimationWaiting = 0,
	};
	enum StateCode
	{
		StateWaiting = 0,
		StateLoitering,
	};
public:
	Monster_01();
	~Monster_01();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;

	void ChangeState(StateCode _NextState)
	{
		State = _NextState;
	}
private:
	CTransform Transform;
	CLight Light;
	CModelRender Model;
	CAnimation Animation;

	StateCode State;

	D3DXVECTOR2 Destination;
	D3DXVECTOR2 DefaultPosition;

	CharacterController CharacterController;
};