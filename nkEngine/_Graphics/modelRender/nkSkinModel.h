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

	//���f�������_�[
	class CModelRender
	{
	public:
		//�R���X�g���N�^
		CModelRender();

		//�f�X�g���N�^
		~CModelRender();

		//������
		//param[in] X�t�@�C���̃t�@�C���p�X
		void Init(LPCSTR Filepass);
		void Init(LPCSTR Filepass, CAnimation* anim);
		//������
		//param[in] �X�L�����f���f�[�^
		void Init(CSkinModelData* ModelData);

		//�X�V
		void Update();

		//�C���X�^���V���O�`��p�̍X�V
		//pram[in] ���_�o�b�t�@�ɃR�s�[����f�[�^
		void UpdateInstancinfDrawData(const void* data)
		{
			m_Skinmodel->UpdateInstancingDrawData(data);
		}

		//�`��
		void Draw();

		//�V���h�E�}�b�v�ɕ`��
		//�V���h�E�}�b�v�ɌĂяo�����
		void DrawToShadowMap();

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
			m_Skinmodel->Release();
			m_Light = nullptr;
			m_camera = nullptr;
			m_Transform = nullptr;
		}

	private:

		void DrawFrame(
			LPD3DXFRAME pFrame,
			bool isDrawToShadowMap);

		void DrawMeshContainer(
			LPD3DXMESHCONTAINER pMeshContainerBase,
			LPD3DXFRAME pFrameBase,
			bool isDrawToShadowMap);

		//DrawMeshContainer����Ă΂��C���X�^���V���O�`��̋��ʏ����B
		void DrawMeshContainer_InstancingDrawCommon(D3DXMESHCONTAINER_DERIVED* meshContainer, int materialID);

	private:
		CSkinModelData* m_Skinmodel; //�X�L�����f���̃f�[�^
		CAnimation m_Animation; //�A�j���[�V���� 
		CLight* m_Light; //���C�g�N���X
		ID3DXEffect* m_Effect; //�G�t�F�N�g

		CCamera* m_camera; //�J�����̃A�h���X

		CTransform* m_Transform; // �g�����X�t�H�[�� �Ϗ������N���X�̃g�����X�t�H�[���̃A�h���X
		D3DXMATRIX m_mWorld; //���[���h�s��
		D3DXMATRIX m_mRotation; //���[�e�[�V�����s��@

		static const int MAX_MATRIX_PALLET = 128; //�}�g���N�X�p���b�g�̍ő吔
		D3DXMATRIX m_BoneMatrixPallet[MAX_MATRIX_PALLET]; //�}�g���N�X�p���b�g

		bool m_isShadowReceiver; //�e�𗎂Ƃ����ǂ���
		bool m_isShadowCaster; //�e���o�邩�ǂ���
		bool m_isRimLight; //�������C�g�����邩�ǂ���
		bool m_isLuminance; //�P�x�𖄂ߍ��ނ�
		CTexture* m_NormalMap; //�@���}�b�v��Texture

		//�V���h�E�L���X�^�[�K�v
	};
}