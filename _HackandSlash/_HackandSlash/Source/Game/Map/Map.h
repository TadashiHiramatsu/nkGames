#pragma once

#include"MapChip.h"

/**
* マップ読み取りクラス.
*/
class Map : public IGameObject
{
private:

	/** マップ読み込みコード. */
	enum MapReadCodeE
	{
		ModelName,  //!< モデル名
		PositionX,	//!< 位置X
		PositionY,	//!< 位置Y
		PositionZ,	//!< 位置Z
		RotationX,  //!< 回転X
		RotationY,  //!< 回転Y
		RotationZ,  //!< 回転Z
		RotationW,  //!< 回転W
		ScaleX,		//!< 拡大X
		ScaleY,		//!< 拡大Y
		ScaleZ,		//!< 拡大Z
	};

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