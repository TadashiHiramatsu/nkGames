/**
 * @file	Source\Game\Item\CItemDataResource.h
 *
 * Declares the item resource class.
 */
#pragma once

#include"SwordItemData.h"
#include"ArmorItemData.h"

/**
 * An item resource.
 *
 * @author	HiramatsuTadashi
 * @date	2017/01/03
 */
class CItemDataResource
{
private:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 */
	CItemDataResource()
	{
	}

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 */
	~CItemDataResource()
	{
	}

public:

	/**
	 * Gets the instance.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 *
	 * @return	The instance.
	 */
	static CItemDataResource& GetInstance()
	{
		static CItemDataResource instance;
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
	void LoadFile(char* _FilePath,IItemData::ItemTypeE _Type);

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
	IItemData* GetItem(int _Number)
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
	map<int, IItemData*> ItemList;
};

static CItemDataResource& ItemDataResource()
{
	return CItemDataResource::GetInstance();
}