/**
 * @file Source\Game\Monster\EnemySpawn.h
 *
 * 敵を生み出す機構クラスの定義.
 */
#pragma once

#include"../IEnemy.h"

 /**
 * エネミースポナークラスの読み込みデータ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct EnemySpawnInfoS
{
public:

	/** 中心地. */
	Vector3 Position_ = Vector3::Up;
	/** 距離. */
	float Distance_ = 0;
	/** 出現最大数. */
	int EnemyMax_ = 10;
	/** 出現間隔. */
	float SpawnTime_ = 1;
	/** レベル. */
	int EnemyLevel_ = 1;
	/** 敵の種類. */
	int EnemyID_ = 0;

};

/**
 * エネミースポナークラス.
 * 中心地から敵は出現する.
 * 今後出現ポイントに変化する可能性あり
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class EnemySpawn : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	EnemySpawn()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~EnemySpawn()
	{
	}

	/**
	 * 初期化.
	 * オーバーライドしていない.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start(EnemySpawnInfoS info);

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update()override;

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Render()override;

	/**
	 * モンスター出現関数.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Appearance();

	/**
	 * プレイヤーのポインタを設定.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param [in,out] p If non-null, the Player to process.
	 */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

	/**
	* 更新を行うかどうかの更新.
	*/
	float ToPlayerUpdate()
	{
		Vector3 ToPlayer;
		ToPlayer.Sub(Player_->Transform_.Position_, Transform_.Position_);
		ToPlayerLength_ = ToPlayer.Length();
		return ToPlayerLength_;
	}

private:

	/** 距離. */
	float Distance_ = 0;
	/** 出現最大数. */
	int EnemyMax_ = 10;
	/** レベル. */
	int EnemyLevel_ = 1;
	/** 敵の種類. */
	int EnemyID_ = 0;

	/** 出現したモンスターを登録する. */
	vector<IEnemy*> EnemyList_;
	
	/** 出現間隔. */
	float SpawnTime_ = 1;
	/** 出現時間のローカルタイム. */
	float SpawnLT_ = 0.0f;

	/** プレイヤーのポインタ. */
	Player* Player_;

	/** プレイヤーとの距離. */
	float ToPlayerLength_ = 0;

};