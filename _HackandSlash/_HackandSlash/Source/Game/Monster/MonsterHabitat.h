/**
 * @file Source\Game\Monster\MonsterHabitat.h
 *
 * モンスターの住処クラスの定義.
 */
#pragma once

#include"IMonster.h"

/**
 * モンスターの住処.
 * 中心地からモンスターは出現する.
 * 今後出現ポイントに変化する可能性あり
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class MonsterHabitat : public IGameObject
{
public:

	/**
	 * MonsterHabitatクラスのパラメータ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	struct MHParameterS
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/11
		 */
		MHParameterS()
		{
			Position_ = D3DXVECTOR3(0, 1, 0);
			Distance_ = 10;
			MonsterID_ = 1;
			MonsterMax_ = 10;
			AppearanceTime_ = 5;
			InitMonsterNum_ = 5;
		}

	public:

		/** 中心地. */
		D3DXVECTOR3 Position_;
		/** 距離. */
		float Distance_;
		/** モンスターの種類. */
		int MonsterID_;
		/** 出現最大数. */
		int MonsterMax_;
		/** 出現間隔. */
		float AppearanceTime_;
		/** 初期化時のモンスターの数. */
		int InitMonsterNum_;
	
	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	MonsterHabitat();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~MonsterHabitat();

public:

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
	MHParameterS Parameter_;
	/** 出現したモンスターを登録する. */
	vector<IMonster*> MonsterList_;
	/** 出現時間のローカルタイム. */
	float AppearanceLT_ = 0.0f;

	/** プレイヤーのポインタ. */
	Player* Player_;

};