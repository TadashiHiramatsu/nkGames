/**
* セーブデータ関係を管理するクラスの定義.
*/
#include"stdafx.h"
#include"SaveData.h"

/**
* 読み込み.
*
* @return true or false.
*/
bool CSaveData::Load()
{
	isContinue_ = Data_.Load(FileName_);

	return isContinue_;
}

/**
* 書き込み.
*/
void CSaveData::Save()
{

	for (auto& obj : SaveObject_)
	{
		obj->Save();
	}

	Data_.Save(FileName_);
}
