#pragma once

#include"Source\Physics\CCollider.h"

class CMeshCollider : public CCollider
{
public:

	//コンストラクタ
	CMeshCollider();

	//デストラクタ
	~CMeshCollider();

	//CModelRenderからMeshコライダーを生成
	//param[in] スキンモデル
	//param[in] オフセット行列
	void Create(CModelRender* model, const D3DXMATRIX* offsetMatrix);

	//ボディを取得
	btCollisionShape* GetBody() override
	{
		return m_MeshShape;
	}

private:
	typedef std::vector<D3DXVECTOR3> VertexBuffer; //頂点バッファ。
	typedef std::vector<unsigned int> IndexBuffer; //インデックスバッファ。
	std::vector<VertexBuffer*> m_VertexBufferArray; //頂点バッファの配列。
	std::vector<IndexBuffer*> m_IndexBufferArray; //インデックスバッファの配列。
	btBvhTriangleMeshShape* m_MeshShape; //メッシュ形状。
	btTriangleIndexVertexArray* m_StridingMeshInterface;
};