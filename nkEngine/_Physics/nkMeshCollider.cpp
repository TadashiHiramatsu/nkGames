/**
 * @file	_Physics\nkMeshCollider.cpp
 *
 * ���b�V���R���C�_�[�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkMeshCollider.h"

namespace nkEngine
{

	/**
	* CModelRender����Mesh�R���C�_�[�𐶐�.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/07
	*
	* @param [in,out]	model			�X�L�����f��.
	* @param 		  	offsetMatrix	�I�t�Z�b�g�s��.
	*/
	void MeshCollider::Create(ModelRender* model, const Matrix* offsetMatrix)
	{
		StridingMeshInterface_ = new btTriangleIndexVertexArray;

		//CSkinModel����R���W�����Ŏg�p����A���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���쐬����B
		LPD3DXMESH mesh = model->GetOrgMeshFirst();
		if (mesh != NULL)
		{
			{
				//���_�X�g���C�h���擾
				DWORD stride = D3DXGetFVFVertexSize(mesh->GetFVF());
				
				//���_�o�b�t�@���擾
				LPDIRECT3DVERTEXBUFFER9 vb;
				mesh->GetVertexBuffer(&vb);
				
				//���_�o�b�t�@�̒�`���擾����
				D3DVERTEXBUFFER_DESC desc;
				vb->GetDesc(&desc);
				
				//���_�o�b�t�@�����b�N����
				Vector3* pos;
				vb->Lock(0, 0, (void**)&pos, D3DLOCK_READONLY);

				//���_�o�b�t�@�쐬
				VertexBufferT* vertexBuffer = new VertexBufferT;
				int numVertex = mesh->GetNumVertices();

				//������f�[�^�Ŏg�p���钸�_�o�b�t�@���쐬
				for (int v = 0; v < numVertex; v++) 
				{
					//�|�W�V�����擾
					Vector3 posTmp = *pos;
					if (offsetMatrix)
					{
						Vector3 vTmp = posTmp;
						posTmp.x = vTmp.x * offsetMatrix->m[0][0] + vTmp.y * offsetMatrix->m[1][0] + vTmp.z * offsetMatrix->m[2][0] + offsetMatrix->m[3][0];
						posTmp.y = vTmp.x * offsetMatrix->m[0][1] + vTmp.y * offsetMatrix->m[1][1] + vTmp.z * offsetMatrix->m[2][1] + offsetMatrix->m[3][1];
						posTmp.z = vTmp.x * offsetMatrix->m[0][2] + vTmp.y * offsetMatrix->m[1][2] + vTmp.z * offsetMatrix->m[2][2] + offsetMatrix->m[3][2];
					}

					vertexBuffer->push_back(posTmp);
					char* p = (char*)pos;
					p += stride;
					pos = (Vector3*)p;
				}

				//�A�����b�N
				vb->Unlock();
				vb->Release();

				//�ݒ�
				VertexBufferArray_.push_back(vertexBuffer);
			}
			{
				//�����ăC���f�b�N�X�o�b�t�@���쐬�B
				LPDIRECT3DINDEXBUFFER9 ib;
				mesh->GetIndexBuffer(&ib);
				D3DINDEXBUFFER_DESC desc;
				ib->GetDesc(&desc);
				
				int stride = 0;
				if (desc.Format == D3DFMT_INDEX16) 
				{
					//�C���f�b�N�X��16bit
					stride = 2;
				}
				else if (desc.Format == D3DFMT_INDEX32) 
				{
					//�C���f�b�N�X��32bit
					stride = 4;
				}

				//�C���f�b�N�X�o�b�t�@�����b�N�B
				char* p;
				HRESULT hr = ib->Lock(0, 0, (void**)&p, D3DLOCK_READONLY);

				//�C���f�b�N�X�o�b�t�@�쐬
				IndexBufferT* indexBuffer = new IndexBufferT;

				for (int i = 0; i < desc.Size / stride; i++)
				{
					unsigned int index;
					if (desc.Format == D3DFMT_INDEX16)
					{
						unsigned short* pIndex = (unsigned short*)p;
						index = (unsigned int)*pIndex;
					}
					else
					{
						unsigned int* pIndex = (unsigned int*)p;
						index = *pIndex;
					}

					indexBuffer->push_back(index);
					p += stride;
				}

				//�A�����b�N
				ib->Unlock();
				//ib->Release();
				
				//�C���f�b�N�X�o�b�t�@�ݒ�
				IndexBufferArray_.push_back(indexBuffer);
			}

			//�C���f�b�N�X���b�V�����쐬�B
			btIndexedMesh indexedMesh;
			VertexBufferT* vb = VertexBufferArray_.back();
			IndexBufferT* ib = IndexBufferArray_.back();
			indexedMesh.m_numTriangles = ib->size() / 3;
			indexedMesh.m_triangleIndexBase = (unsigned char*)(&ib->front());
			indexedMesh.m_triangleIndexStride = 12;
			indexedMesh.m_numVertices = vb->size();
			indexedMesh.m_vertexBase = (unsigned char*)(&vb->front());
			indexedMesh.m_vertexStride = sizeof(Vector3);
			
			StridingMeshInterface_->addIndexedMesh(indexedMesh);

		}
		
		//���b�V���`��̍쐬
		MeshShape_ = new btBvhTriangleMeshShape(StridingMeshInterface_, true);
	}

}// namespace nkEngine