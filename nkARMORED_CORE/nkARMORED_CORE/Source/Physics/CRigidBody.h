#pragma once

class CCollider;

//剛体情報
struct SRigidBodyInfo
{
	SRigidBodyInfo():
		Collider(nullptr),
		Mass(0.0f),
		Position(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		Rotation(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
	{

	}
	D3DXVECTOR3 Position; //座標
	D3DXQUATERNION Rotation; //回転
	CCollider* Collider; //コライダー
	float Mass; //質量
};

//剛体クラス
class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();
	void Release();
	void Create(SRigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return m_RigidBody;
	}
private:
	btRigidBody* m_RigidBody; //剛体
	btDefaultMotionState* m_MotionState; //モーションステート
};