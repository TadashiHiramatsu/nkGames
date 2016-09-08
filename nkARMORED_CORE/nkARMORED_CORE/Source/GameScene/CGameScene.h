#pragma once

#include"CPlayer.h"
#include"CGround.h"
#include"CObject.h"
#include"CSkybox.h"
#include"CBuilding.h"
class CBuilding;

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
	CSkybox m_skybox;
	CBuilding m_building;
};