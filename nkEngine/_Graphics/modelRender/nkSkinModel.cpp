#include"nkEngine/nkstdafx.h"
#include"nkSkinModel.h"

namespace nkEngine
{

	D3DXMATRIX viewMatrixRotInv;

	CModelRender::CModelRender() :
		m_Skinmodel(nullptr),
		m_Light(nullptr),
		m_NormalMap(nullptr),
		m_isShadowCaster(false),
		m_isShadowReceiver(false),
		m_isRimLight(false)
	{

	}

	CModelRender::~CModelRender()
	{
		SAFE_RELEASE(m_Effect);
	}

	void CModelRender::Init(LPCSTR FileName)
	{
		m_Effect = EffectManager().LoadEffect("skinModel.fx");
		m_Skinmodel = new CSkinModelData;
		m_Skinmodel->LoadModelData(FileName, &m_Animation);
	}

	void CModelRender::Init(CSkinModelData * ModelData)
	{
		m_Skinmodel = ModelData;
	}

	void CModelRender::Update()
	{
		D3DXMATRIX mPosition, mScale;
		
		D3DXMatrixTranslation(&mPosition, m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);
		D3DXMatrixRotationQuaternion(&m_mRotation, &m_Transform->GetRotation());
		D3DXMatrixScaling(&mScale, m_Transform->GetScale().x, m_Transform->GetScale().y, m_Transform->GetScale().z);

		m_mWorld = mScale * m_mRotation * mPosition;

		if (m_Skinmodel)
		{
			m_Skinmodel->UpdateBoneMatrix(m_mWorld);
		}
	}

	void CModelRender::Draw()
	{
		if (m_Skinmodel) {
			DrawFrame(m_Skinmodel->GetFrameRoot(),false);
		}
	}

	void CModelRender::DrawToShadowMap()
	{
		if (m_Skinmodel) {
			DrawFrame(m_Skinmodel->GetFrameRoot(), true);
		}
	}

	void CModelRender::DrawFrame(LPD3DXFRAME pFrame, bool isDrawToShadowMap)
	{
		LPD3DXMESHCONTAINER MeshContainer;

		MeshContainer = pFrame->pMeshContainer;
		while (MeshContainer != NULL)
		{
			DrawMeshContainer(
				MeshContainer,
				pFrame, isDrawToShadowMap);

			MeshContainer = MeshContainer->pNextMeshContainer;
		}

		if (pFrame->pFrameSibling != NULL)
		{
			DrawFrame(
				pFrame->pFrameSibling, isDrawToShadowMap);
		}

		if (pFrame->pFrameFirstChild != NULL)
		{
			DrawFrame(
				pFrame->pFrameFirstChild, isDrawToShadowMap);
		}
	}

	void CModelRender::DrawMeshContainer(
		LPD3DXMESHCONTAINER pMeshContainerBase,
		LPD3DXFRAME pFrameBase,
		bool isDrawToShadowMap)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
		UINT iAttrib;
		LPD3DXBONECOMBINATION pBoneComb;

		D3DXMATRIXA16 matTemp;
		D3DCAPS9 d3dCaps;
		Engine().GetDevice()->GetDeviceCaps(&d3dCaps);
	
		//�e�N�j�b�N��ݒ�
		{
			
			//�C���X�^���V���O�`��
			if (m_Skinmodel->GetNumInstance() != 0)
			{

				//�A�j���[�V����
				if (pMeshContainer->pSkinInfo != NULL)
				{
					if (isDrawToShadowMap)
					{
						//�e
						m_Effect->SetTechnique("SkinModelInstancingRenderToShadowMap");
					}
					else
					{
						//�ʏ�
						m_Effect->SetTechnique("SkinModelInstancing");
					}
				}
				//�m���A�j���[�V����
				else
				{
					if (isDrawToShadowMap)
					{
						//�e
						m_Effect->SetTechnique("NoSkinModelInstancingRenderToShadowMap");
					}
					else
					{
						//�ʏ�
						m_Effect->SetTechnique("NoSkinModelInstancing");
					}
				}
			}
			//�ʏ�
			else
			{
				//�A�j���[�V����
				if (pMeshContainer->pSkinInfo != NULL)
				{
					if (isDrawToShadowMap)
					{
						//�e
						m_Effect->SetTechnique("SkinModelRenderShadowMap");
					}
					else
					{
						//�ʏ�
						m_Effect->SetTechnique("SkinModel");
					}
				}
				//�m���A�j���[�V����
				else
				{
					if (isDrawToShadowMap)
					{
						//�e
						m_Effect->SetTechnique("NoSkinModelRenderShadowMap");
					}
					else
					{
						//�ʏ�
						m_Effect->SetTechnique("NoSkinModel");
					}
				}
			}
		}

		//���ʂ̒萔���W�X�^��ݒ�
		{
			//�r���[�v���W�F�N�V�����s��
			if (isDrawToShadowMap)
			{
				m_Effect->SetMatrix("g_mViewProj", Shadow().GetVPMatrix());
			}
			else
			{
				D3DXMATRIX viewProj;
				D3DXMatrixMultiply(&viewProj, &m_camera->GetViewMatrix(),&m_camera->GetProjectionMatrix());
				m_Effect->SetMatrix("g_mViewProj", &viewProj);
			}

			//���C�g
			m_Effect->SetValue("g_light", m_Light, sizeof(CLight));

			//true or false �ŏI�I��GPU�ɑ���
			int flag[4] = { 0 };
			
			//�@���}�b�v
			if (m_NormalMap != nullptr)
			{
				flag[0] = true;
				m_Effect->SetTexture("g_normalMap", m_NormalMap->GetTextureDX());
			}

			//�V���h�E���V�[�o�[
			if (!isDrawToShadowMap && m_isShadowReceiver)
			{
				flag[1] = true;
				m_Effect->SetTexture("g_ShadowTexture", Shadow().GetTexture());
				m_Effect->SetMatrix("g_mLVP", Shadow().GetLVPMatrix());
			}

			//�������C�g
			if (m_isRimLight)
			{
				flag[2] = true;
			}

			//�P�x
			if (m_isLuminance)
			{
				flag[3] = true;
			}
			m_Effect->SetValue("g_flags", flag, sizeof(flag));

		}

		//�A�j���[�V����
		if (pMeshContainer->pSkinInfo != NULL)
		{
			pBoneComb = reinterpret_cast<D3DXBONECOMBINATION*>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
			for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
			{
				for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
				{
					DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
					if (iMatrixIndex != UINT_MAX)
					{
						NK_ASSERT(iPaletteEntry < MAX_MATRIX_PALLET, "�{�[���s��p���b�g�̍ő吔�𒴂���");
						D3DXMatrixMultiply(
							&m_BoneMatrixPallet[iPaletteEntry],
							&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
					}
				}

				m_Effect->SetMatrixArray("g_mWorldMatrixArray", m_BoneMatrixPallet, pMeshContainer->NumPaletteEntries);
				//�{�[���̐�
				m_Effect->SetInt("g_numBone", pMeshContainer->NumInfl);
				
				//�f�B�t���[�Y�e�N�X�`��
				m_Effect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

				//�J�����̉�]�s��̋t�s��
				m_Effect->SetMatrix("g_mViewMatrixRotInv",&m_camera->GetRotationInvMatrix());

				m_Effect->Begin(0, D3DXFX_DONOTSAVESTATE);
				m_Effect->BeginPass(0);
				m_Effect->CommitChanges();

				//�C���X�^���V���O
				if (m_Skinmodel->GetNumInstance() != 0)
				{
					DrawMeshContainer_InstancingDrawCommon(pMeshContainer, iAttrib);
				}
				//�ʏ�
				else
				{
					pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				}
				m_Effect->EndPass();
				m_Effect->End();
			}
		}
		//�A�j���[�V�����Ȃ�
		else
		{
			D3DXMATRIX mWorld;

			if (pFrame != NULL)
			{
				mWorld = pFrame->CombinedTransformationMatrix;
			}
			else
			{
				mWorld = m_mWorld;
			}

			m_Effect->SetMatrix("g_mWorldMatrix", &mWorld);
			m_Effect->SetMatrix("g_mRotation", &m_mRotation);

			m_Effect->Begin(0, D3DXFX_DONOTSAVESTATE);
			m_Effect->BeginPass(0);

			for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++)
			{
				//�f�B�t���[�Y�e�N�X�`��
				m_Effect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
				m_Effect->CommitChanges();

				//�C���X�^���V���O
				if (m_Skinmodel->GetNumInstance() != 0)
				{
					DrawMeshContainer_InstancingDrawCommon(pMeshContainer, 0);
				}
				//�ʏ�
				else
				{
					pMeshContainer->MeshData.pMesh->DrawSubset(i);
				}

				m_Effect->EndPass();
				m_Effect->End();
			}
		}
	}

	void CModelRender::DrawMeshContainer_InstancingDrawCommon(D3DXMESHCONTAINER_DERIVED * meshContainer, int materialID)
	{
		IDirect3DVertexBuffer9* vb;
		IDirect3DIndexBuffer9* ib;

		ID3DXMesh* mesh = meshContainer->MeshData.pMesh;
		mesh->GetVertexBuffer(&vb);
		mesh->GetIndexBuffer(&ib);
		DWORD sttributeTableSize = 256;

		DWORD stride = m_Skinmodel->GetVertexBufferStride();

		IDirect3DDevice9* d3dDevice = Engine().GetDevice();

		d3dDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | m_Skinmodel->GetNumInstance());
		d3dDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

		d3dDevice->SetVertexDeclaration(m_Skinmodel->GetVertexDeclForInstancingDraw());

		//���_�o�b�t�@���X�g���[���O�Ԗڂɐݒ�
		d3dDevice->SetStreamSource(0, vb, 0, stride);

		d3dDevice->SetStreamSource(
			1,
			m_Skinmodel->GetInstancingVertexBuffer().GetBody(),
			0,
			m_Skinmodel->GetInstancingVertexBuffer().GetStride());

		d3dDevice->SetIndices(ib);
		d3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			mesh->GetNumVertices(),
			meshContainer->pAttributeTable[materialID].FaceStart * 3,
			meshContainer->pAttributeTable[materialID].FaceCount);

		//��n��
		d3dDevice->SetStreamSourceFreq(0, 1);
		d3dDevice->SetStreamSourceFreq(1, 1);
	}

}