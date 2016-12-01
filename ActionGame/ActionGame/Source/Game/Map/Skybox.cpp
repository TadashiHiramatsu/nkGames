#include"stdafx.h"
#include"Skybox.h"

#include"..\GameCamera.h"

Skybox::Skybox()
{

}

Skybox::~Skybox()
{

}

void Skybox::Start()
{
	Model.Load("Skybox.x", nullptr);
	Model.SetCamera(g_MainCamera->GetCamera());
	Model.SetTransform(&transform);
	Model.SetLight(&Light);

	Light.SetAmbientLight(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Skybox::Update()
{
	transform.Position = player->transform.Position;

	transform.Update();

	Model.Update();
}

void Skybox::Render()
{
	Model.Render();
}

void Skybox::Release()
{
	Model.Release();
}
