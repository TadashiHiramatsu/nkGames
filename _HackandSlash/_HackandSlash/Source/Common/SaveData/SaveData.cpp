/**
* �Z�[�u�f�[�^�֌W���Ǘ�����N���X�̒�`.
*/
#include"stdafx.h"
#include"SaveData.h"

/**
* �ǂݍ���.
*
* @return true or false.
*/
bool CSaveData::Load()
{
	isContinue_ = Data_.Load(FileName_);

	return isContinue_;
}

/**
* ��������.
*/
void CSaveData::Save()
{

	for (auto& obj : SaveObject_)
	{
		obj->Save();
	}

	Data_.Save(FileName_);
}
