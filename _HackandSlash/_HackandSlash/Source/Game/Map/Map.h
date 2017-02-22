#pragma once

#include"MapChip.h"

/**
* �}�b�v�ǂݎ��N���X.
*/
class Map : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	Map()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~Map()
	{
	}

	/**
	* ������.
	*/
	void Start()override;
	
	/**
	* ���.
	*/
	void Release()override
	{
		for (auto& mapchip : MapChipList_) {
			DeleteGO(mapchip);
		}
	}

private:

	/** �}�b�v���b�v�̃��X�g. */
	vector<MapChip*> MapChipList_;

};