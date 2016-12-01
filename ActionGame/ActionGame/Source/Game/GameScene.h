#pragma once

#include"Player\Player.h"

class GameScene : public IScene
{
public:
	GameScene();
	~GameScene();
	void Start()override;
};

extern Player* g_Player;