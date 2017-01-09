/**
 * @file _Graphics\nkEffectManager.cpp
 *
 * エフェクトマネージャクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkEffectManager.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CEffectManager::CEffectManager()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CEffectManager::~CEffectManager()
	{
		Release();
	}

	/**
	* エフェクトのロード.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param filePath ファイルパス.
	*
	* @return ロードしたエフェクト.
	*/
	ID3DXEffect * CEffectManager::LoadEffect(const char * filePath)
	{
		//エフェクトの作成
		ID3DXEffect* pEffect = nullptr;

		//ハッシュ値の作成
		int hash = Hash::MakeHash(filePath);

		//ハッシュ値から探す
		auto it = EffectDictinary_.find(hash);

		if (it == EffectDictinary_.end())
		{
			//新規
			
			//ファイルパスを作成
			char* baseDir = "Asset/Shader/";
			char fp[64];
			strcpy(fp, baseDir);
			strcat(fp, filePath);

			LPD3DXBUFFER  compileErrorBuffer = nullptr;

			//ファイルをロード
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
				&pEffect,
				&compileErrorBuffer
			);

			//エラー
			if (FAILED(hr)) {
				MessageBox(nullptr, r_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
				NK_ASSERT(SUCCEEDED(hr), "error");
			}

			//保存
			EffectDictinary_.insert(make_pair(hash, pEffect));
		}
		else
		{
			//登録済み。
			pEffect = it->second;
		}

		return pEffect;
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