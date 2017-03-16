/**
* ウェーブファイルバンククラスの実装.
*/
#include"nkEngine/nkstdafx.h"
#include"nkWaveFile.h"
#include"nkWaveFileBank.h"

namespace nkEngine
{

	/**
	* 波形データを登録.
	*
	* @param groupID	グループID.
	* @param wavefile	波形データ.
	*/
	void WaveFileBank::SetWaveFile(int groupID, WaveFilePtrT wavefile)
	{
		WaveFileMap_[groupID].insert({ wavefile->GetFileNameHash(),wavefile });
	}

	/**
	* 引数で指定したファイルパスの波形データがバンクに登録されているか検索する.
	*
	* @param groupID	グループID.
	* @param filepath	ファイル名.
	*/
	WaveFilePtrT WaveFileBank::FindWaveFile(int groupID, const char * filename)
	{
		auto& value = WaveFileMap_[groupID].find(Hash::MakeHash(filename));
		if (value != WaveFileMap_[groupID].end())
		{
			//見つかった.
			return value->second;
		}
		//見つからない.
		return nullptr;
	}

	/**
	* グループ単位で解放.
	*
	* @param groupID	グループID.
	*/
	void WaveFileBank::Release(int groupID)
	{
		for (auto& wf : WaveFileMap_[groupID])
		{
			wf.second->Release();
		}
		WaveFileMap_[groupID].clear();
	}

}