#pragma once

#include "nkEngine/_Physics/CMeshCollider.h"
#include "nkEngine/_Physics/CRigidBody.h"

class Ground : public CGameObject
{
public:
	Ground();
	~Ground();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;
private:
	CTransform Transform;
	CLight Light;
	CModelRender Model;

	CRigidBody RigidBody;
	CMeshCollider MeshCollider;
	D3DXMATRIX* mWorld;
};