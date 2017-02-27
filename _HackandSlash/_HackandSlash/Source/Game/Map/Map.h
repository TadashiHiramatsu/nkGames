#pragma once

#include"MapChip.h"

/**
* �}�b�v�ǂݎ��N���X.
*/
class Map : public IGameObject
{
private:

	/** �}�b�v�ǂݍ��݃R�[�h. */
	enum MapReadCodeE
	{
		ModelName,  //!< ���f����
		PositionX,	//!< �ʒuX
		PositionY,	//!< �ʒuY
		PositionZ,	//!< �ʒuZ
		RotationX,  //!< ��]X
		RotationY,  //!< ��]Y
		RotationZ,  //!< ��]Z
		RotationW,  //!< ��]W
		ScaleX,		//!< �g��X
		ScaleY,		//!< �g��Y
		ScaleZ,		//!< �g��Z
	};

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