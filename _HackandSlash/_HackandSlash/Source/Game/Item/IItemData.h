/**
 * @file	Source\Game\Item\IItem.h
 *
 * Declares the IItem interface.
 */
#pragma once

/**
 * アイテムの基底クラス 
 * アイテムをリソースクラスで扱うため 
 * IDで識別する.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class IItemData
{
public:

	static const int TypeID = 10000;
	static const int SubTypeID = 1000;

	/** レアリティ。ただそれだけ. */
	//enum RarityCodeE
	//{
	//	Common = 1,		//!< コモン。どこでも手に入る.
	//	Magic,			//!< マジック.
	//	Rare,			//!< レア.
	//	Unique,			//!< ユニーク.
	//};

	/** アイテムのタイプ. */
	/** アイテムIDの上一桁と一致. */
	enum ItemTypeE
	{
		Sword = 1,	//!< 剣
		Shield,		//!< 盾
		Armor,		//!< 防具
		Accessory,  //!< アクセサリ
	};

public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	IItemData()
	{
	}


	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	virtual ~IItemData() 
	{
	}

	/**
	 * IDを取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @return The identifier.
	 */
	int GetID()
	{
		return ID_;
	}

	/**
	* アイテム名の取得.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/16
	*
	* @return Null if it fails, else the name.
	*/
	const char* GetName()
	{
		return Name_;
	}

	/**
	 * アイコンファイルパスの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @return Null if it fails, else the icon file path.
	 */
	const char* GetIconFilePath()
	{
		return IconFilePath_;
	}

	/**
	 * アイテムタイプの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @return The item type.
	 */
	ItemTypeE GetItemType()
	{
		return Type_;
	}

protected:

	/**   
	* アイテムを識別するためのコード. 
	* 例:00000 
	* 上一桁:アイテムタイプ
	* 二桁目:サブタイプ
	* 下三桁:個別ID
	*/
	int ID_ = 0;
	/** アイテムの名称。ゲーム内で表示するもの. */
	char Name_[64];
	/** アイコンのファイルパス . */
	char IconFilePath_[64];
	/** アイテムタイプ. */
	ItemTypeE Type_;

};