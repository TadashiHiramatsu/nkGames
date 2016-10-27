#include"stdafx.h"
#include"Skybox.h"

#include"..\GameCamera.h"

Skybox::Skybox()
{

}

Skybox::~Skybox()
{

}

void Skybox::Init()
{
	Model.Load("Skybox.x", nullptr);
	Model.SetCamera(MainCamera.GetCamera());
	Model.SetTransform(&Transform);
	Model.SetLight(&Light);

	Light.SetAmbientLight(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Skybox::Update()
{
	Model.Update();
}

void Skybox::Render()
{
	Model.Render();
}

void Skybox::Release()
{

}

