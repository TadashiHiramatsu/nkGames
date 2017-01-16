/**
 * @file	Source\Game\Item\ItemResource.h
 *
 * Declares the item resource class.
 */
#pragma once

#include"Other.h"
#include"Weapon.h"
#include"Armor.h"

/**
 * An item resource.
 *
 * @author	HiramatsuTadashi
 * @date	2017/01/03
 */
class CItemResource
{
private:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 */
	CItemResource();

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 */
	~CItemResource();

public:

	/**
	 * Gets the instance.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 *
	 * @return	The instance.
	 */
	static CItemResource& GetInstance()
	{
		static CItemResource instance;
		return instance;
	}

	/**
	 * Loads this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 */
	void Load();

	/**
	 * Loads the file.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 */
	void LoadFile(char* _FilePath,IItem::ItemTypeE _Type);

	/**
	 * Gets an item.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/05
	 *
	 * @param	_Number	Number of.
	 *
	 * @return	Null if it fails, else the item.
	 */
	IItem* GetItem(int _Number)
	{
		auto& it = ItemList.find(_Number);
		if (it == ItemList.end())
		{
			NK_ASSERT(false, "_Number‚ÌƒAƒCƒeƒ€‚ª‘¶Ý‚µ‚Ü‚¹‚ñ");
		}
		return it->second;
	}

private:
	/** List of items. */
	map<int, IItem*> ItemList;
};

static CItemResource& ItemResource()
{
	return CItemResource::GetInstance();
}