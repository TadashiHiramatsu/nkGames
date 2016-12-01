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
			//�C���X�^���V���O���f���̓��f���f�[�^�̎g���܂킵�s��
			CSkinModelDataPtr SkinModelData(new CSkinModelData);
			SkinModelData->LoadModelData(_FilePath, _Anim);
		
			//�C���X�^���V���O�`��p�̃f�[�^���쐬
			D3DVERTEXELEMENT9 VertexElement[] = {
				{ 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },  // WORLD 1�s��
				{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },  // WORLD 2�s��
				{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },  // WORLD 3�s��
				{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },  // WORLD 4�s��
				D3DDECL_END()
			};

			//�C���X�^���V���O�`��p�f�[�^��ݒ�
			SkinModelData->CreateInstancingRenderData(_NumInstancing, VertexElement);

			//���X�g�ɓo�^
			InstancingList.push_back(SkinModelData);
			_SkinModelDataHandle.Init(SkinModelData, _Anim, false);
		}
		else
		{
			//�ʏ탂�f��
			int hash = CHash::MakeHash(_FilePath);
			auto& it = SkinModelDataMap.find(hash);
			
			if (it == SkinModelDataMap.end())
			{
				//���o�^
				CSkinModelDataPtr SkinModelData(new CSkinModelData);
				SkinModelData->LoadModelData(_FilePath, _Anim);
				SkinModelDataMap.insert(pair<int, CSkinModelDataPtr>(hash, SkinModelData));
				_SkinModelDataHandle.Init(SkinModelData, _Anim, false);
			}
			else
			{
				//����
				_SkinModelDataHandle.Init(it->second, _Anim, true);
			}
		}
	}

	void CSkinModelDataResources::Load(const char * _FilePath)
	{
		//�ʏ탂�f��
		int hash = CHash::MakeHash(_FilePath);
		auto& it = SkinModelDataMap.find(hash);

		if (it == SkinModelDataMap.end())
		{
			//���o�^
			CSkinModelDataPtr SkinModelData(new CSkinModelData);
			SkinModelData->LoadModelData(_FilePath, nullptr);
			SkinModelDataMap.insert(pair<int, CSkinModelDataPtr>(hash, SkinModelData));
		}
	}
	
}