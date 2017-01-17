/**
 * @file _Graphics\_ModelRender\nkModelRender.cpp
 *
 * ���f�������_�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkModelRender.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	ModelRender::ModelRender() :
		ModelData_(nullptr),
		Light_(nullptr),
		NormalMap_(nullptr),
		SpecMap_(nullptr),
		isShadowCaster_(false),
		isShadowReceiver_(false),
		isRimLight_(false),
		FogFunc_(FogFuncNone)
	{
		FogParam_[0] = 0.0f;
		FogParam_[1] = 0.0f;
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	ModelRender::~ModelRender()
	{
	}

	/**
	 * Loads the given file.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param 		   filePath Filename of the file.
	 * @param [in,out] anim	    If non-null, the animation.
	 */
	void ModelRender::Load(LPCSTR filePath, Animation* anim)
	{
		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("ModelRender.fx");

		//���f���f�[�^�̃��[�h
		ModelData_ = new SkinModelData;
		ModelData_->LoadModelData(filePath, anim);
	
	}
	/**
	 * Loads the given m modeldata.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] modeldata If non-null, the modeldata to load.
	 */
	void ModelRender::Load(SkinModelData* modeldata)
	{
		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("ModelRender.fx");

		//���f���̃R�s�[
		ModelData_ = modeldata;
	
	}

	/**
	 * Updates this object.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void ModelRender::Update()
	{
		if (isShadowCaster_ && Shadow().isEnable()) 
		{
			// �V���h�E�L���X�^�[.
			// �V���h�E�}�b�v�Ƀ��f����ݒ�
			Shadow().Entry(this);
		}
		
		if (ModelData_)
		{
			//�{�[���s��̌v�Z
			ModelData_->UpdateBoneMatrix(Transform_->WorldMatrix_);
		}

	}

	/**
	 * Renders this object.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void ModelRender::Render()
	{
		if (ModelData_)
		{
			//�`��
			RenderFrame(ModelData_->GetFrameRoot(),false);
		}

	}

	/**
	 * Renders to shadow map.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void ModelRender::RenderToShadowMap()
	{
		if (ModelData_ != nullptr) 
		{
			//�`��
			RenderFrame(ModelData_->GetFrameRoot(), true);
		}
	
	}

	/**
	 * Renders the frame.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param pFrame			  The frame.
	 * @param isRenderToShadowMap True if this object is render to shadow map.
	 */
	void ModelRender::RenderFrame(LPD3DXFRAME pFrame, bool isRenderToShadowMap)
	{
		//���b�V���R���g���[���̎擾
		LPD3DXMESHCONTAINER MeshContainer = pFrame->pMeshContainer;

		while (MeshContainer != NULL)
		{
			//�`��
			RenderMeshContainer(
				MeshContainer,
				pFrame, isRenderToShadowMap
			);

			MeshContainer = MeshContainer->pNextMeshContainer;
	
		}

		if (pFrame->pFrameSibling != NULL)
		{
			//�Z��
			RenderFrame(pFrame->pFrameSibling, isRenderToShadowMap);
		}

		if (pFrame->pFrameFirstChild != NULL)
		{
			//�q��
			RenderFrame(pFrame->pFrameFirstChild, isRenderToShadowMap);
		}

	}

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
	void ModelRender::RenderMeshContainer(
		LPD3DXMESHCONTAINER pMeshContainerBase,
		LPD3DXFRAME pFrameBase,
		bool isRenderToShadowMap)
	{
		//���b�V���R���g���[���̎擾
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

		//�t���[���x�[�X�̎擾
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
		LPD3DXBONECOMBINATION pBoneComb;

		//�f�o�C�X���擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		D3DCAPS9 d3dCaps;
		Device->GetDeviceCaps(&d3dCaps);


	
		//�e�N�j�b�N��ݒ�
		{
			//�C���X�^���V���O�`��
			if (ModelData_->GetNumInstance() != 0)
			{
				//�A�j���[�V����
				if (pMeshContainer->pSkinInfo != NULL)
				{
					if (isRenderToShadowMap)
					{
						//�e
						Effect_->SetTechnique("SkinModelInstancingRenderToShadowMap");
					}
					else
					{
						//�ʏ�
						Effect_->SetTechnique("SkinModelInstancing");
					}
				}
				//�m���A�j���[�V����
				else
				{
					if (isRenderToShadowMap)
					{
						//�e
						Effect_->SetTechnique("NoSkinModelInstancingRenderToShadowMap");
					}
					else
					{
						//�ʏ�
						Effect_->SetTechnique("NoSkinModelInstancing");
					}
				}
			}
			//�ʏ�
			else
			{
				//�A�j���[�V����
				if (pMeshContainer->pSkinInfo != NULL)
				{
					if (isRenderToShadowMap)
					{
						//�e
						Effect_->SetTechnique("SkinModelRenderShadowMap");
					}
					else
					{
						//�ʏ�
						Effect_->SetTechnique("SkinModel");
					}
				}
				//�m���A�j���[�V����
				else
				{
					if (isRenderToShadowMap)
					{
						//�e
						Effect_->SetTechnique("NoSkinModelRenderShadowMap");
					}
					else
					{
						//�ʏ�
						Effect_->SetTechnique("NoSkinModel");
					}
				}
			}
		}

		//�J�n
		Effect_->Begin(0, D3DXFX_DONOTSAVESTATE);
		Effect_->BeginPass(0);

		//���ʂ̒萔���W�X�^��ݒ�
		{
			//�r���[�v���W�F�N�V�����s��
			if (isRenderToShadowMap)
			{
				//�V���h�E�̕`��
				Effect_->SetMatrix("g_mViewProj", &Shadow().GetLightViewProjectionMatrix());
			}
			else
			{
				//�ʏ�̕`��
				D3DXMATRIX viewProj;
				D3DXMatrixMultiply(&viewProj, &Camera_->GetViewMatrix(),&Camera_->GetProjectionMatrix());
				Effect_->SetMatrix("g_mViewProj", &viewProj);

				//�A���t�@�u�����f�B���O���s��
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				// ���ߏ������s��
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				// �������������s��
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			}

			//���C�g��ݒ�
			Effect_->SetValue("g_light", Light_, sizeof(Light));

			//�F�̐ݒ�
			Effect_->SetValue("g_Color", &Color_, sizeof(Color_));

			//true or false �ŏI�I��GPU�ɑ���
			int flag[4] = { 0 };
			
			//�@���}�b�v
			if (NormalMap_ != nullptr)
			{
				flag[0] = true;
				Effect_->SetTexture("g_normalMap", NormalMap_->GetTexture());
			}

			//�V���h�E���V�[�o�[
			if (!isRenderToShadowMap && isShadowReceiver_)
			{
				flag[1] = true;
				Effect_->SetTexture("g_ShadowMap_0", Shadow().GetTexture(0)->GetTexture());
				Effect_->SetTexture("g_ShadowMap_1", Shadow().GetTexture(1)->GetTexture());
				Effect_->SetTexture("g_ShadowMap_2", Shadow().GetTexture(2)->GetTexture());

				const CShadowMap::ShadowReceiverParamS& param = Shadow().GetShadowReceiverParam();
				Effect_->SetValue("g_ShadowReceiverParam", &param, sizeof(CShadowMap::ShadowReceiverParamS));
			}

			//�������C�g
			if (isRimLight_)
			{
				flag[2] = true;
			}

			Effect_->SetValue("g_flags", flag, sizeof(flag));

			//�X�y�L�����ƃt�H�O�Ŏg�p
			//�J�����̃|�W�V�������v�Z
			D3DXVECTOR3 cameraPos;
			cameraPos.x = Camera_->GetViewInvMatrix().m[3][0];
			cameraPos.y = Camera_->GetViewInvMatrix().m[3][1];
			cameraPos.z = Camera_->GetViewInvMatrix().m[3][2];
			Effect_->SetVector("g_cameraPos", (D3DXVECTOR4*)&cameraPos);

			//�X�y�L�����}�b�v
			if (SpecMap_ != nullptr)
			{
				Effect_->SetTexture("g_speculerMap", SpecMap_->GetTexture());
				Effect_->SetBool("g_isSpec", true);
			}
			else
			{
				Effect_->SetBool("g_isSpec", false);
			}

			D3DXVECTOR4 fogParam;
			if (FogFunc_ == FogFuncDist) 
			{
				//�����t�H�O
				fogParam.x = FogParam_[0];
				fogParam.y = FogParam_[1];
				fogParam.z = 1.0f;
			}
			else if (FogFunc_ == FogFuncHeight) 
			{
				//�����t�H�O
				fogParam.x = FogParam_[0];
				fogParam.y = FogParam_[1];
				fogParam.z = 2.0f;
			}
			else
			{
				fogParam.z = 0.0f;
			}
			Effect_->SetVector("g_fogParam", &fogParam);

		}

		//�A�j���[�V����
		if (pMeshContainer->pSkinInfo != NULL)
		{
			pBoneComb = reinterpret_cast<D3DXBONECOMBINATION*>(pMeshContainer->BoneCombinationBuf_->GetBufferPointer());

			//�����O���[�v�����[�v
			for (UINT iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroup_; iAttrib++)
			{
				//�{�[���s��v�Z�H
				for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
				{
					DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];

					if (iMatrixIndex != UINT_MAX)
					{
						NK_ASSERT(iPaletteEntry < MAX_MATRIX_PALLET, "�{�[���s��p���b�g�̍ő吔�𒴂���");
						NK_ASSERT(pMeshContainer->BoneMatrixPtrs_[iMatrixIndex] != NULL, "NULL");

						D3DXMatrixMultiply(
							&BoneMatrixPallets_[iPaletteEntry],
							&pMeshContainer->BoneOffsetMatrix_[iMatrixIndex],
							pMeshContainer->BoneMatrixPtrs_[iMatrixIndex]
						);

					}

				}

				//�{�[���s��̔z��
				Effect_->SetMatrixArray("g_mWorldMatrixArray", BoneMatrixPallets_, pMeshContainer->NumPaletteEntries);

				//�{�[���̐�
				Effect_->SetInt("g_numBone", pMeshContainer->NumInfl_);
				
				//�f�B�t���[�Y�e�N�X�`��
				Effect_->SetTexture("g_diffuseTexture", pMeshContainer->Texture_[pBoneComb[iAttrib].AttribId]);

				//�J�����̉�]�s��̋t�s��
				Effect_->SetMatrix("g_mViewMatrixRotInv",&Camera_->GetRotationInvMatrix());

				Effect_->CommitChanges();

				if (ModelData_->GetNumInstance() != 0)
				{
					//�C���X�^���V���O
					RenderMeshContainer_InstancingRenderCommon(pMeshContainer, iAttrib);
				}
				else
				{
					//�ʏ�
					pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				}

			}
		}
		//�A�j���[�V�����Ȃ�
		else
		{
			D3DXMATRIX mWorld;

			if (pFrame != NULL)
			{
				mWorld = pFrame->CombinedTransformationMatrix_;
			}
			else
			{
				mWorld = Transform_->WorldMatrix_;
			}

			//���[���h�s��
			Effect_->SetMatrix("g_mWorldMatrix", &mWorld);

			//��]�s��
			Effect_->SetMatrix("g_mRotation", &Transform_->RotationMatrix_);

			for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++)
			{
				//�f�B�t���[�Y�e�N�X�`��
				Effect_->SetTexture("g_diffuseTexture", pMeshContainer->Texture_[i]);

				Effect_->CommitChanges();

				if (ModelData_->GetNumInstance() != 0)
				{
					//�C���X�^���V���O
					RenderMeshContainer_InstancingRenderCommon(pMeshContainer, 0);
					//RenderMeshContainer_InstancingRenderCommon(pMeshContainer, i);//����i����ˁH
				}
				else
				{
					//�ʏ�
					pMeshContainer->MeshData.pMesh->DrawSubset(i);
				}
			}
		}

		//�I��
		Effect_->EndPass();
		Effect_->End();

		//���ɖ߂�
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		
	}

	/**
	 * Renders the mesh container instancing render common.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] meshContainer If non-null, the mesh container.
	 * @param 		   materialID    Identifier for the material.
	 */
	void ModelRender::RenderMeshContainer_InstancingRenderCommon(D3DXMESHCONTAINER_DERIVED * meshContainer, int materialID)
	{

		//���_�o�b�t�@�̍쐬
		IDirect3DVertexBuffer9* vb;
		//�C���f�b�N�X�o�b�t�@�̍쐬
		IDirect3DIndexBuffer9* ib;

		ID3DXMesh* mesh = meshContainer->MeshData.pMesh;
		mesh->GetVertexBuffer(&vb);
		mesh->GetIndexBuffer(&ib);

		//���_�X�g���C�h���擾
		DWORD stride = ModelData_->GetVertexBufferStride();

		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | ModelData_->GetNumInstance());
		Device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

		Device->SetVertexDeclaration(ModelData_->GetVertexDeclForInstancingRender());

		//���_�o�b�t�@���X�g���[���O�Ԗڂɐݒ�
		Device->SetStreamSource(0, vb, 0, stride);

		//�X�g���[����ݒ�
		Device->SetStreamSource(
			1,
			ModelData_->GetInstancingVertexBuffer().GetBody(),
			0,
			ModelData_->GetInstancingVertexBuffer().GetStride()
		);

		Device->SetIndices(ib);
		Device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			mesh->GetNumVertices(),
			meshContainer->AttributeTable_[materialID].FaceStart * 3,
			meshContainer->AttributeTable_[materialID].FaceCount
		);

		//��n��
		Device->SetStreamSourceFreq(0, 1);
		Device->SetStreamSourceFreq(1, 1);
	}

}// namespace nkEngine