/**
 * @file	_Resources\nkSkinModelDataResources.cpp
 *
 * スキンモデルのリソースクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSkinModelDataResources.h"
#include"nkSkinModelDataHandle.h"

namespace nkEngine
{

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	CSkinModelDataResources::CSkinModelDataResources()
	{

	}

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	CSkinModelDataResources::~CSkinModelDataResources()
	{
	
	}

	/**
	 * 読み取り.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param [in,out]	skinModelDataHandle	スキンモデルデータハンドル.
	 * @param 		  	filePath		   	ファイルパス.
	 * @param [in,out]	anim			   	アニメーション.
	 * @param 		  	isInstancing	   	インスタンシングフラグ.
	 * @param 		  	numInstancing	   	インスタンス数.
	 */
	void CSkinModelDataResources::Load(SkinModelDataHandle& skinModelDataHandle, const char* filePath, CAnimation* anim, bool isInstancing, int numInstancing)
	{
		if (isInstancing)
		{
			//インスタンシングモデルはモデルデータの使いまわし不可
			SkinModelDataPtrT SkinModelData(new CSkinModelData);
			SkinModelData->LoadModelData(filePath, anim);
		
			//インスタンシング描画用のデータを作成
			D3DVERTEXELEMENT9 VertexElement[] = {
				{ 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },  // WORLD 1行目
				{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },  // WORLD 2行目
				{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },  // WORLD 3行目
				{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },  // WORLD 4行目
				D3DDECL_END()
			};

			//インスタンシング描画用データを設定
			SkinModelData->CreateInstancingRenderData(numInstancing, VertexElement);

			//リストに登録
			InstancingList_.push_back(SkinModelData);
			skinModelDataHandle.Init(SkinModelData, anim, false);
		}
		else
		{
			//通常モデル
			int hash = CHash::MakeHash(filePath);
			auto& it = SkinModelDataMap_.find(hash);
			
			if (it == SkinModelDataMap_.end())
			{
				//未登録
				SkinModelDataPtrT SkinModelData(new CSkinModelData);
				SkinModelData->LoadModelData(filePath, anim);
				SkinModelDataMap_.insert(make_pair(hash, SkinModelData));
				skinModelDataHandle.Init(SkinModelData, anim, false);
			}
			else
			{
				//既存
				skinModelDataHandle.Init(it->second, anim, true);
			}
		}
	}

}// namespace nkEngine