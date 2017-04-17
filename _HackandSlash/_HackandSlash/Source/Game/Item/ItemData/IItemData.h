/**
 * アイテムの基底クラスの定義.
 */
#pragma once

#include"ItemType.h"

/**
 * アイテムの基底クラス.
 * アイテムをリソースクラスで扱うため.
 * IDで識別する.
 */
class IItemData
{
public:

	static const int TypeID = 1000;

public:

	/**
	* コンストラクタ.
	*/
	IItemData()
	{
	}

	/**
	 * コンストラクタ.
	 *
	 * @param	id			 	アイテムID.
	 * @param	itemname		アイテム名.
	 * @param	iconfilename	アイコンファイル名.
	 * @param	type		 	アイテムタイプ.
	 * @param	minlevel	 	最低レベル.
	 * @param	maxlevel	 	最高レベル.
	 * @param	probability	 	ドロップ率.
	 */
	IItemData(
		int id,
		const string& itemname,
		const string& iconfilename,
		ItemTypeE type,
		int minlevel,
		int maxlevel,
		int probability);

	/**
	 * デストラクタ.
	 */
	virtual ~IItemData() 
	{
	}

	/**
	 * IDを取得.
	 *
	 * @return The identifier.
	 */
	int GetID() const
	{
		return ItemID_;
	}

	/**
	* アイテム名の取得.
	*
	* @return Null if it fails, else the name.
	*/
	const string& GetName() const
	{
		return Name_;
	}

	/**
	 * アイコンファイルパスの取得.
	 *
	 * @return Null if it fails, else the icon file path.
	 */
	const string& GetIconFilePath() const
	{
		return IconFilePath_;
	}

	/**
	 * アイテムタイプの取得.
	 *
	 * @return The item type.
	 */
	ItemTypeE GetItemType() const
	{
		return Type_;
	}

	/**
	* 各種パラメータを取得する.
	*/
	virtual int GetParameter() const
	{
		return -1;
	}

	/**
	* 最低レベルを取得.
	*/
	int GetMinLevel() const
	{
		return MinLevel_;
	}

	/**
	* 最高レベルを取得.
	*/
	int GetMaxLevel() const
	{
		return MaxLevel_;
	}

	/**
	* ドロップ率を取得.
	*/
	int GetProbability() const
	{
		return Probability_;
	}

protected:

	/**   
	* アイテムを識別するためのコード. 
	* 例:1001 
	* 上1桁:アイテムタイプ
	* 下3桁:個別ID
	*/
	int ItemID_ = 0;
	/** アイテムの名称。ゲーム内で表示するもの. */
	string Name_ = "";
	/** アイコンのファイルパス . */
	string IconFilePath_ = "";
	/** アイテムタイプ. */
	ItemTypeE Type_ = ItemTypeE::Weapon;

	/** 最低レベル. */
	int MinLevel_ = 0;
	/** 最高レベル. */
	int MaxLevel_ = 100;
	/** ドロップ確率. */
	int Probability_ = 100;
};