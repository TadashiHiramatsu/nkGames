#pragma once

#include"CPlayer.h"
class CPlayer;
#include"CGround.h"
class CGround;
#include"CObject.h"
class CObject;

#include"CGameCamera.h"

class CGameScene : public CScene
{
public:
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;
private:
	CPlayer m_player;
	CGround m_ground;
	CObject m_object;
};