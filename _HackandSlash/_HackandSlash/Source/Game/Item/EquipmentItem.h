#pragma once

#include"ItemData\IItemData.h"

class EquipmentItem
{
public:

	EquipmentItem()
	{
	}

	EquipmentItem(IItemData* itemdata)
	{
		ItemData_ = itemdata;
	}

	~EquipmentItem()
	{
	}

	ItemTypeE GetItemType()
	{
		return ItemData_->GetItemType();
	}

	IItemData* GetItemData()
	{
		return ItemData_;
	}

	const char* GetIconFilePath()
	{
		return ItemData_->GetIconFilePath();
	}

	const char* GetName()
	{
		return ItemData_->GetName();
	}

	int GetParameter()
	{
		return ItemData_->GetParameter();
	}

private:

	IItemData* ItemData_;

};