/**
 * @file	_Resources\nkSkinModelDataResources.cpp
 *
 * �X�L�����f���̃��\�[�X�N���X�̎���.
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
	 * �ǂݎ��.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param [in,out]	skinModelDataHandle	�X�L�����f���f�[�^�n���h��.
	 * @param 		  	filePath		   	�t�@�C���p�X.
	 * @param [in,out]	anim			   	�A�j���[�V����.
	 * @param 		  	isInstancing	   	�C���X�^���V���O�t���O.
	 * @param 		  	numInstancing	   	�C���X�^���X��.
	 */
	void CSkinModelDataResources::Load(SkinModelDataHandle& skinModelDataHandle, const char* filePath, CAnimation* anim, bool isInstancing, int numInstancing)
	{
		if (isInstancing)
		{
			//�C���X�^���V���O���f���̓��f���f�[�^�̎g���܂킵�s��
			SkinModelDataPtrT SkinModelData(new CSkinModelData);
			SkinModelData->LoadModelData(filePath, anim);
		
			//�C���X�^���V���O�`��p�̃f�[�^���쐬
			D3DVERTEXELEMENT9 VertexElement[] = {
				{ 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },  // WORLD 1�s��
				{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },  // WORLD 2�s��
				{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },  // WORLD 3�s��
				{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },  // WORLD 4�s��
				D3DDECL_END()
			};

			//�C���X�^���V���O�`��p�f�[�^��ݒ�
			SkinModelData->CreateInstancingRenderData(numInstancing, VertexElement);

			//���X�g�ɓo�^
			InstancingList_.push_back(SkinModelData);
			skinModelDataHandle.Init(SkinModelData, anim, false);
		}
		else
		{
			//�ʏ탂�f��
			int hash = CHash::MakeHash(filePath);
			auto& it = SkinModelDataMap_.find(hash);
			
			if (it == SkinModelDataMap_.end())
			{
				//���o�^
				SkinModelDataPtrT SkinModelData(new CSkinModelData);
				SkinModelData->LoadModelData(filePath, anim);
				SkinModelDataMap_.insert(make_pair(hash, SkinModelData));
				skinModelDataHandle.Init(SkinModelData, anim, false);
			}
			else
			{
				//����
				skinModelDataHandle.Init(it->second, anim, true);
			}
		}
	}

}// namespace nkEngine