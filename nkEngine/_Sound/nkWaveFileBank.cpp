/**
* �E�F�[�u�t�@�C���o���N�N���X�̎���.
*/
#include"nkEngine/nkstdafx.h"
#include"nkWaveFile.h"
#include"nkWaveFileBank.h"

namespace nkEngine
{

	/**
	* �g�`�f�[�^��o�^.
	*
	* @param groupID	�O���[�vID.
	* @param wavefile	�g�`�f�[�^.
	*/
	void WaveFileBank::SetWaveFile(int groupID, WaveFilePtrT wavefile)
	{
		WaveFileMap_[groupID].insert({ wavefile->GetFileNameHash(),wavefile });
	}

	/**
	* �����Ŏw�肵���t�@�C���p�X�̔g�`�f�[�^���o���N�ɓo�^����Ă��邩��������.
	*
	* @param groupID	�O���[�vID.
	* @param filepath	�t�@�C����.
	*/
	WaveFilePtrT WaveFileBank::FindWaveFile(int groupID, const char * filename)
	{
		auto& value = WaveFileMap_[groupID].find(Hash::MakeHash(filename));
		if (value != WaveFileMap_[groupID].end())
		{
			//��������.
			return value->second;
		}
		//������Ȃ�.
		return nullptr;
	}

	/**
	* �O���[�v�P�ʂŉ��.
	*
	* @param groupID	�O���[�vID.
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