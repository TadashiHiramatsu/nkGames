#pragma once

class Skybox : public CGameObject
{
public:
	Skybox();
	~Skybox();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;

	void SetPosition(D3DXVECTOR3& pos)
	{
		Transform.SetPosition(pos);
	}

private:
	CTransform Transform;
	CLight Light;
	CModelRender Model;
};