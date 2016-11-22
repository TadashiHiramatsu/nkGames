//�X�L�����f��
#pragma once 

#include"nkSkinModelData.h"
#include"nkAnimation.h"
#include"nkLight.h"

namespace nkEngine
{
	class CSkinModelData;
	class CLight;
	class CTransform;
	class CCamera;

	enum EFogFunc
	{
		enFogFuncNone, //�t�H�O�Ȃ�
		enFogFuncDist, //�����t�H�O
		enFogFuncHeight, //�����t�H�O
	};

	//���f�������_�[
	class CModelRender
	{
	public:
		//�R���X�g���N�^
		CModelRender();

		//�f�X�g���N�^
		~CModelRender();

		//�ǂݎ��
		//param[in] X�t�@�C���̃t�@�C���p�X
		void Load(LPCSTR Filepass, CAnimation* anim);
		//�ǂݎ��
		//param[in] X�t�@�C���̃t�@�C���p�X
		void Load(CSkinModelData* m_modeldata);

		//�X�V
		virtual void Update();

		//�C���X�^���V���O�`��p�̍X�V
		//pram[in] ���_�o�b�t�@�ɃR�s�[����f�[�^
		void UpdateInstancinfRenderData(const void* data)
		{
			m_ModelData->UpdateInstancingRenderData(data);
		}

		//�`��
		void Render();

		//�V���h�E�}�b�v�ɕ`��
		//�V���h�E�}�b�v�ɌĂяo�����
		void RenderToShadowMap();

		//���C�g��ݒ�
		//param[in] ���C�g�̃A�h���X
		void SetLight(CLight* light)
		{
			m_Light = light;
		}

		//�@���}�b�v��ݒ�
		//param[in] �e�N�X�`��
		void SetNormalMap(CTexture* normalmap)
		{
			m_NormalMap = normalmap;
		}

		//�X�y�L�����}�b�v��ݒ�
		//param[in] �e�N�X�`��
		void SetSpecMap(CTexture* spec)
		{
			m_SpecMap = spec;
		}

		//�V���h�E�L���X�^�[�̃t���O��ݒ�
		//param[in] �V���h�E�L���X�^�[�̃t���O
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}

		//�V���h�E���V�[�o�[�̃t���O��ݒ�
		//param[in] �V���h�E���V�[�o�[�̃t���O
		void SetShadowReceiverFlag(bool flag)
		{
			m_isShadowReceiver = flag;
		}

		//�������C�g�t���O��ݒ�
		//param[in]	�������C�g�̃t���O
		void SetRimLight(bool flag)
		{
			m_isRimLight = flag;
		}

		//�P�x�𖄂ߍ��ރt���O��ݒ�
		//param[in] �P�x�𖄂ߍ��ރt���O
		void SetLuminance(bool flag)
		{
			m_isLuminance = flag;
		}

		//�J�����̃A�h���X��ݒ�
		//param[in] �J����
		void SetCamera(CCamera* camera)
		{
			m_camera = camera;
		}

		//�g�����X�t�H�[����ݒ�
		//param[in] �g�����X�t�H�[���̃A�h���X
		void SetTransform(CTransform* trans)
		{
			m_Transform = trans;
		}

		//�����[�X�֐�
		void Release()
		{
			m_ModelData->Release();
			m_Light = nullptr;
			m_camera = nullptr;
			m_Transform = nullptr;
		}

		//�t�H�O�p�����[�^��ݒ�
		//param[in] �t�H�O�̎��
		//param[in] �t�H�O��������n�߂鋗��
		//param[in] �t�H�O�������肫�鋗��
		void SetFogParam(EFogFunc fogfunc, float idx0, float idx1)
		{
			m_fogFunc = fogfunc;
			m_fogParam[0] = idx0;
			m_fogParam[1] = idx1;
		}

		//���b�V�����擾
		LPD3DXMESH GetMesh()
		{
			static D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)(m_ModelData->GetFrameRoot()->pMeshContainer);
			return pMeshContainer->pOrigMesh;
		}

		//�擪�̃��b�V�����擾
		LPD3DXMESH GetOrgMeshFirst() const
		{
			return m_ModelData->GetOrgMeshFirst();
		}

		D3DXFRAME* GetFrame()
		{
			return m_ModelData->GetFrameRoot();
		}
		D3DXFRAME* GetFrame(const char* name)
		{
			return D3DXFrameFind(GetFrame(), name);
		}

		D3DXMATRIX* FindBoneWorldMatrix(const char* name)
		{
			D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_ModelData->GetFrameRoot(), name);
			return &frame->CombinedTransformationMatrix;
		}

		void FindBoneRotationMatrix(const char* name, D3DXMATRIX* rot)
		{
			D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_ModelData->GetFrameRoot(), name);
			frame->RotationMatrix = rot;
		}

		D3DXMATRIX* GetWorldInv()
		{
			return &m_mWorldInv;
		}

		void SetParentMatrix(D3DXMATRIX* _w)
		{
			m_mParentWorld = _w;
		}

	protected:

		void RenderFrame(
			LPD3DXFRAME pFrame,
			bool isRenderToShadowMap);

		void RenderMeshContainer(
			LPD3DXMESHCONTAINER pMeshContainerBase,
			LPD3DXFRAME pFrameBase,
			bool isRenderToShadowMap);

		//RenderMeshContainer����Ă΂��C���X�^���V���O�`��̋��ʏ����B
		void RenderMeshContainer_InstancingRenderCommon(D3DXMESHCONTAINER_DERIVED* meshContainer, int materialID);

	protected:

		CSkinModelData* m_ModelData; //�X�L�����f���̃f�[�^
		CLight* m_Light; //���C�g�N���X
		ID3DXEffect* m_Effect; //�G�t�F�N�g

		CCamera* m_camera; //�J�����̃A�h���X

		CTransform* m_Transform; // �g�����X�t�H�[�� �Ϗ������N���X�̃g�����X�t�H�[���̃A�h���X
		D3DXMATRIX m_mWorld; //���[���h�s��
		D3DXMATRIX m_mWorldInv; //���[���h�s��
		D3DXMATRIX m_mRotation; //���[�e�[�V�����s��@
		D3DXMATRIX* m_mParentWorld; //�e��World�s��

		static const int MAX_MATRIX_PALLET = 128; //�}�g���N�X�p���b�g�̍ő吔
		D3DXMATRIX m_BoneMatrixPallet[MAX_MATRIX_PALLET]; //�}�g���N�X�p���b�g

		bool m_isShadowReceiver; //�e�𗎂Ƃ����ǂ���
		bool m_isShadowCaster; //�e���o�邩�ǂ���
		bool m_isRimLight; //�������C�g�����邩�ǂ���
		bool m_isLuminance; //�P�x�𖄂ߍ��ނ�
		CTexture* m_NormalMap; //�@���}�b�v��Texture
		CTexture* m_SpecMap; //���ʔ��˃}�b�v��Texture

		EFogFunc m_fogFunc;	//�t�H�O�̎��
		float m_fogParam[2]; //�t�H�O�̃p�����[�^
	};
}