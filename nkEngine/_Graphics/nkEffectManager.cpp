#include"nkEngine/nkstdafx.h"
#include"nkEffectManager.h"

namespace nkEngine
{
	CEffectManager::CEffectManager()
	{
	}
	CEffectManager::~CEffectManager()
	{
		Release();
	}
	ID3DXEffect * CEffectManager::LoadEffect(const char * filePath)
	{
		ID3DXEffect* pEffect = nullptr;
		int hash = CHash::MakeHash(filePath);

		auto it = m_effectDictinary.find(hash);

		if (it == m_effectDictinary.end())
		{
			//êVãK
			char* baseDir = "Shader/";
			char fileP[64];
			strcpy(fileP, baseDir);
			strcat(fileP, filePath);
			LPD3DXBUFFER  compileErrorBuffer = nullptr;
			HRESULT hr = D3DXCreateEffectFromFile(
				Engine().GetDevice(),
				fileP,
				NULL,
				NULL,
#ifdef _DEBUG
				D3DXSHADER_DEBUG,
#else
				D3DXSHADER_SKIPVALIDATION,
#endif
				NULL,
				&pEffect,
				&compileErrorBuffer
			);
			if (FAILED(hr)) {
				MessageBox(nullptr, r_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
				NK_ASSERT(SUCCEEDED(hr), "error");
			}

			pair<int, ID3DXEffect*> node(hash, pEffect);
			m_effectDictinary.insert(node);
		}
		else
		{
			//ìoò^çœÇ›ÅB
			pEffect = it->second;
		}

		return pEffect;
	}
	void CEffectManager::Release()
	{
		for (auto p : m_effectDictinary) {
			SAFE_RELEASE(p.second);
		}
		m_effectDictinary.clear();
	}
}