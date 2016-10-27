#include"nkEngine/nkstdafx.h"
#include"CMeshCollider.h"

namespace nkEngine
{

	CMeshCollider::CMeshCollider() :
		m_MeshShape(nullptr),
		m_StridingMeshInterface(nullptr)
	{
	}

	CMeshCollider::~CMeshCollider()
	{
		for (auto& vb : m_VertexBufferArray) {
			delete vb;
		}
		for (auto& ib : m_IndexBufferArray) {
			delete ib;
		}
		delete m_StridingMeshInterface;
	}

	void CMeshCollider::Create(CModelRender * model, const D3DXMATRIX * offsetMatrix)
	{
		m_StridingMeshInterface = new btTriangleIndexVertexArray;
		//CSkinModelからコリジョンで使用する、頂点バッファとインデックスバッファを作成する。
		LPD3DXMESH mesh = model->GetOrgMeshFirst();
		if (mesh != NULL)
		{
			{
				//頂点ストライドを取得
				DWORD stride = D3DXGetFVFVertexSize(mesh->GetFVF());
				//頂点バッファを取得
				LPDIRECT3DVERTEXBUFFER9 vb;
				mesh->GetVertexBuffer(&vb);
				//頂点バッファの定義を取得する
				D3DVERTEXBUFFER_DESC desc;
				vb->GetDesc(&desc);
				//頂点バッファをロックする
				D3DXVECTOR3* pos;
				vb->Lock(0, 0, (void**)&pos, D3DLOCK_READONLY);
				VertexBuffer* vertexBuffer = new VertexBuffer;
				int numVertex = mesh->GetNumVertices();
				//当たりデータで使用する頂点バッファを作成
				for (int v = 0; v < numVertex; v++) {
					D3DXVECTOR3 posTmp = *pos;
					if (offsetMatrix) {
						D3DXVECTOR3 vTmp = posTmp;
						posTmp.x = vTmp.x * offsetMatrix->m[0][0] + vTmp.y * offsetMatrix->m[1][0] + vTmp.z * offsetMatrix->m[2][0] + offsetMatrix->m[3][0];
						posTmp.y = vTmp.x * offsetMatrix->m[0][1] + vTmp.y * offsetMatrix->m[1][1] + vTmp.z * offsetMatrix->m[2][1] + offsetMatrix->m[3][1];
						posTmp.z = vTmp.x * offsetMatrix->m[0][2] + vTmp.y * offsetMatrix->m[1][2] + vTmp.z * offsetMatrix->m[2][2] + offsetMatrix->m[3][2];
					}
					vertexBuffer->push_back(posTmp);
					char* p = (char*)pos;
					p += stride;
					pos = (D3DXVECTOR3*)p;
				}
				vb->Unlock();
				vb->Release();
				m_VertexBufferArray.push_back(vertexBuffer);
			}
			{
				//続いてインデックスバッファを作成。
				LPDIRECT3DINDEXBUFFER9 ib;
				mesh->GetIndexBuffer(&ib);
				D3DINDEXBUFFER_DESC desc;
				ib->GetDesc(&desc);
				int stride = 0;
				if (desc.Format == D3DFMT_INDEX16) {
					//インデックスが16bit
					stride = 2;
				}
				else if (desc.Format == D3DFMT_INDEX32) {
					//インデックスが32bit
					stride = 4;
				}
				//インデックスバッファをロック。
				char* p;
				HRESULT hr = ib->Lock(0, 0, (void**)&p, D3DLOCK_READONLY);
				IndexBuffer* indexBuffer = new IndexBuffer;
				for (int i = 0; i < desc.Size / stride; i++) {
					unsigned int index;
					if (desc.Format == D3DFMT_INDEX16) {
						unsigned short* pIndex = (unsigned short*)p;
						index = (unsigned int)*pIndex;
					}
					else {
						unsigned int* pIndex = (unsigned int*)p;
						index = *pIndex;
					}

					indexBuffer->push_back(index);
					p += stride;
				}
				ib->Unlock();
				//ib->Release();
				m_IndexBufferArray.push_back(indexBuffer);
			}
			//インデックスメッシュを作成。
			btIndexedMesh indexedMesh;
			IndexBuffer* ib = m_IndexBufferArray.back();
			VertexBuffer* vb = m_VertexBufferArray.back();
			indexedMesh.m_numTriangles = ib->size() / 3;
			indexedMesh.m_triangleIndexBase = (unsigned char*)(&ib->front());
			indexedMesh.m_triangleIndexStride = 12;
			indexedMesh.m_numVertices = vb->size();
			indexedMesh.m_vertexBase = (unsigned char*)(&vb->front());
			indexedMesh.m_vertexStride = sizeof(D3DXVECTOR3);
			m_StridingMeshInterface->addIndexedMesh(indexedMesh);

		}
		m_MeshShape = new btBvhTriangleMeshShape(m_StridingMeshInterface, true);
	}

}