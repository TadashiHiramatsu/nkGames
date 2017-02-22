#pragma once

#include"MapChip.h"

/**
* マップ読み取りクラス.
*/
class Map : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	Map()
	{
	}

	/**
	* デストラクタ.
	*/
	~Map()
	{
	}

	/**
	* 初期化.
	*/
	void Start()override;
	
	/**
	* 解放.
	*/
	void Release()override
	{
		for (auto& mapchip : MapChipList_) {
			DeleteGO(mapchip);
		}
	}

private:

	/** マップリップのリスト. */
	vector<MapChip*> MapChipList_;

};