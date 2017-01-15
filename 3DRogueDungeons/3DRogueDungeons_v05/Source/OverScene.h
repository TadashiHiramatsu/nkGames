#pragma once

#include"IncludeManagers.h"

#include"Scene.h"
#include"SceneManager.h"

#include"OverBack.h"

class CSceneManager;

class COverScene :public CScene
{
public:
	COverScene(const string& name) : CScene(name){ }
	void Initialize();
	void Update();
	void Draw();
	HRESULT CreateSprite();	//スプライト生成関数
private:
	LPD3DXSPRITE m_pSprite;	//スプライト
	COverBack* m_pOverBack;
};