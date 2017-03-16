/**
 * @file	Source\Game\Item\IItem.h
 *
 * Declares the IItem interface.
 */
#pragma once

#include"ItemType.h"

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

	static const int TypeID = 1000;

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

	/**
	* 各種パラメータを取得する.
	*/
	virtual int GetParameter()
	{
		return -1;
	}

	/**
	* 最低レベルを取得.
	*/
	int GetMinLevel()
	{
		return MinLevel_;
	}

	/**
	* 最高レベルを取得.
	*/
	int GetMaxLevel()
	{
		return MaxLevel_;
	}

	/**
	* ドロップ率を取得.
	*/
	int GetProbability()
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
	int ID_ = 0;
	/** アイテムの名称。ゲーム内で表示するもの. */
	char Name_[64];
	/** アイコンのファイルパス . */
	char IconFilePath_[64];
	/** アイテムタイプ. */
	ItemTypeE Type_;

	/** 最低レベル. */
	int MinLevel_ = 0;
	/** 最高レベル. */
	int MaxLevel_ = 100;
	/** ドロップ確率. */
	int Probability_ = 100;

};