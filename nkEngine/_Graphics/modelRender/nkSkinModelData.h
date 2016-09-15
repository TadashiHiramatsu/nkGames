//�X�L�����f���f�[�^
#pragma once

#include"..\nkVertexBuffer.h"

namespace nkEngine
{
	struct D3DXFRAME_DERIVED : public D3DXFRAME {
		D3DXMATRIXA16	CombinedTransformationMatrix;	//�����ςݍs��B
	};
	struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9* ppTextures;
		LPD3DXMESH pOrigMesh;
		LPD3DXATTRIBUTERANGE pAttributeTable;
		DWORD NumAttributeGroups;
		DWORD NumInfl;
		LPD3DXBUFFER pBoneCombinationBuf;
		D3DXMATRIX** ppBoneMatrixPtrs;
		D3DXMATRIX* pBoneOffsetMatrices;
		DWORD NumPaletteEntries;
		bool UseSoftwareVP;
		DWORD iAttributeSW;
	};

	//�A�j���[�V�����N���X
	class CAnimation;

	//�X�L�����f���f�[�^
	class CSkinModelData
	{
	public:
		//�R���X�g���N�^
		CSkinModelData();

		//�f�X�g���N�^
		~CSkinModelData();

		//���f���f�[�^�����[�h
		//param[in] �t�@�C���p�X
		//param[out] �A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�A�j���[�V�����N���X���\�z����܂��B
		void LoadModelData(const char* filepath, CAnimation* anim);

		//�C���X�^���V���O�`����s�����߂̃f�[�^���쐬����
		//param[in] �C���X�^���X�̐�
		//param[in] �C���X�^���V���O�`��p�̒��_�X�g���[���P�ɗ������ޒ��_�o�b�t�@�̒��_���C�A�E�g
		void CreateInstancingDrawData(int numInstance, D3DVERTEXELEMENT9* vertexElement);

		//���f���f�[�^�̃N���[�����쐬
		//param[in] ���f���f�[�^
		//param[in] �A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�A�j���[�V�����N���X���\�z����܂��B
		void CloneModelData(const CSkinModelData& ModelData, CAnimation* anim);

		//�����[�X
		void Release();

		//�X�P���g���폜
		void DeleteSkeleton(LPD3DXFRAME frame);

		//�t���[�����[�g�̎擾
		//return �t���[�����[�g
		D3DXFRAME* GetFrameRoot()
		{
			return m_FrameRoot;
		}

		//�e�X�g �Ӗ��s
		//param[in] �t���[��
		//param[in] �A�j���[�V�����R���g���[��
		void SetupOutputAnimationRegist(D3DXFRAME* frame, ID3DXAnimationController* aniCon);

		//�{�[���s����X�V
		//param[in] ���[���h�s��
		void UpdateBoneMatrix(const D3DXMATRIX& matWorld);

		void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, const D3DXMATRIX* pParentMatrix);

		//�C���X�^���V���O�`��p�̃f�[�^���X�V
		//param[in] ���_�o�b�t�@�ɃR�s�[����f�[�^
		void UpdateInstancingDrawData(const void* data)
		{
			m_instanceVertexBuffer.Update(data);
		}

		//�C���X�^���V���O�`��p�̂Ƃ��Ɏg�p���钸�_��`���擾
		//return ���_��`
		IDirect3DVertexDeclaration9* GetVertexDeclForInstancingDraw()const
		{
			return m_vertexDeclForInstancingDraw;
		}

		//�C���X�^���V���O�`��p�̒��_�o�b�t�@���擾
		//return �X�g���[���P�ɗ������_�o�b�t�@
		const CVertexBuffer& GetInstancingVertexBuffer() const
		{
			return(const_cast<CSkinModelData&>(*this)).GetInstancingVertexBuffer();
		}
		//�C���X�^���V���O�`��p�̒��_�o�b�t�@���擾
		//return ���_�o�b�t�@
		CVertexBuffer& GetInstancingVertexBuffer()
		{
			return m_instanceVertexBuffer;
		}

		//�C���X�^���X�̐����擾
		//return �C���X�^���X��
		int GetNumInstance()
		{
			return m_numInstance;
		}

		//���_�o�b�t�@�̃X�g���C�h���擾
		int GetVertexBufferStride() const
		{
			return m_vertexBufferStride;
		}

		//���b�V���R���e�i�̍폜
		//HRESULT DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase);

	private:

		//�X�P���g���̃N���[�����쐬
		//param[out] �N���[����̃X�P���g���̊i�[��
		//param[in] �N���[�����̃X�P���g��
		void CloneSkeleton(LPD3DXFRAME& dstFrame, D3DXFRAME* srcFrame);

		//�X�P���g���̃N���[�����폜
		//param[in]�@�폜����X�P���g��
		void DeleteCloneSkeleton(D3DXFRAME* frame);

		//�C���X�^���V���O�`��p�̃f�[�^���쐬
		//param[in] �t���[��
		//param[in] �C���X�^���X�̐�
		//param[in] �C���X�^���V���O�`��p�̒��_�X�g���[��1�ɗ������ޒ��_�o�b�t�@�̒��_���C�A�E�g
		//return true���A���Ă�����ċA�����I��
		bool CreateInstancingDrawData(D3DXFRAME* frame, int numInstance, D3DVERTEXELEMENT9* vertexElement);

		//��
		HRESULT SetupBoneMatrixPointers(D3DXFRAME* pFrame, D3DXFRAME* pRootFrame);
	private:
		D3DXFRAME* m_FrameRoot; //�t���[�����[�g
		ID3DXAnimationController* m_AnimController; //�A�j���[�V�����R���g���[���[
		bool m_isClone; //�N���[��
		CVertexBuffer m_instanceVertexBuffer; //�C���X�^���V���O�`��p�̒��_�o�b�t�@�̃��X�g
		IDirect3DVertexDeclaration9* m_vertexDeclForInstancingDraw; //�C���X�^���V���O�`��p�̒��_��`
		int m_numInstance; //�C���X�^���X�̐�
		int m_vertexBufferStride; //���_�X�g���C�h
	};
}