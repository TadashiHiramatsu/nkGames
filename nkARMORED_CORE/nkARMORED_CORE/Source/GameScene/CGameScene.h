#pragma once

#include"CPlayer.h"
class CPlayer;
#include"CGround.h"
class CGround;

#include"CGameCamera.h"

class CGameScene : public CScene
{
public:
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;
private:
	CPlayer* m_player;
	CPlayer m_p;
	CGround m_ground;
};