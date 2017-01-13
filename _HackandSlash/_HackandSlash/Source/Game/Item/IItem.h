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
class IItem
{
public:

	static const int TypeID = 10000;
	static const int SubTypeID = 1000;

	/** レアリティ。ただそれだけ. */
	enum RarityCode
	{
		Common = 1, //コモン。どこでも手に入る。
		Magic, //マジック
		Rare, //レア。
		Unique, //ユニーク
	};

	/** アイテムのタイプ. */
	/** アイテムIDの上一桁と一致. */
	enum ItemType
	{
		Weapon = 1, //武器
		Armor = 2, //防具
		Other = 3, //その他
	};

public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	IItem();


	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	virtual ~IItem();

protected:
	/** アイテムを識別するためのコード. */
	// 例:00000 
	// 上一桁:アイテムタイプ
	// 二桁目:サブタイプ
	// 下三桁:個別ID
	int ID;
	/** アイテムの名称。ゲーム内で表示するもの. */
	const char* Name;
	/** アイコンのファイルパス . */
	const char* IconFilePath;
	/** レアリティ. */
	RarityCode Rarity;
	/** アイテムタイプ. */
	ItemType Type;
};