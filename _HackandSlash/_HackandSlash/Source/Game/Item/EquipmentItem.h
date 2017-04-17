/**
* 装備アイテムクラスの定義.
*/
#pragma once

#include"ItemData\IItemData.h"

/**
* 装備アイテムクラス.
*/
class EquipmentItem
{
public:

	/**
	* コンストラクタ.
	*/
	EquipmentItem()
	{
	}

	/**
	* コンストラクタ.
	*/
	EquipmentItem(IItemData* itemdata)
	{
		ItemData_ = itemdata;
	}

	/**
	* デストラクタ.
	*/
	~EquipmentItem()
	{
	}

	/**
	* アイテムタイプの取得.
	*/
	ItemTypeE GetItemType() const
	{
		return ItemData_->GetItemType();
	}

	/**
	* アイテムデータの取得.
	*/
	IItemData* GetItemData() const
	{
		return ItemData_;
	}

	/**
	* アイコンファイルパスの取得.
	*/
	const string& GetIconFilePath() const
	{
		return ItemData_->GetIconFilePath();
	}

	/**
	* アイテム名の取得.
	*/
	const string& GetName() const
	{
		return ItemData_->GetName();
	}

	/**
	* 特殊パラメータの取得.
	*/
	int GetParameter()
	{
		return ItemData_->GetParameter();
	}

	/**
	* アイテムIDの取得.
	*/
	int GetID() const
	{
		return ItemData_->GetID();
	}

private:

	/** アイテムデータ. */
	IItemData* ItemData_ = nullptr;

};