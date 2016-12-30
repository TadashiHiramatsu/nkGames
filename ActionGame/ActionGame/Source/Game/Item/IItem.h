#pragma once

//アイテムの基底クラス
//アイテムをリソースクラスで扱うため
//IDで識別する
class IItem
{
public:

	//レアリティ。ただそれだけ
	enum RarityCode
	{
		Common, //コモン。どこでも手に入る。
		Magic, //マジック
		Rare, //レア。
		Unique, //ユニーク
	};

public:

private:
	int ID; //アイテムを識別するためのコード
	char* Name; //アイテムの名称。ゲーム内で表示するもの
	RarityCode Rarity; //レアリティ。
};