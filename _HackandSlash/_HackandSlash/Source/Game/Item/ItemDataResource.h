/**
 * @file	Source\Game\Item\CItemDataResource.h
 *
 * Declares the item resource class.
 */
#pragma once

#include"ItemData\WeaponItemData.h"
#include"ItemData/ArmorItemData.h"

/**
 * アイテムデータのリソース群.
 *
 * @author	HiramatsuTadashi
 * @date	2017/01/03
 */
class CItemDataResource
{
public:

	/** アイテムデータ読み込みコード. */
	enum ItemDataReadCodeE
	{
		ItemID = 0,		//!< アイテムID.
		ItemName,		//!< アイテム名.
		FileName,		//!< ファイル名.
		ItemType,		//!< アイテムタイプ.
		MinLevel,		//!< 最低レベル.
		MaxLevel,		//!< 最高レベル.
		Probability,	//!< ドロップ率.
		Parameter,		//!< 各種パラメータ.
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
	 * 読み込み.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/03
	 */
	void Load();

	/**
	 * アイテムデータの取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/05
	 *
	 * @param	id	アイテムID.
	 *
	 * @return	Null if it fails, else the item.
	 */
	IItemData* GetItemData(int id)
	{
		auto& it = ItemList.find(id);
		if (it == ItemList.end())
		{
			NK_ASSERT(false, "idのアイテムが存在しません");
		}
		return it->second;
	}

	/**
	* アイテムリストの取得.
	*/
	const map<int, IItemData*>& GetItemMap() const
	{
		return ItemList;
	}

private:

	/**
	* ファイルの読み込み.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/03
	*/
	void LoadFile(char* filePath);

private:

	/** アイテムリスト. */
	map<int, IItemData*> ItemList;

};

static CItemDataResource& ItemDataResource()
{
	return CItemDataResource::GetInstance();
}