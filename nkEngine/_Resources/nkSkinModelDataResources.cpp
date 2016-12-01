#include"nkEngine/nkstdafx.h"
#include"nkSkinModelDataResources.h"
#include"nkSkinModelDataHandle.h"

namespace nkEngine
{
	CSkinModelDataResources::CSkinModelDataResources()
	{

	}

	CSkinModelDataResources::~CSkinModelDataResources()
	{
	
	}
	
	void CSkinModelDataResources::Load(CSkinModelDataHandle& _SkinModelDataHandle, const char* _FilePath, CAnimation* _Anim, bool _isInstancing, int _NumInstancing)
	{
		if (_isInstancing)
		{
			//インスタンシングモデルはモデルデータの使いまわし不可
			CSkinModelDataPtr SkinModelData(new CSkinModelData);
			SkinModelData->LoadModelData(_FilePath, _Anim);
		
			//インスタンシング描画用のデータを作成
			D3DVERTEXELEMENT9 VertexElement[] = {
				{ 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },  // WORLD 1行目
				{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },  // WORLD 2行目
				{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },  // WORLD 3行目
				{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },  // WORLD 4行目
				D3DDECL_END()
			};

			//インスタンシング描画用データを設定
			SkinModelData->CreateInstancingRenderData(_NumInstancing, VertexElement);

			//リストに登録
			InstancingList.push_back(SkinModelData);
			_SkinModelDataHandle.Init(SkinModelData, _Anim, false);
		}
		else
		{
			//通常モデル
			int hash = CHash::MakeHash(_FilePath);
			auto& it = SkinModelDataMap.find(hash);
			
			if (it == SkinModelDataMap.end())
			{
				//未登録
				CSkinModelDataPtr SkinModelData(new CSkinModelData);
				SkinModelData->LoadModelData(_FilePath, _Anim);
				SkinModelDataMap.insert(pair<int, CSkinModelDataPtr>(hash, SkinModelData));
				_SkinModelDataHandle.Init(SkinModelData, _Anim, false);
			}
			else
			{
				//既存
				_SkinModelDataHandle.Init(it->second, _Anim, true);
			}
		}
	}

	void CSkinModelDataResources::Load(const char * _FilePath)
	{
		//通常モデル
		int hash = CHash::MakeHash(_FilePath);
		auto& it = SkinModelDataMap.find(hash);

		if (it == SkinModelDataMap.end())
		{
			//未登録
			CSkinModelDataPtr SkinModelData(new CSkinModelData);
			SkinModelData->LoadModelData(_FilePath, nullptr);
			SkinModelDataMap.insert(pair<int, CSkinModelDataPtr>(hash, SkinModelData));
		}
	}
	
}