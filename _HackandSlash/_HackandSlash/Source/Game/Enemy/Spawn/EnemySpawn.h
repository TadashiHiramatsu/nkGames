/**
 * @file Source\Game\Monster\EnemySpawn.h
 *
 * 敵を生み出す機構クラスの定義.
 */
#pragma once

#include"../IEnemy.h"

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
	 * エネミースポナークラスのパラメータ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	struct ESParameterS
	{
	public:

		/** 中心地. */
		D3DXVECTOR3 Position_ = D3DXVECTOR3(0, 0, 0);
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
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

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

private:

	/** モンスターハンターポータブルじゃないよ. */
	ESParameterS Parameter_;

	/** 出現したモンスターを登録する. */
	vector<IEnemy*> EnemyList_;
	
	/** 出現時間のローカルタイム. */
	float SpawnLT_ = 0.0f;

	/** プレイヤーのポインタ. */
	Player* Player_;

};