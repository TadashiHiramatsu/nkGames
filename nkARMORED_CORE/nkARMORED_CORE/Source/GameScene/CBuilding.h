#pragma once

struct Parameter
{
	D3DXVECTOR3 pos;
	D3DXQUATERNION rot;
	D3DXVECTOR3 scale;
};

class CBuilding : public CGameObject
{
public:
	CBuilding();
	~CBuilding();
	void Init() override;
	void Update() override;
	void Render() override;
	void Release()override;
private:
	CSkinModelData			skinModelData;
	CModelRender			skinModel;			//スキンモデル。
	CLight					light;				//ライト。
	D3DXMATRIX*				worldMatrixBuffer;
	CTransform m_trans;

};