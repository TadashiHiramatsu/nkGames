#pragma once

class Ground : public IGameObject
{
public:

	Ground();
	~Ground();
	void Start()override;
	void Update()override;
	void Render()override;
	void Release()override;

private:
	CModelRender Model;
	CLight Light;

	CRigidBody RigidBody;
	CMeshCollider MeshCollider;

	D3DXMATRIX* mWorld;

	CTexture Normal;
	CTexture Specular;
};