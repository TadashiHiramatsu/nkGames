#pragma once

#include"Player\Player.h"
#include"Map\Ground.h"
#include"Map\Skybox.h"

#include"Monster\MonsterHabitat.h"

class GameScene : public CScene
{
public:
	GameScene();
	~GameScene();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;
private:
	Player Player;
	Ground Ground;
	Skybox Skybox;

	MonsterHabitat TestMH;

	TestFont MouseX;
	TestFont MouseY;
};

extern Player* g_Player;