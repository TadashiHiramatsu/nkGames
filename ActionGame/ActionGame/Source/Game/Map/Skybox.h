#pragma once

#include"..\Player\Player.h"
class Player;

class Skybox : public IGameObject
{
public:
	Skybox();
	~Skybox();
	void Start()override;
	void Update()override;
	void Render()override;
	void Release()override;

	void SetPlayerPointer(Player* _pla)
	{
		player = _pla;
	}

private:
	CLight Light;
	CModelRender Model;

	Player* player;
};