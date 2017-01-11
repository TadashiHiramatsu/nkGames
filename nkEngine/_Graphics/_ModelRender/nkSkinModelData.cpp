/**
 * @file _Graphics\_ModelRender\nkSkinModelData.cpp
 *
 * スキンモデルデータクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSkinModelData.h"
#include"nkAnimation.h"

//無名空間
namespace 
{
	using namespace nkEngine;

	/**
	 * Inner destroy mesh container.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param meshContainerBase The mesh container base.
	 */
	void InnerDestroyMeshContainer(LPD3DXMESHCONTAINER meshContainerBase)
	{
		//メッシュコントローラの取得
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)meshContainerBase;

		//削除
		SAFE_DELETE_ARRAY(pMeshContainer->Name);
		SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
		SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
		//自作メンバの削除
		SAFE_DELETE_ARRAY(pMeshContainer->AttributeTable_);
		SAFE_DELETE_ARRAY(pMeshContainer->BoneOffsetMatrix_);

		//テクスチャが存在していれば
		if (pMeshContainer->Texture_ != NULL)
		{
			//マテリアル削除
			for (UINT iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
			{
				SAFE_RELEASE(pMeshContainer->Texture_[iMaterial]);
			}
		}

		//解放
		SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
		SAFE_RELEASE(pMeshContainer->pSkinInfo);
		//自作メンバのデリート
		SAFE_DELETE_ARRAY(pMeshContainer->Texture_);
		SAFE_DELETE_ARRAY(pMeshContainer->BoneMatrixPtrs_);
		//自作メンバのリリース
		SAFE_RELEASE(pMeshContainer->BoneCombinationBuf_);
		SAFE_RELEASE(pMeshContainer->OrigMesh_);

		//メッシュコントローラの削除
		SAFE_DELETE(pMeshContainer);

	}

	/**
	 * Generates a skinned mesh.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] d3dDevice	  If non-null, the pd 3D device.
	 * @param [in,out] meshContainer If non-null, the mesh container.
	 *
	 * @return The skinned mesh.
	 */
	HRESULT GenerateSkinnedMesh(
		IDirect3DDevice9* d3dDevice,
		D3DXMESHCONTAINER_DERIVED* meshContainer
	)
	{
		HRESULT hr = S_OK;
		D3DCAPS9 d3dCaps;
		d3dDevice->GetDeviceCaps(&d3dCaps);

		if (meshContainer->pSkinInfo == NULL)
		{
			return hr;
		}

		SAFE_RELEASE(meshContainer->MeshData.pMesh);
		SAFE_RELEASE(meshContainer->BoneCombinationBuf_);

		{
			// Get palette size
			// First 9 constants are used for other data.  Each 4x3 matrix takes up 3 constants.
			// (96 - 9) /3 i.e. Maximum constant count - used constants 
			UINT MaxMatrices = 26;
			meshContainer->NumPaletteEntries = min(MaxMatrices, meshContainer->pSkinInfo->GetNumBones());

			DWORD Flags = D3DXMESHOPT_VERTEXCACHE;
			if (d3dCaps.VertexShaderVersion >= D3DVS_VERSION(1, 1))
			{
				meshContainer->UseSoftwareVP = false;
				Flags |= D3DXMESH_MANAGED;
			}
			else
			{
				meshContainer->UseSoftwareVP = true;
				Flags |= D3DXMESH_SYSTEMMEM;
			}

			//メッシュの解放
			SAFE_RELEASE(meshContainer->MeshData.pMesh);


			hr = meshContainer->pSkinInfo->ConvertToIndexedBlendedMesh
			(
				meshContainer->OrigMesh_,
				Flags,
				meshContainer->NumPaletteEntries,
				meshContainer->pAdjacency,
				NULL, NULL, NULL,
				&meshContainer->NumInfl_,
				&meshContainer->NumAttributeGroup_,
				&meshContainer->BoneCombinationBuf_,
				&meshContainer->MeshData.pMesh
			);

			if (FAILED(hr))
			{
				goto e_Exit;
			}


			// FVF has to match our declarator. Vertex shaders are not as forgiving as FF pipeline
			DWORD NewFVF = (meshContainer->MeshData.pMesh->GetFVF() & D3DFVF_POSITION_MASK) | D3DFVF_NORMAL |
				D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4;

			if (NewFVF != meshContainer->MeshData.pMesh->GetFVF())
			{
				LPD3DXMESH pMesh;
				hr = meshContainer->MeshData.pMesh->CloneMeshFVF(meshContainer->MeshData.pMesh->GetOptions(), NewFVF,
					d3dDevice, &pMesh);

				if (!FAILED(hr))
				{
					meshContainer->MeshData.pMesh->Release();
					meshContainer->MeshData.pMesh = pMesh;
					pMesh = NULL;
				}
			}

			D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
			LPD3DVERTEXELEMENT9 pDeclCur;
			hr = meshContainer->MeshData.pMesh->GetDeclaration(pDecl);

			if (FAILED(hr))
			{
				goto e_Exit;
			}

			// the vertex shader is expecting to interpret the UBYTE4 as a D3DCOLOR, so update the type 
			//   NOTE: this cannot be done with CloneMesh, that would convert the UBYTE4 data to float and then to D3DCOLOR
			//          this is more of a "cast" operation
			pDeclCur = pDecl;
			while (pDeclCur->Stream != 0xff)
			{
				if ((pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) && (pDeclCur->UsageIndex == 0))
				{
					pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
				}

				pDeclCur++;
			}

			hr = meshContainer->MeshData.pMesh->UpdateSemantics(pDecl);

			if (FAILED(hr))
			{
				goto e_Exit;
			}

		}

	e_Exit:
		return hr;

	}

	/**
	 * Allocate name.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param 		   name	    The name.
	 * @param [in,out] newName If non-null, name of the new.
	 *
	 * @return A hResult.
	 */
	HRESULT AllocateName(LPCSTR name, LPSTR* newName)
	{
		UINT cbLength;

		//名前がない
		if (name != NULL)
		{
			cbLength = (UINT)strlen(name) + 1;
			
			*newName = new CHAR[cbLength];
			if (*newName == NULL)
			{
				return E_OUTOFMEMORY;
			}

			memcpy(*newName, name, cbLength * sizeof(CHAR));
		
		}
		else
		{
			*newName = NULL;
		}

		return S_OK;
	}

	/**
	 * --------------------------------------------------------------------------------------
	 *  Called to setup the pointers for a given bone to its transformation matrix
	 * --------------------------------------------------------------------------------------.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param meshContainerBase The mesh container base.
	 * @param rootFrame			 The root frame.
	 *
	 * @return A hResult.
	 */
	HRESULT SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER meshContainerBase, LPD3DXFRAME rootFrame)
	{
		UINT iBone, cBones;
		D3DXFRAME_DERIVED* pFrame;

		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)meshContainerBase;

		// if there is a skinmesh, then setup the bone matrices
		if (pMeshContainer->pSkinInfo != NULL)
		{
			cBones = pMeshContainer->pSkinInfo->GetNumBones();

			//ボーンマトリクスのポインタを作成
			pMeshContainer->BoneMatrixPtrs_ = new D3DXMATRIX*[cBones];
			if (pMeshContainer->BoneMatrixPtrs_ == NULL)
			{
				return E_OUTOFMEMORY;
			}

			for (iBone = 0; iBone < cBones; iBone++)
			{
				pMeshContainer->BoneMatrixPtrs_[iBone] = NULL;
				LPCSTR boneName = pMeshContainer->pSkinInfo->GetBoneName(iBone);

				//フレーム呼び出し
				pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(rootFrame,boneName);

				if (pFrame == NULL)
				{
					//ない
					return E_FAIL;
				}

				//登録
				pMeshContainer->BoneMatrixPtrs_[iBone] = &pFrame->CombinedTransformationMatrix_;

			}

		}

		return S_OK;
	}

	/**
	 * An allocate hierarchy.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class AllocateHierarchy : public ID3DXAllocateHierarchy
	{
	public:

		/**
		* コンストラクタ.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/10
		*/
		AllocateHierarchy()
		{
		}

		STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
		STDMETHOD(CreateMeshContainer)(THIS_
			LPCSTR Name,
			CONST D3DXMESHDATA *pMeshData,
			CONST D3DXMATERIAL *pMaterials,
			CONST D3DXEFFECTINSTANCE *pEffectInstances,
			DWORD NumMaterials,
			CONST DWORD *pAdjacency,
			LPD3DXSKININFO pSkinInfo,
			LPD3DXMESHCONTAINER *ppNewMeshContainer);
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);
		
	};

	/**
	 * --------------------------------------------------------------------------------------
	 *  Name: AllocateHierarchy::CreateFrame()
	 *  Desc:
	 * --------------------------------------------------------------------------------------.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param 		   Name		  The name.
	 * @param [in,out] ppNewFrame If non-null, the new frame.
	 *
	 * @return The new frame.
	 */
	HRESULT AllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
	{
		HRESULT hr = S_OK;
		D3DXFRAME_DERIVED* pFrame;

		*ppNewFrame = NULL;

		pFrame = new D3DXFRAME_DERIVED;
		if (pFrame == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		hr = AllocateName(Name, &pFrame->Name);
		if (FAILED(hr))
			goto e_Exit;

		// initialize other data members of the frame
		D3DXMatrixIdentity(&pFrame->TransformationMatrix);
		D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix_);

		pFrame->pMeshContainer = NULL;
		pFrame->pFrameSibling = NULL;
		pFrame->pFrameFirstChild = NULL;

		*ppNewFrame = pFrame;
		pFrame = NULL;

	e_Exit:
		delete pFrame;
		return hr;
	}

	/**
	 * --------------------------------------------------------------------------------------
	 *  Name: AllocateHierarchy::CreateMeshContainer()
	 *  Desc:
	 * --------------------------------------------------------------------------------------.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param 		   Name				  The name.
	 * @param 		   pMeshData		  Information describing the mesh.
	 * @param 		   pMaterials		  The materials.
	 * @param 		   pEffectInstances   The effect instances.
	 * @param 		   NumMaterials		  Number of materials.
	 * @param 		   pAdjacency		  The adjacency.
	 * @param 		   pSkinInfo		  Information describing the skin.
	 * @param [in,out] ppNewMeshContainer If non-null, the new mesh container.
	 *
	 * @return The new mesh container.
	 */
	HRESULT AllocateHierarchy::CreateMeshContainer(
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer)
	{
		HRESULT hr;
		D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;
		UINT NumFaces;
		UINT iMaterial;
		UINT iBone, cBones;
		LPDIRECT3DDEVICE9 pd3dDevice = NULL;

		LPD3DXMESH pMesh = NULL;

		*ppNewMeshContainer = NULL;

		// this sample does not handle patch meshes, so fail when one is found
		if (pMeshData->Type != D3DXMESHTYPE_MESH)
		{
			hr = E_FAIL;
			goto e_Exit;
		}

		// get the pMesh interface pointer out of the mesh data structure
		pMesh = pMeshData->pMesh;
		DWORD numVert = pMesh->GetNumVertices();
		// this sample does not FVF compatible meshes, so fail when one is found
		if (pMesh->GetFVF() == 0)
		{
			hr = E_FAIL;
			goto e_Exit;
		}

		// allocate the overloaded structure to return as a D3DXMESHCONTAINER
		pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
		if (pMeshContainer == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}
		memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

		// make sure and copy the name.  All memory as input belongs to caller, interfaces can be addref'd though
		hr = AllocateName(Name, &pMeshContainer->Name);
		if (FAILED(hr))
			goto e_Exit;
		
		pMesh->GetDevice(&pd3dDevice);
		NumFaces = pMesh->GetNumFaces();

		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		pMesh->AddRef();

		D3DVERTEXELEMENT9 decl[] = {
			{ 0, 0 ,	D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION		, 0 },
			{ 0, 16,    D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT	, 0 },
			{ 0, 32,    D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES	, 0 },
			{ 0, 48,	D3DDECLTYPE_FLOAT3		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL		, 0 },
			{ 0, 60,	D3DDECLTYPE_FLOAT3		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT		, 0 },
			{ 0, 72,	D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD		, 0 },
			D3DDECL_END()
		};


		// allocate memory to contain the material information.  This sample uses
		//   the D3D9 materials and texture names instead of the EffectInstance style materials
		pMeshContainer->NumMaterials = max(1, NumMaterials);
		pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
		pMeshContainer->Texture_ = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
		pMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
		if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces * 3);
		memset(pMeshContainer->Texture_, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

		// if materials provided, copy them
		if (NumMaterials > 0)
		{
			memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

			for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
			{
				if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
				{
					char* baseDir = "Asset/Texture/";
					char filePath[64];
					strcpy(filePath, baseDir);
					strcat(filePath, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
					if (FAILED(D3DXCreateTextureFromFile(
						pd3dDevice,
						filePath,
						&pMeshContainer->Texture_[iMaterial]))
						) {
						pMeshContainer->Texture_[iMaterial] = NULL;
					}

					// don't remember a pointer into the dynamic memory, just forget the name after loading
					pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
				}
			}
		}
		else // if no materials provided, use a default one
		{
			pMeshContainer->pMaterials[0].pTextureFilename = NULL;
			memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
			pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
			pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
			pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
			pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
		}

		// if there is skinning information, save off the required data and then setup for HW skinning
		if (pSkinInfo != NULL)
		{
			// first save off the SkinInfo and original mesh data
			pMeshContainer->pSkinInfo = pSkinInfo;
			pSkinInfo->AddRef();

			pMeshContainer->OrigMesh_ = pMesh;
			pMesh->AddRef();

			// Will need an array of offset matrices to move the vertices from the figure space to the bone's space
			cBones = pSkinInfo->GetNumBones();
			pMeshContainer->BoneOffsetMatrix_ = new D3DXMATRIX[cBones];

			if (pMeshContainer->BoneOffsetMatrix_ == NULL)
			{
				hr = E_OUTOFMEMORY;
				goto e_Exit;
			}

			// get each of the bone offset matrices so that we don't need to get them later
			for (iBone = 0; iBone < cBones; iBone++)
			{
				pMeshContainer->BoneOffsetMatrix_[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
			}

			// GenerateSkinnedMesh will take the general skinning information and transform it to a HW friendly version
			hr = GenerateSkinnedMesh(pd3dDevice, pMeshContainer);

			if (FAILED(hr))
				goto e_Exit;

			LPD3DXMESH pOutMesh, pTmpMesh;
			hr = pMeshContainer->MeshData.pMesh->CloneMesh(
				pMeshContainer->MeshData.pMesh->GetOptions(),
				decl,
				pd3dDevice, &pOutMesh);

			if (FAILED(hr))
				goto e_Exit;

			//一時メッシュに退避。
			pTmpMesh = pOutMesh;
			//D3DXComputeTangentFrameExを実行すると属性テーブルの情報が失われる・・・。
			DWORD numAttributeTable;
			pMeshContainer->MeshData.pMesh->GetAttributeTable(NULL, &numAttributeTable);
			pMeshContainer->AttributeTable_ = new D3DXATTRIBUTERANGE[numAttributeTable];
			pMeshContainer->MeshData.pMesh->GetAttributeTable(pMeshContainer->AttributeTable_, NULL);

			hr = D3DXComputeTangentFrameEx(
				pTmpMesh,
				D3DDECLUSAGE_TEXCOORD,
				0,
				D3DDECLUSAGE_TANGENT,
				0,
				D3DX_DEFAULT,
				0,
				D3DDECLUSAGE_NORMAL,
				0,
				0,
				NULL,
				0.01f,    //ボケ具合.値をおおきくするとぼけなくなる
				0.25f,
				0.01f,
				&pOutMesh,
				NULL
			);

			//一時メッシュを破棄。
			SAFE_RELEASE(pTmpMesh);
			SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
			pMeshContainer->MeshData.pMesh = pOutMesh;

			if (FAILED(hr))
			{
				goto e_Exit;
			}

		}
		else 
		{

			pMeshContainer->OrigMesh_ = pMesh;
			pMesh->AddRef();

			LPD3DXMESH pOutMesh, pTmpMesh;
			DWORD numVert = pMeshContainer->MeshData.pMesh->GetNumVertices();
			hr = pMeshContainer->MeshData.pMesh->CloneMesh(
				pMeshContainer->MeshData.pMesh->GetOptions(),
				decl,
				pd3dDevice, &pOutMesh);
			DWORD numAttributeTable;
			pMeshContainer->MeshData.pMesh->GetAttributeTable(NULL, &numAttributeTable);
			pMeshContainer->AttributeTable_ = new D3DXATTRIBUTERANGE[numAttributeTable];
			pMeshContainer->MeshData.pMesh->GetAttributeTable(pMeshContainer->AttributeTable_, NULL);
			numVert = pMeshContainer->MeshData.pMesh->GetNumVertices();
			
			//一時メッシュに退避。
			pTmpMesh = pOutMesh; 
			
			hr = D3DXComputeTangentFrameEx(
				pTmpMesh,
				D3DDECLUSAGE_TEXCOORD,
				0,
				D3DDECLUSAGE_TANGENT,
				0,
				D3DX_DEFAULT,
				0,
				D3DDECLUSAGE_NORMAL,
				0,
				0,
				NULL,
				0.01f,    //ボケ具合.値をおおきくするとぼけなくなる
				0.25f,
				0.01f,
				&pOutMesh,
				NULL
			);

			//一時メッシュを破棄。
			SAFE_RELEASE(pTmpMesh);
			numVert = pOutMesh->GetNumVertices();
			SAFE_RELEASE(pMesh);
			pMeshContainer->MeshData.pMesh = pOutMesh;
			if (FAILED(hr))
				goto e_Exit;

		}

		*ppNewMeshContainer = pMeshContainer;

		pMeshContainer = NULL;

	e_Exit:

		SAFE_RELEASE(pd3dDevice);

		// call Destroy function to properly clean up the memory allocated 
		if (pMeshContainer != NULL)
		{
			DestroyMeshContainer(pMeshContainer);
		}

		return hr;
	}

	/**
	 * --------------------------------------------------------------------------------------
	 *  Name: AllocateHierarchy::DestroyFrame()
	 *  Desc:
	 * --------------------------------------------------------------------------------------.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param pFrameToFree The frame to free.
	 *
	 * @return A hResult.
	 */
	HRESULT AllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
	{
		SAFE_DELETE_ARRAY(pFrameToFree->Name);
		SAFE_DELETE(pFrameToFree);
		return S_OK;
	}

	/**
	 * --------------------------------------------------------------------------------------
	 *  Name: AllocateHierarchy::DestroyMeshContainer()
	 *  Desc:
	 * --------------------------------------------------------------------------------------.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param pMeshContainerBase The mesh container base.
	 *
	 * @return A hResult.
	 */
	HRESULT AllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
	{
		InnerDestroyMeshContainer(pMeshContainerBase);
		return S_OK;
	}

}

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	SkinModelData::SkinModelData() :
		FrameRoot_(nullptr),
		isClone_(false),
		D3DAnimController_(nullptr),
		VertexDeclForInstancingRender_(nullptr),
		numInstance_(0),
		VertexBufferStride_(0)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	SkinModelData::~SkinModelData()
	{
		Release();
	}

	/**
	 * Clone model data.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param 		   modelData Information describing the model.
	 * @param [in,out] anim		 If non-null, the animation.
	 */
	void SkinModelData::CloneModelData(const SkinModelData & modelData, Animation * anim)
	{
		//スケルトンの複製を作成
		isClone_ = true;

		FrameRoot_ = new D3DXFRAME_DERIVED;
		FrameRoot_->pFrameFirstChild = nullptr;
		FrameRoot_->pFrameSibling = nullptr;
		FrameRoot_->pMeshContainer = nullptr;

		//クローン作製
		CloneSkeleton(FrameRoot_, modelData.FrameRoot_);

		//アニメーションコントローラを作成して、スケルトンと関連付けを行う。
		if (modelData.D3DAnimController_)
		{
			//アニメーションコントローラをクローン
			modelData.D3DAnimController_->CloneAnimationController(
				modelData.D3DAnimController_->GetMaxNumAnimationOutputs(),
				modelData.D3DAnimController_->GetMaxNumAnimationSets(),
				modelData.D3DAnimController_->GetMaxNumTracks(),
				modelData.D3DAnimController_->GetMaxNumEvents(),
				&D3DAnimController_
			);

			//意味不
			SetupOutputAnimationRegist(FrameRoot_, D3DAnimController_);

			//アニメーションコントローラがあれば
			if (anim && D3DAnimController_)
			{
				//アニメーションクラスの初期化
				anim->Init(D3DAnimController_);
			}

		}

		//謎
		SetupBoneMatrixPointers(FrameRoot_, FrameRoot_);
	
	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void SkinModelData::Release()
	{

		SAFE_RELEASE(VertexDeclForInstancingRender_);

		if (isClone_ && FrameRoot_)
		{
			//クローン
			DeleteCloneSkeleton(FrameRoot_);
			FrameRoot_ = nullptr;
		}
		else
		{
			DeleteSkeleton(FrameRoot_);
		}

		//インスタンス用頂点バッファの解放
		InstanceVertexBuffer_.Release();

		numInstance_ = 0;

	}

	/**
	 * Deletes the skeleton described by frame.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param frame The frame.
	 */
	void SkinModelData::DeleteSkeleton(LPD3DXFRAME frame)
	{

		//フレームが無効
		if (!frame) 
		{
			return;
		}

		if (frame->pMeshContainer != NULL)
		{
			//メッシュコンテナがある。
			InnerDestroyMeshContainer(frame->pMeshContainer);
		}

		if (frame->pFrameSibling != NULL)
		{
			//兄弟がいる。
			DeleteSkeleton(frame->pFrameSibling);
		}

		if (frame->pFrameFirstChild != NULL)
		{
			//子供がいる。
			DeleteSkeleton(frame->pFrameFirstChild);
		}

		SAFE_DELETE_ARRAY(frame->Name);
		SAFE_DELETE(frame);

	}

	/**
	 * Loads model data.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param 		   filePath Full pathname of the file.
	 * @param [in,out] anim	    If non-null, the animation.
	 */
	void SkinModelData::LoadModelData(const char* filePath, Animation* anim)
	{

		//ファイルパスの作成
		char* baseDir = "Asset/Model/";
		char Path[64];
		strcpy(Path, baseDir);
		strcat(Path, filePath);
		
		AllocateHierarchy alloc;

		//ロード
		HRESULT hr = D3DXLoadMeshHierarchyFromX(
			Path,
			D3DXMESH_VB_MANAGED,
			Engine().GetDevice(),
			&alloc,
			nullptr,
			&FrameRoot_,
			&D3DAnimController_
		);

		NK_ASSERT(SUCCEEDED(hr), "D3DXLoadMeshHierarchyFromXに失敗しました");

		//謎
		SetupBoneMatrixPointers(FrameRoot_, FrameRoot_);

		if (anim && D3DAnimController_) 
		{
			//アニメーションクラスの初期化
			anim->Init(D3DAnimController_);
		}
		else 
		{
			//アニメーションコントローラの解放
			SAFE_RELEASE(D3DAnimController_);
		}
	}

	/**
	 * Creates instancing render data.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param 		   numInstance   Number of instances.
	 * @param [in,out] vertexElement If non-null, the vertex element.
	 */
	void SkinModelData::CreateInstancingRenderData(int numInstance, D3DVERTEXELEMENT9 * vertexElement)
	{
		numInstance_ = numInstance;

		CreateInstancingRenderData(FrameRoot_, numInstance_, vertexElement);
	}

	/**
	 * Creates instancing render data.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] frame		 If non-null, the frame.
	 * @param 		   numInstance   Number of instances.
	 * @param [in,out] vertexElement If non-null, the vertex element.
	 *
	 * @return True if it succeeds, false if it fails.
	 */
	bool SkinModelData::CreateInstancingRenderData(D3DXFRAME * frame, int numInstance, D3DVERTEXELEMENT9 * vertexElement)
	{
		if (frame->pMeshContainer)
		{
			//メッシュを発見
			//ストリーム１の頂点バッファを追加した頂点定義を作成する
			//頂点定義はすべてのメッシュで同じ
			D3DVERTEXELEMENT9 declElement[MAX_FVF_DECL_SIZE];
			frame->pMeshContainer->MeshData.pMesh->GetDeclaration(declElement);
			
			int elementIndex = 0;

			while (true)
			{
				if (declElement[elementIndex].Type == D3DDECLTYPE_UNUSED)
				{
					//元々の頂点定義の終端を発見
					//ここからインすランシング用の頂点レイアウトを埋め込む
					for (int i = 0; vertexElement[i].Type != D3DDECLTYPE_UNUSED; i++)
					{
						declElement[elementIndex] = vertexElement[i];
						elementIndex++;
					}

					//終端を埋め込んで終わり
					declElement[elementIndex] = D3DDECL_END();

					break;
				}

				elementIndex++;
			}

			//頂点定義の作成
			IDirect3DDevice9* d3dDevice;
			frame->pMeshContainer->MeshData.pMesh->GetDevice(&d3dDevice);
			d3dDevice->CreateVertexDeclaration(declElement, &VertexDeclForInstancingRender_);

			//頂点バッファの作成
			DWORD vertexBufferStride = D3DXGetDeclVertexSize(vertexElement, 1);
			InstanceVertexBuffer_.Create(numInstance, vertexBufferStride, vertexElement, nullptr);
		
			return true;
		}

		if (frame->pFrameSibling != nullptr)
		{
			//兄弟がいる
			if (CreateInstancingRenderData(frame->pFrameSibling, numInstance, vertexElement))
			{
				return true;
			}
		}

		if (frame->pFrameFirstChild != nullptr)
		{
			//子供がいる。
			if (CreateInstancingRenderData(frame->pFrameFirstChild, numInstance, vertexElement)) 
			{
				return true;
			}
		}

		return false;
	}

	/**
	 * Sets up the bone matrix pointers.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] pFrame	  If non-null, the frame.
	 * @param [in,out] pRootFrame If non-null, the root frame.
	 *
	 * @return A hResult.
	 */
	HRESULT SkinModelData::SetupBoneMatrixPointers(D3DXFRAME * pFrame, D3DXFRAME * pRootFrame)
	{
		HRESULT hr;

		if (pFrame->pMeshContainer != NULL)
		{
			//頂点ストライドもここで調べる。
			D3DVERTEXELEMENT9 Declaration[MAX_FVF_DECL_SIZE];
			pFrame->pMeshContainer->MeshData.pMesh->GetDeclaration(Declaration);
			VertexBufferStride_ = D3DXGetDeclVertexSize(Declaration, 0);
			hr = SetupBoneMatrixPointersOnMesh(pFrame->pMeshContainer, pRootFrame);
			
			if (FAILED(hr))
			{
				return hr;
			}

		}

		if (pFrame->pFrameSibling != NULL)
		{
			hr = SetupBoneMatrixPointers(pFrame->pFrameSibling, pRootFrame);

			if (FAILED(hr))
			{
				return hr;
			}
		}

		if (pFrame->pFrameFirstChild != NULL)
		{
			hr = SetupBoneMatrixPointers(pFrame->pFrameFirstChild, pRootFrame);
		
			if (FAILED(hr))
			{
				return hr;
			}
		}

		return S_OK;
	}

	/**
	 * Gets organisation mesh.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param frame The frame.
	 *
	 * @return The organisation mesh.
	 */
	LPD3DXMESH SkinModelData::GetOrgMesh(LPD3DXFRAME frame) const
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)(frame->pMeshContainer);
		
		if (pMeshContainer != nullptr)
		{
			return pMeshContainer->OrigMesh_;
		}
		
		if (frame->pFrameSibling != nullptr) 
		{
			//兄弟
			LPD3DXMESH mesh = GetOrgMesh(frame->pFrameSibling);

			if (mesh) 
			{
				return mesh;
			}
		}
		
		if (frame->pFrameFirstChild != nullptr)
		{
			//子供。
			LPD3DXMESH mesh = GetOrgMesh(frame->pFrameFirstChild);
			
			if (mesh) 
			{
				return mesh;
			}
		}

		return nullptr;
	}

	/**
	 * Gets organisation mesh first.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @return The organisation mesh first.
	 */
	LPD3DXMESH SkinModelData::GetOrgMeshFirst() const
	{
		return GetOrgMesh(FrameRoot_);
	}

	/**
	 * Sets up the output animation regist.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] frame  If non-null, the frame.
	 * @param [in,out] aniCon If non-null, the animation con.
	 */
	void SkinModelData::SetupOutputAnimationRegist(D3DXFRAME * frame, ID3DXAnimationController * aniCon)
	{
		if (aniCon == nullptr) 
		{
			return;
		}

		//ここ危険な気がする
		aniCon->RegisterAnimationOutput(frame->Name, &frame->TransformationMatrix, nullptr, nullptr, nullptr);

		if (frame->pFrameSibling != nullptr) 
		{
			SetupOutputAnimationRegist(frame->pFrameSibling, aniCon);
		}

		if (frame->pFrameFirstChild != nullptr)
		{
			SetupOutputAnimationRegist(frame->pFrameFirstChild, aniCon);
		}

	}

	/**
	 * Updates the bone matrix described by matWorld.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param matWorld The matrix world.
	 */
	void SkinModelData::UpdateBoneMatrix(const D3DXMATRIX& matWorld)
	{
		UpdateFrameMatrices(FrameRoot_, reinterpret_cast<const D3DXMATRIX*>(&matWorld));
	}

	/**
	 * Updates the frame matrices.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param pFrameBase    The frame base.
	 * @param pParentMatrix The parent matrix.
	 */
	void SkinModelData::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, const D3DXMATRIX* pParentMatrix)
	{
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

		if (pParentMatrix != NULL)
		{
			//親がいたので行列計算
			D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix_, &pFrame->TransformationMatrix, pParentMatrix);
		}
		else
		{
			//親がいない
			pFrame->CombinedTransformationMatrix_ = pFrame->TransformationMatrix;
		}

		if (pFrame->pFrameSibling != NULL)
		{
			//兄弟
			UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
		}

		if (pFrame->pFrameFirstChild != NULL)
		{
			//子供
			UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix_);
		}

	}

	/**
	 * Clone skeleton.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] dstFrame Destination frame.
	 * @param [in,out] srcFrame If non-null, source frame.
	 */
	void SkinModelData::CloneSkeleton(LPD3DXFRAME & dstFrame, D3DXFRAME * srcFrame)
	{
		//名前と行列をコピー
		dstFrame->TransformationMatrix = srcFrame->TransformationMatrix;

		//メッシュコンテナをコピー。メッシュは使いまわす
		if (srcFrame->pMeshContainer)
		{
			dstFrame->pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
			memcpy(dstFrame->pMeshContainer, srcFrame->pMeshContainer, sizeof(D3DXMESHCONTAINER_DERIVED));
		}
		else
		{
			dstFrame->pMeshContainer = nullptr;
		}

		//名前をコピー
		AllocateName(srcFrame->Name, &dstFrame->Name);

		if (srcFrame->pFrameSibling != nullptr)
		{
			//兄弟がいるので、兄弟のためのメモリも確保
			dstFrame->pFrameSibling = new D3DXFRAME_DERIVED;
			dstFrame->pFrameSibling->pFrameFirstChild = nullptr;
			dstFrame->pFrameSibling->pFrameSibling = nullptr;
			dstFrame->pFrameSibling->pMeshContainer = nullptr;
			
			CloneSkeleton(dstFrame->pFrameSibling, srcFrame->pFrameSibling);
		}

		if (srcFrame->pFrameFirstChild != nullptr)
		{
			//子供がいるので、子供のためのメモリを確保
			dstFrame->pFrameFirstChild = new D3DXFRAME_DERIVED;
			dstFrame->pFrameFirstChild->pFrameFirstChild = nullptr;
			dstFrame->pFrameFirstChild->pFrameSibling = nullptr;
			dstFrame->pFrameFirstChild->pMeshContainer = nullptr;

			CloneSkeleton(dstFrame->pFrameFirstChild, srcFrame->pFrameFirstChild);
		}

	}

	/**
	 * Deletes the clone skeleton described by frame.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] frame If non-null, the frame.
	 */
	void SkinModelData::DeleteCloneSkeleton(D3DXFRAME * frame)
	{
		if (frame->pFrameSibling != nullptr)
		{
			//兄弟
			DeleteCloneSkeleton(frame->pFrameSibling);
		}

		if (frame->pFrameFirstChild != nullptr)
		{
			//子供
			DeleteCloneSkeleton(frame->pFrameFirstChild);
		}
		
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)(frame->pMeshContainer);
		
		if (pMeshContainer)
		{
			delete[] pMeshContainer->BoneMatrixPtrs_;
			delete pMeshContainer;
		}

		delete[] frame->Name;
		delete frame;

	}

}// namespace nkEngine