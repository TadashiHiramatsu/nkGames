#pragma once

#include"Source\Physics\CCollider.h"

class CMeshCollider : public CCollider
{
public:

	//�R���X�g���N�^
	CMeshCollider();

	//�f�X�g���N�^
	~CMeshCollider();

	//CModelRender����Mesh�R���C�_�[�𐶐�
	//param[in] �X�L�����f��
	//param[in] �I�t�Z�b�g�s��
	void Create(CModelRender* model, const D3DXMATRIX* offsetMatrix);

	//�{�f�B���擾
	btCollisionShape* GetBody() override
	{
		return m_MeshShape;
	}

private:
	typedef std::vector<D3DXVECTOR3> VertexBuffer; //���_�o�b�t�@�B
	typedef std::vector<unsigned int> IndexBuffer; //�C���f�b�N�X�o�b�t�@�B
	std::vector<VertexBuffer*> m_VertexBufferArray; //���_�o�b�t�@�̔z��B
	std::vector<IndexBuffer*> m_IndexBufferArray; //�C���f�b�N�X�o�b�t�@�̔z��B
	btBvhTriangleMeshShape* m_MeshShape; //���b�V���`��B
	btTriangleIndexVertexArray* m_StridingMeshInterface;
};