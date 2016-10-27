#pragma once

#include"Player\Player.h"
#include"Map\Ground.h"
#include"Map\Skybox.h"
#include"Monster\Monster_01.h"

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
	Monster_01 Monster;
};