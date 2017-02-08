/**
 * @file _Graphics\nkEffectManager.cpp
 *
 * �G�t�F�N�g�}�l�[�W���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkEffectManager.h"

namespace nkEngine
{

	/**
	* �G�t�F�N�g�̃��[�h.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param filePath �t�@�C���p�X.
	*
	* @return ���[�h�����G�t�F�N�g.
	*/
	Effect* CEffectManager::LoadEffect(const char* filePath)
	{
		//�G�t�F�N�g�N���X�̍쐬
		Effect* effect = nullptr;

		//�n�b�V���l�̍쐬
		int hash = Hash::MakeHash(filePath);

		//�n�b�V���l����T��
		auto it = EffectDictinary_.find(hash);

		if (it == EffectDictinary_.end())
		{
			//�V�K�ǂݍ���
			
			//�t�@�C���p�X���쐬
			char* baseDir = "Asset/Shader/";
			char fp[64];
			strcpy(fp, baseDir);
			strcat(fp, filePath);

			ID3DXEffect* d3deffect = nullptr;
			LPD3DXBUFFER  compileErrorBuffer = nullptr;

			//�t�@�C�������[�h
			HRESULT hr = D3DXCreateEffectFromFile(
				Engine().GetDevice(),
				fp,
				NULL,
				NULL,
#ifdef _DEBUG
				D3DXSHADER_DEBUG,
#else
				D3DXSHADER_SKIPVALIDATION,
#endif
				NULL,
				&d3deffect,
				&compileErrorBuffer
			);

			//�G���[
			if (FAILED(hr)) {
				MessageBox(nullptr, r_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
				NK_ASSERT(SUCCEEDED(hr), "error");
			}

			effect = new Effect(d3deffect);

			//�ۑ�
			EffectDictinary_.insert(make_pair(hash, effect));
		}
		else
		{
			//�o�^�ς݁B
			effect = it->second;
		}

		return effect;
	}

	/**
	 * Releases this object.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CEffectManager::Release()
	{
		for (auto p : EffectDictinary_) {
			//SAFE_RELEASE(p.second);
		}
		EffectDictinary_.clear();
	}

}// namespace nkEngine