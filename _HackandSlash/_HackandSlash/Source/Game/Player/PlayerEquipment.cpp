#include"stdafx.h"
#include"PlayerEquipment.h"

/**
* �R���X�g���N�^.
*/
PlayerEquipment::PlayerEquipment()
{
	for (int i = 0; i < ItemTypeE::TypeNum; i++)
	{
		EquipmentItem_[i] = nullptr;
	}
}
