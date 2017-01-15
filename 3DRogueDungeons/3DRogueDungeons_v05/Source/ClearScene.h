#pragma once

#include"IncludeManagers.h"

#include"Scene.h"
#include"SceneManager.h"

#include"ClearBack.h"


class CSceneManager;

class CClearScene :public CScene
{
public:
	CClearScene(const string& name) : CScene(name){ }
	void Initialize();
	void Update();
	void Draw();
	HRESULT CreateSprite();	//�X�v���C�g�����֐�
private:
	LPD3DXSPRITE m_pSprite;	//�X�v���C�g
	CClearBack* m_pClearBack;
};