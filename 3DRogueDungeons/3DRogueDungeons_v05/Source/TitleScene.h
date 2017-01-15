#pragma once

#include"IncludeManagers.h"

#include"Scene.h"
#include"SceneManager.h"

#include"TitleCursor.h"
#include"TitleBack.h"

class CSceneManager;

class CTitleScene :public CScene
{
public:
	CTitleScene(const string& name) : CScene(name){ }
	void Initialize();
	void Update();
	void Draw();
	HRESULT CreateSprite();	//�X�v���C�g�����֐�
private:
	LPD3DXSPRITE m_pSprite;	//�X�v���C�g
	CTitleCursor* m_pTitleCursor;
	CTitleBack* m_pTitleBack;
};