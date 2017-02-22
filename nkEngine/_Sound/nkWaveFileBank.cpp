#include"nkEngine/nkstdafx.h"
#include"nkWaveFile.h"
#include"nkWaveFileBank.h"

namespace nkEngine
{
	void WaveFileBank::SetWaveFile(int groupID, WaveFilePtrT wavefile)
	{
		WaveFileMap_[groupID].insert({ wavefile->GetFileNameHash(),wavefile });
	}

	WaveFilePtrT WaveFileBank::FindWaveFile(int groupID, const char * filename)
	{
		auto& value = WaveFileMap_[groupID].find(Hash::MakeHash(filename));
		if (value != WaveFileMap_[groupID].end())
		{
			//Œ©‚Â‚©‚Á‚½.
			return value->second;
		}
		//Œ©‚Â‚©‚ç‚È‚¢.
		return nullptr;
	}

	void WaveFileBank::Release(int groupID)
	{
		for (auto& wf : WaveFileMap_[groupID])
		{
			wf.second->Release();
		}
		WaveFileMap_[groupID].clear();
	}

}