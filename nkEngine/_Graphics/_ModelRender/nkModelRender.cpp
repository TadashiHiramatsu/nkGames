/**
 * @file _Graphics\_ModelRender\nkModelRender.cpp
 *
 * モデルレンダクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkModelRender.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
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
	 * デストラクタ.
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
		//エフェクトのロード
		Effect_ = EffectManager().LoadEffect("ModelRender.fx");

		//モデルデータのロード
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
		//エフェクトのロード
		Effect_ = EffectManager().LoadEffect("ModelRender.fx");

		//モデルのコピー
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
			// シャドウキャスター.
			// シャドウマップにモデルを設定
			Shadow().Entry(this);
		}
		
		if (ModelData_)
		{
			//ボーン行列の計算
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
			//描画
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
			//描画
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
		//メッシュコントローラの取得
		LPD3DXMESHCONTAINER MeshContainer = pFrame->pMeshContainer;

		while (MeshContainer != NULL)
		{
			//描画
			RenderMeshContainer(
				MeshContainer,
				pFrame, isRenderToShadowMap
			);

			MeshContainer = MeshContainer->pNextMeshContainer;
	
		}

		if (pFrame->pFrameSibling != NULL)
		{
			//兄弟
			RenderFrame(pFrame->pFrameSibling, isRenderToShadowMap);
		}

		if (pFrame->pFrameFirstChild != NULL)
		{
			//子供
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
		//メッシュコントローラの取得
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

		//フレームベースの取得
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
		LPD3DXBONECOMBINATION pBoneComb;

		//デバイスを取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		D3DCAPS9 d3dCaps;
		Device->GetDeviceCaps(&d3dCaps);


	
		//テクニックを設定
		{
			//インスタンシング描画
			if (ModelData_->GetNumInstance() != 0)
			{
				//アニメーション
				if (pMeshContainer->pSkinInfo != NULL)
				{
					if (isRenderToShadowMap)
					{
						//影
						Effect_->SetTechnique("SkinModelInstancingRenderToShadowMap");
					}
					else
					{
						//通常
						Effect_->SetTechnique("SkinModelInstancing");
					}
				}
				//ノンアニメーション
				else
				{
					if (isRenderToShadowMap)
					{
						//影
						Effect_->SetTechnique("NoSkinModelInstancingRenderToShadowMap");
					}
					else
					{
						//通常
						Effect_->SetTechnique("NoSkinModelInstancing");
					}
				}
			}
			//通常
			else
			{
				//アニメーション
				if (pMeshContainer->pSkinInfo != NULL)
				{
					if (isRenderToShadowMap)
					{
						//影
						Effect_->SetTechnique("SkinModelRenderShadowMap");
					}
					else
					{
						//通常
						Effect_->SetTechnique("SkinModel");
					}
				}
				//ノンアニメーション
				else
				{
					if (isRenderToShadowMap)
					{
						//影
						Effect_->SetTechnique("NoSkinModelRenderShadowMap");
					}
					else
					{
						//通常
						Effect_->SetTechnique("NoSkinModel");
					}
				}
			}
		}

		//開始
		Effect_->Begin(0, D3DXFX_DONOTSAVESTATE);
		Effect_->BeginPass(0);

		//共通の定数レジスタを設定
		{
			//ビュープロジェクション行列
			if (isRenderToShadowMap)
			{
				//シャドウの描画
				Effect_->SetMatrix("g_mViewProj", &Shadow().GetLightViewProjectionMatrix());
			}
			else
			{
				//通常の描画
				D3DXMATRIX viewProj;
				D3DXMatrixMultiply(&viewProj, &Camera_->GetViewMatrix(),&Camera_->GetProjectionMatrix());
				Effect_->SetMatrix("g_mViewProj", &viewProj);

				//アルファブレンディングを行う
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				// 透過処理を行う
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				// 半透明処理を行う
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			}

			//ライトを設定
			Effect_->SetValue("g_light", Light_, sizeof(Light));

			//色の設定
			Effect_->SetValue("g_Color", &Color_, sizeof(Color_));

			//true or false 最終的にGPUに送る
			int flag[4] = { 0 };
			
			//法線マップ
			if (NormalMap_ != nullptr)
			{
				flag[0] = true;
				Effect_->SetTexture("g_normalMap", NormalMap_->GetTexture());
			}

			//シャドウレシーバー
			if (!isRenderToShadowMap && isShadowReceiver_)
			{
				flag[1] = true;
				Effect_->SetTexture("g_ShadowMap_0", Shadow().GetTexture(0)->GetTexture());
				Effect_->SetTexture("g_ShadowMap_1", Shadow().GetTexture(1)->GetTexture());
				Effect_->SetTexture("g_ShadowMap_2", Shadow().GetTexture(2)->GetTexture());

				const CShadowMap::ShadowReceiverParamS& param = Shadow().GetShadowReceiverParam();
				Effect_->SetValue("g_ShadowReceiverParam", &param, sizeof(CShadowMap::ShadowReceiverParamS));
			}

			//リムライト
			if (isRimLight_)
			{
				flag[2] = true;
			}

			Effect_->SetValue("g_flags", flag, sizeof(flag));

			//スペキュラとフォグで使用
			//カメラのポジションを計算
			D3DXVECTOR3 cameraPos;
			cameraPos.x = Camera_->GetViewInvMatrix().m[3][0];
			cameraPos.y = Camera_->GetViewInvMatrix().m[3][1];
			cameraPos.z = Camera_->GetViewInvMatrix().m[3][2];
			Effect_->SetVector("g_cameraPos", (D3DXVECTOR4*)&cameraPos);

			//スペキュラマップ
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
				//距離フォグ
				fogParam.x = FogParam_[0];
				fogParam.y = FogParam_[1];
				fogParam.z = 1.0f;
			}
			else if (FogFunc_ == FogFuncHeight) 
			{
				//高さフォグ
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

		//アニメーション
		if (pMeshContainer->pSkinInfo != NULL)
		{
			pBoneComb = reinterpret_cast<D3DXBONECOMBINATION*>(pMeshContainer->BoneCombinationBuf_->GetBufferPointer());

			//属性グループをループ
			for (UINT iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroup_; iAttrib++)
			{
				//ボーン行列計算？
				for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
				{
					DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];

					if (iMatrixIndex != UINT_MAX)
					{
						NK_ASSERT(iPaletteEntry < MAX_MATRIX_PALLET, "ボーン行列パレットの最大数を超えた");
						NK_ASSERT(pMeshContainer->BoneMatrixPtrs_[iMatrixIndex] != NULL, "NULL");

						D3DXMatrixMultiply(
							&BoneMatrixPallets_[iPaletteEntry],
							&pMeshContainer->BoneOffsetMatrix_[iMatrixIndex],
							pMeshContainer->BoneMatrixPtrs_[iMatrixIndex]
						);

					}

				}

				//ボーン行列の配列
				Effect_->SetMatrixArray("g_mWorldMatrixArray", BoneMatrixPallets_, pMeshContainer->NumPaletteEntries);

				//ボーンの数
				Effect_->SetInt("g_numBone", pMeshContainer->NumInfl_);
				
				//ディフューズテクスチャ
				Effect_->SetTexture("g_diffuseTexture", pMeshContainer->Texture_[pBoneComb[iAttrib].AttribId]);

				//カメラの回転行列の逆行列
				Effect_->SetMatrix("g_mViewMatrixRotInv",&Camera_->GetRotationInvMatrix());

				Effect_->CommitChanges();

				if (ModelData_->GetNumInstance() != 0)
				{
					//インスタンシング
					RenderMeshContainer_InstancingRenderCommon(pMeshContainer, iAttrib);
				}
				else
				{
					//通常
					pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				}

			}
		}
		//アニメーションなし
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

			//ワールド行列
			Effect_->SetMatrix("g_mWorldMatrix", &mWorld);

			//回転行列
			Effect_->SetMatrix("g_mRotation", &Transform_->RotationMatrix_);

			for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++)
			{
				//ディフューズテクスチャ
				Effect_->SetTexture("g_diffuseTexture", pMeshContainer->Texture_[i]);

				Effect_->CommitChanges();

				if (ModelData_->GetNumInstance() != 0)
				{
					//インスタンシング
					RenderMeshContainer_InstancingRenderCommon(pMeshContainer, 0);
					//RenderMeshContainer_InstancingRenderCommon(pMeshContainer, i);//ここiじゃね？
				}
				else
				{
					//通常
					pMeshContainer->MeshData.pMesh->DrawSubset(i);
				}
			}
		}

		//終了
		Effect_->EndPass();
		Effect_->End();

		//元に戻れ
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

		//頂点バッファの作成
		IDirect3DVertexBuffer9* vb;
		//インデックスバッファの作成
		IDirect3DIndexBuffer9* ib;

		ID3DXMesh* mesh = meshContainer->MeshData.pMesh;
		mesh->GetVertexBuffer(&vb);
		mesh->GetIndexBuffer(&ib);

		//頂点ストライドを取得
		DWORD stride = ModelData_->GetVertexBufferStride();

		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | ModelData_->GetNumInstance());
		Device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

		Device->SetVertexDeclaration(ModelData_->GetVertexDeclForInstancingRender());

		//頂点バッファをストリーム０番目に設定
		Device->SetStreamSource(0, vb, 0, stride);

		//ストリームを設定
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

		//後始末
		Device->SetStreamSourceFreq(0, 1);
		Device->SetStreamSourceFreq(1, 1);
	}

}// namespace nkEngine