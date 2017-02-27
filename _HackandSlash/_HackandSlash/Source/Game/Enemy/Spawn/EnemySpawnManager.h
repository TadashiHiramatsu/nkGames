/**
* エネミースポナー管理クラスの定義.
*/
#pragma once

#include"EnemySpawn.h"

/**
* エネミースポナー管理クラス.
*/
class EnemySpawnManager : public IGameObject
{
private:

	/** エネミースポナー読み込みコード. */
	enum ESReadCodeE
	{
		PositionX,	//!< 座標X.
		PositionY,	//!< 座標Y.
		PositionZ,	//!< 座標Z.
		Distance,	//!< 出現範囲.
		EnemyMax,	//!< 敵出現数.
		SpawnTime,	//!< 出現時間.
		EnemyLevel,	//!< 敵レベル.
		EnemyID,	//!< エネミーID.
	};

public:

	/**
	* コンストラクタ.
	*/
	EnemySpawnManager()
	{
	}
	
	/**
	* デストラクタ.
	*/
	~EnemySpawnManager()
	{
	}

	/**
	* 初期化.
	*/
	void Start()override;
	
	/**
	* プレイヤーのポインタを設定.
	*
	* @param [in]	p	プレイヤーのポインタ.
 	*/
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** エネミースポーンリスト. */
	list<EnemySpawn*> EnemySpawnList_;

	/** プレイヤーのポインタ. */
	Player* Player_;

};