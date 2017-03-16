/**
 * @file	Source\Game\Item\CItemDataResource.h
 *
 * Declares the item resource class.
 */
#pragma once

#include"ItemData\WeaponItemData.h"
#include"ItemData/ArmorItemData.h"

/**
 * An item resource.
 *
 * @author	HiramatsuTadashi
 * @date	2017/01/03
 */
class CItemDataResource
{
public:

	/** �A�C�e���f�[�^�ǂݍ��݃R�[�h. */
	enum ItemDataReadCodeE
	{
		ItemID = 0,		//!< �A�C�e��ID.
		ItemName,		//!< �A�C�e����.
		FileName,		//!< �t�@�C����.
		ItemType,		//!< �A�C�e���^�C�v.
		MinLevel,		//!< �Œ჌�x��.
		MaxLevel,		//!< �ō����x��.
		Probability,	//!< �h���b�v��.
		Parameter,		//!< �e��p�����[�^.
	};

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
	void LoadFile(char* _FilePath);

	/**
	 * Gets an item.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/05
	 *
	 * @param	id	�A�C�e��ID.
	 *
	 * @return	Null if it fails, else the item.
	 */
	IItemData* GetItem(int id)
	{
		auto& it = ItemList.find(id);
		if (it == ItemList.end())
		{
			NK_ASSERT(false, "id�̃A�C�e�������݂��܂���");
		}
		return it->second;
	}

	const map<int, IItemData*>& GetItemMap() const
	{
		return ItemList;
	}

private:

	/** List of items. */
	map<int, IItemData*> ItemList;

};

static CItemDataResource& ItemDataResource()
{
	return CItemDataResource::GetInstance();
}