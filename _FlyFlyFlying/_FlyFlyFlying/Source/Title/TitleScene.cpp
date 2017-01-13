/**
 * @file Source\Title\TitleScene.cpp
 *
 * タイトルシーンクラスの実装.
 */
#include"stdafx.h"
#include"TitleScene.h"

void TitleScene::Start()
{
	
	m_camera.Initialize();
	m_camera.SetNear(0.1f);
	
	m_camera.SetDistance(4.0f);
	m_camera.RotLongitudinal(D3DXToRadian(-20.0f));
	m_camera.SetLookat(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	m_camera.UpdateProjectionMatrix();
	m_camera.Update();
	m_title.Initialize();
	m_continue.Initialize();
	m_start.Initialize();
	m_Unitychan.Init(m_Unitychan.Run);
}

void CTitleScene::Update()
{
	m_camera.Update();
	m_title.Update();
	m_continue.Update();
	m_start.Update();
	m_Unitychan.Update();

	Select();//セレクト
}

void CTitleScene::Draw()
{
	m_title.Draw();
	CDataLoad dl;
	int num = dl.LoadData();
#ifndef _DEBUG
	if (num > 0 && num<10)
#endif
	{
		m_continue.Draw();
	}
	m_start.Draw();
	(*graphicsDevice()).Clear(
		0,
		NULL,
		D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);
	m_Unitychan.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
}

void CTitleScene::Select()
{


	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_A))
		{
			STAGEMANEGER->SelectStage(1);
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

		}
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_B))
		{
			CDataLoad dl;
			int num = dl.LoadData();
			if (num > 0 && num<10)
			{
				STAGEMANEGER->SelectStage(num);
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

			}
		}
		
	}
	else
	{
		if (KEYDOWN(diks, DIK_RETURN))
		{
			STAGEMANEGER->SelectStage(1);
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

		}
		else if (KEYDOWN(diks, DIK_B))
		{
			CDataLoad dl;
			int num = dl.LoadData();
			if (num > 0 && num<10)
			{
				STAGEMANEGER->SelectStage(num);
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

			}
		
		}
		else
		{
			(*GetKeyDevice()).Acquire();//キーデバイス取得
		}
	}

}