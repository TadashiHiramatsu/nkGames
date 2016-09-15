#include"nkEngine/nkstdafx.h"
#include"nkSkinModel.h"

namespace nkEngine
{

	D3DXMATRIX viewMatrixRotInv;

	CModelRender::CModelRender() :
		m_Skinmodel(nullptr),
		m_Light(nullptr),
		m_NormalMap(nullptr),
		m_SpecMap(nullptr),
		m_isShadowCaster(false),
		m_isShadowReceiver(false),
		m_isRimLight(false),
		m_fogFunc(enFogFuncNone)
	{
		m_fogParam[0] = 0.0f;
		m_fogParam[1] = 0.0f;
	}

	CModelRender::~CModelRender()
	{
	}

	void CModelRender::Init(LPCSTR FileName, CAnimation* anim)
	{
		m_Effect = EffectManager().LoadEffect("skinModel.fx");
		m_Skinmodel = new CSkinModelData;

		m_Skinmodel->LoadModelData(FileName, anim);

	}

	void CModelRender::Init(CSkinModelData * ModelData)
	{
		m_Effect = EffectManager().LoadEffect("skinModel.fx");

		m_Skinmodel = ModelData;
	}

	void CModelRender::Update()
	{
		if (m_isShadowCaster && Shadow().IsActive()) {
			//シャドウキャスター。
			Shadow().Entry(this);
		}

		D3DXMATRIX mPosition, mScale;
		
		D3DXMatrixTranslation(&mPosition, m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);
		D3DXMatrixRotationQuaternion(&m_mRotation, &m_Transform->GetRotation());
		D3DXMatrixScaling(&mScale, m_Transform->GetScale().x, m_Transform->GetScale().y, m_Transform->GetScale().z);

		m_mWorld = mScale * m_mRotation * mPosition;

		D3DXMatrixInverse(&m_mWorldInv, NULL , &m_mWorld);

		if (m_Skinmodel)
		{
			m_Skinmodel->UpdateBoneMatrix(m_mWorld);
		}
	}

	void CModelRender::Render()
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
	
		//テクニックを設定
		{
			
			//インスタンシング描画
			if (m_Skinmodel->GetNumInstance() != 0)
			{

				//アニメーション
				if (pMeshContainer->pSkinInfo != NULL)
				{
					if (isDrawToShadowMap)
					{
						//影
						m_Effect->SetTechnique("SkinModelInstancingRenderToShadowMap");
					}
					else
					{
						//通常
						m_Effect->SetTechnique("SkinModelInstancing");
					}
				}
				//ノンアニメーション
				else
				{
					if (isDrawToShadowMap)
					{
						//影
						m_Effect->SetTechnique("NoSkinModelInstancingRenderToShadowMap");
					}
					else
					{
						//通常
						m_Effect->SetTechnique("NoSkinModelInstancing");
					}
				}
			}
			//通常
			else
			{
				//アニメーション
				if (pMeshContainer->pSkinInfo != NULL)
				{
					if (isDrawToShadowMap)
					{
						//影
						m_Effect->SetTechnique("SkinModelRenderShadowMap");
					}
					else
					{
						//通常
						m_Effect->SetTechnique("SkinModel");
					}
				}
				//ノンアニメーション
				else
				{
					if (isDrawToShadowMap)
					{
						//影
						m_Effect->SetTechnique("NoSkinModelRenderShadowMap");
					}
					else
					{
						//通常
						m_Effect->SetTechnique("NoSkinModel");
					}
				}
			}
		}

		//共通の定数レジスタを設定
		{
			//ビュープロジェクション行列
			if (isDrawToShadowMap)
			{
				m_Effect->SetMatrix("g_mViewProj", Shadow().GetLVPMatrix());
			}
			else
			{
				D3DXMATRIX viewProj;
				D3DXMatrixMultiply(&viewProj, &m_camera->GetViewMatrix(),&m_camera->GetProjectionMatrix());
				m_Effect->SetMatrix("g_mViewProj", &viewProj);
			}

			//ライト
			m_Effect->SetValue("g_light", m_Light, sizeof(CLight));

			//true or false 最終的にGPUに送る
			int flag[4] = { 0 };
			
			//法線マップ
			if (m_NormalMap != nullptr)
			{
				flag[0] = true;
				m_Effect->SetTexture("g_normalMap", m_NormalMap->GetTextureDX());
			}

			//シャドウレシーバー
			if (!isDrawToShadowMap && m_isShadowReceiver)
			{
				flag[1] = true;
				m_Effect->SetTexture("g_ShadowTexture", Shadow().GetTexture()->GetTextureDX());
				m_Effect->SetMatrix("g_mLVP", Shadow().GetLVPMatrix());
			}

			//リムライト
			if (m_isRimLight)
			{
				flag[2] = true;
			}

			//輝度
			if (m_isLuminance)
			{
				flag[3] = true;
			}
			m_Effect->SetValue("g_flags", flag, sizeof(flag));

			//スペキュラとフォグで使用
			D3DXVECTOR3 cameraPos;
			cameraPos.x = m_camera->GetViewInvMatrix().m[3][0];
			cameraPos.y = m_camera->GetViewInvMatrix().m[3][1];
			cameraPos.z = m_camera->GetViewInvMatrix().m[3][2];
			m_Effect->SetVector("g_cameraPos", (D3DXVECTOR4*)&cameraPos);

			//スペキュラマップ
			if (m_SpecMap != nullptr)
			{
				m_Effect->SetTexture("g_speculerMap", m_SpecMap->GetTextureDX());
				m_Effect->SetBool("g_isSpec", true);
			}
			else
			{
				m_Effect->SetBool("g_isSpec", false);
			}

			D3DXVECTOR4 fogParam;
			if (m_fogFunc == enFogFuncDist) {
				//距離フォグ
				fogParam.x = m_fogParam[0];
				fogParam.y = m_fogParam[1];
				fogParam.z = 1.0f;
			}
			else if (m_fogFunc == enFogFuncHeight) {
				//高さフォグ
				fogParam.x = m_fogParam[0];
				fogParam.y = m_fogParam[1];
				fogParam.z = 2.0f;
			}
			else {
				fogParam.z = 0.0f;
			}
			
			m_Effect->SetVector("g_fogParam",&fogParam);

		}

		//アニメーション
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
						NK_ASSERT(iPaletteEntry < MAX_MATRIX_PALLET, "ボーン行列パレットの最大数を超えた");
						D3DXMatrixMultiply(
							&m_BoneMatrixPallet[iPaletteEntry],
							&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
					}
				}

				m_Effect->SetMatrixArray("g_mWorldMatrixArray", m_BoneMatrixPallet, pMeshContainer->NumPaletteEntries);
				//ボーンの数
				m_Effect->SetInt("g_numBone", pMeshContainer->NumInfl);
				
				//ディフューズテクスチャ
				m_Effect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

				//カメラの回転行列の逆行列
				m_Effect->SetMatrix("g_mViewMatrixRotInv",&m_camera->GetRotationInvMatrix());

				m_Effect->Begin(0, D3DXFX_DONOTSAVESTATE);
				m_Effect->BeginPass(0);
				m_Effect->CommitChanges();

				//インスタンシング
				if (m_Skinmodel->GetNumInstance() != 0)
				{
					DrawMeshContainer_InstancingDrawCommon(pMeshContainer, iAttrib);
				}
				//通常
				else
				{
					pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				}
				m_Effect->EndPass();
				m_Effect->End();
			}
		}
		//アニメーションなし
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
				//ディフューズテクスチャ
				m_Effect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
				m_Effect->CommitChanges();

				//インスタンシング
				if (m_Skinmodel->GetNumInstance() != 0)
				{
					DrawMeshContainer_InstancingDrawCommon(pMeshContainer, 0);
					//DrawMeshContainer_InstancingDrawCommon(pMeshContainer, i);//ここiじゃね？
				}
				//通常
				else
				{
					pMeshContainer->MeshData.pMesh->DrawSubset(i);
				}
			}

			m_Effect->EndPass();
			m_Effect->End();
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

		//頂点バッファをストリーム０番目に設定
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

		//後始末
		d3dDevice->SetStreamSourceFreq(0, 1);
		d3dDevice->SetStreamSourceFreq(1, 1);
	}

}