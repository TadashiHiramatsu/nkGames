/**
 * @file _Graphics\_ModelRender\nkModelRender.h
 *
 * ���f�������_�[�N���X�̒�`.
 */
#pragma once 

#include"nkSkinModelData.h"
#include"nkAnimation.h"
#include"nkLight.h"
#include"../nkCamera.h"
#include"../nkTexture.h"

namespace nkEngine
{

	/**
	 * ���f�������_�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class ModelRender
	{
	public:

		/** �t�H�O�̃p�����[�^. */
		enum FogFuncE
		{
			FogFuncNone,	//!< �t�H�O�Ȃ�
			FogFuncDist,	//!< �����t�H�O
			FogFuncHeight,	//!< �����t�H�O
		};

	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		ModelRender();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~ModelRender();

		/**
		 * �ǂݎ��.
		 * "Asset/Model/"�t�H���_���ɂ���X�t�@�C���̃��f�������[�h
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param 		   filePath X�t�@�C���̃t�@�C���p�X�A"Asset/Model/"���Ȃ����t�@�C���p�X.
		 * @param [in,out] anim	    �A�j���[�V�����N���X.
		 */
		void Load(LPCSTR filePath, Animation* anim);

		/**
		 * �ǂݎ��.
		 * ���f���f�[�^���R�s�[���ă��[�h
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] modeldata If non-null, the modeldata to load.
		 */
		void Load(SkinModelData* modeldata);

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Update();

		/**
		 * �C���X�^���V���O�`��p�̍X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param data ���_�o�b�t�@�ɃR�s�[����f�[�^.
		 */
		void UpdateInstancinfRenderData(const void* data)
		{
			ModelData_->UpdateInstancingRenderData(data);
		}

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Render();

		/**
		 * �V���h�E�}�b�v�ɕ`��. 
		 * �V���h�E�}�b�v�ɌĂяo�����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void RenderToShadowMap();

		/**
		 * ���C�g��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] light ���C�g�̃A�h���X.
		 */
		void SetLight(Light* light)
		{
			Light_ = light;
		}

		/**
		 * �@���}�b�v��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] normalmap �e�N�X�`��.
		 */
		void SetNormalMap(Texture* normalmap)
		{
			NormalMap_ = normalmap;
		}

		/**
		 * �X�y�L�����}�b�v��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] spec �e�N�X�`��.
		 */
		void SetSpecMap(Texture* spec)
		{
			SpecMap_ = spec;
		}

		/**
		 * �V���h�E�L���X�^�[�̃t���O��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param flag �V���h�E�L���X�^�[�̃t���O.
		 */
		void SetShadowCasterFlag(bool flag)
		{
			isShadowCaster_ = flag;
		}

		/**
		 * �V���h�E���V�[�o�[�̃t���O��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param flag �V���h�E���V�[�o�[�̃t���O.
		 */
		void SetShadowReceiverFlag(bool flag)
		{
			isShadowReceiver_ = flag;
		}

		/**
		 * �������C�g�t���O��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param flag �������C�g�̃t���O.
		 */
		void SetRimLight(bool flag)
		{
			isRimLight_ = flag;
		}

		/**
		 * �P�x�𖄂ߍ��ރt���O��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param flag �P�x�𖄂ߍ��ރt���O.
		 */
		void SetLuminance(bool flag)
		{
			isLuminance_ = flag;
		}

		/**
		 * �J�����̃A�h���X��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] camera �J����.
		 */
		void SetCamera(Camera* camera)
		{
			Camera_ = camera;
		}

		/**
		 * �g�����X�t�H�[����ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] trans �g�����X�t�H�[���̃A�h���X.
		 */
		void SetTransform(Transform* trans)
		{
			Transform_ = trans;
		}

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Release()
		{
			ModelData_->Release();
			Light_ = nullptr;
			Camera_ = nullptr;
			Transform_ = nullptr;
		}

		/**
		 * �t�H�O�p�����[�^��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param fogfunc The �t�H�O�̎��.
		 * @param idx0    The �t�H�O��������n�߂鋗��.
		 * @param idx1    The �t�H�O�������肫�鋗��.
		 */
		void SetFogParam(FogFuncE fogfunc, float idx0, float idx1)
		{
			FogFunc_ = fogfunc;
			FogParam_[0] = idx0;
			FogParam_[1] = idx1;
		}

		/**
		 * ���b�V�����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The mesh.
		 */
		LPD3DXMESH GetMesh()
		{
			static D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)(ModelData_->GetFrameRoot()->pMeshContainer);
			return pMeshContainer->OrigMesh_;
		}

		/**
		 * �擪�̃��b�V�����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The organisation mesh first.
		 */
		LPD3DXMESH GetOrgMeshFirst() const
		{
			return ModelData_->GetOrgMeshFirst();
		}

		/**
		 * �t���[���̌���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the frame.
		 */
		D3DXFRAME* GetFrame()
		{
			return ModelData_->GetFrameRoot();
		}
		/**
		 * �t���[���̌���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param name The name.
		 *
		 * @return Null if it fails, else the frame.
		 */
		D3DXFRAME* GetFrame(const char* name)
		{
			return D3DXFrameFind(GetFrame(), name);
		}

		/**
		 * �t���[���̃��[���h�s��̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param name The name.
		 *
		 * @return Null if it fails, else the found bone world matrix.
		 */
		D3DXMATRIX* FindBoneWorldMatrix(const char* name)
		{
			D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)GetFrame(name);
			return &frame->CombinedTransformationMatrix_;
		}

	protected:

		/**
		 * Renders the frame.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param pFrame			  The frame.
		 * @param isRenderToShadowMap True if this object is render to shadow map.
		 */
		void RenderFrame(
			LPD3DXFRAME pFrame,
			bool isRenderToShadowMap);

		/**
		 * Renders the mesh container.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param pMeshContainerBase  The mesh container base.
		 * @param pFrameBase		  The frame base.
		 * @param isRenderToShadowMap True if this object is render to shadow map.
		 */
		void RenderMeshContainer(
			LPD3DXMESHCONTAINER pMeshContainerBase,
			LPD3DXFRAME pFrameBase,
			bool isRenderToShadowMap);

		/**
		 * RenderMeshContainer����Ă΂��C���X�^���V���O�`��̋��ʏ����B.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] meshContainer If non-null, the mesh container.
		 * @param 		   materialID    Identifier for the material.
		 */
		void RenderMeshContainer_InstancingRenderCommon(D3DXMESHCONTAINER_DERIVED* meshContainer, int materialID);

	protected:

		/** �X�L�����f���̃f�[�^. */
		SkinModelData* ModelData_;
		/** ���C�g�N���X. */
		Light* Light_;
		/** �G�t�F�N�g. */
		ID3DXEffect* Effect_;
		/** �J�����̃A�h���X. */
		Camera* Camera_;
		/** �g�����X�t�H�[�� �Ϗ������N���X�̃g�����X�t�H�[���̃A�h���X. */
		Transform* Transform_;

		/** �}�g���N�X�p���b�g�̍ő吔. */
		static const int MAX_MATRIX_PALLET = 128;
		/** �}�g���N�X�p���b�g. */
		D3DXMATRIX BoneMatrixPallets_[MAX_MATRIX_PALLET];

		/** �e�𗎂Ƃ����ǂ���. */
		bool isShadowReceiver_;
		/** �e���o�邩�ǂ���. */
		bool isShadowCaster_;
		/** �������C�g�����邩�ǂ���. */
		bool isRimLight_;
		/** �P�x�𖄂ߍ��ނ�. */
		bool isLuminance_;

		/** �@���}�b�v��Texture. */
		Texture* NormalMap_;
		/** ���ʔ��˃}�b�v��Texture. */
		Texture* SpecMap_;

		/** �t�H�O�̎��. */
		FogFuncE FogFunc_;
		/** �t�H�O�̃p�����[�^. */
		float FogParam_[2];

	};

}// namespace nkEngine