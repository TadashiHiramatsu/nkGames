#pragma once
#include "2DImage.h"
#include"IncludeManagers.h"
#include"Player.h"

class CLifeGage : public C2DImage
{
public:
	CLifeGage();
	~CLifeGage();
	void Initialize(CPlayer*);
	void Update()override;
private:
	CPlayer* pPlayer;
	float MaxLife;
	float NowLife;
};

