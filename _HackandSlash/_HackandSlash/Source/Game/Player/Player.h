/**
 * @file Source\Game\Player\Player.h
 *
 * プレイヤークラスの定義.
 */
#pragma once

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

#include"PlayerEquipment.h"

#include"../../Common/SaveData/SaveData.h"

/**
 * プレイヤークラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class Player : public IGameObject
{
public:

	/**
	 * プレイヤーパラメータの構造体.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct PlayerParameterS
	{
	public:

		/**
		* 読み込み.
		*/
		void Continue()
		{
			if (SaveData().IsContinue())
			{
				picojson::object player = SaveData().GetDataObject("Player");
				Level_ = player["Level"].get<double>();
				Experience_ = player["Experience"].get<double>();
				NextLevelExperience_ = player["NextLevelExperience"].get<double>();
				Attack_ = player["Attack"].get<double>();
				MaxHp_ = player["MaxHp"].get<double>();
				NowHp_ = player["NowHp"].get<double>();
			}
		}

		/**
		* 書き込み.
		*/
		void Save()
		{
			picojson::object player;

			player["Level"] = (picojson::value)(double)Level_;
			player["Experience"] = (picojson::value)(double)Experience_;
			player["NextLevelExperience"] = (picojson::value)(double)NextLevelExperience_;
			player["Attack"] = (picojson::value)(double)Attack_;
			player["MaxHp"] = (picojson::value)(double)MaxHp_;
			player["NowHp"] = (picojson::value)(double)NowHp_;

			SaveData().SetDataObject("Player", player);
		}

	public:

		/** レベル. */
		int Level_ = 1;
		/** 現在の経験値. */
		int Experience_ = 0;
		/** 次のレベルへの経験値. */
		int NextLevelExperience_ = 10;
		/** 攻撃力. */
		int	Attack_ = 10;
		/** 体力. */
		int MaxHp_ = 100;
		/** 体力. */
		int NowHp_ = 100;
		/** 無敵時間. */
		float InvincibleTime_ = 1.0f;

	};

	/** アニメーションコードの列挙. */
	enum class AnimationCodeE
	{
		Invalid = -1,				//!< 無効
		Idol = 0,					//!< 待機
		Walk,						//!< 歩き
		Run,						//!< 走り
		Attack_Start,				//!< 攻撃アニメーションコード開始.
		Attack_01 = Attack_Start,	//!< 攻撃01
		Attack_08,					//!< 攻撃08
		Attack_End = Attack_08,		//!< 攻撃アニメーションコード終了.
		Death_01,					//!< 死亡
		AnimationNum,				//!< アニメーションの数
	};


	/** ステートコードの列挙. */
	enum class StateCodeE
	{
		Invalid = -1,	//!< 無効
		Waiting = 0,	//!< 待機
		Walk,			//!< 歩き
		Run,			//!< 走り
		Attack,			//!< 攻撃
		Damage,			//!< やられ
		Death,			//!< 死亡
	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Player()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~Player()
	{
		Release();
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Update()override;

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Render()override;

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Release()override;

	/**
	* セーブ.
	*/
	void Save()override;

	/**
	 * ダメージ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Damage();

	/**
	 * レベルアップ処理.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void ParameterUpdate();

	/**
	 * 経験値加算.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param add The add.
	 */
	void AddExperience(int add)
	{
		Parameter_.Experience_ += add;
	}

	/**
	 * プレイヤーパラメータの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @return The player parameter.
	 */
	PlayerParameterS& GetParameter()
	{
		return Parameter_;
	}

	/**
	 * ポジションの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @return The position.
	 */
	const Vector3& GetPosition() const
	{
		return Transform_.Position_;
	}

	/**
	* 死んでいるかを返す.
	*/
	bool GetDeathFlag() const
	{
		return (State_ == StateCodeE::Death);
	}

	/**
	* 装備中のアイテムを取得
	*
	* @param type	アイテムタイプ.
	*
	* @return アイテム.
	*/
	EquipmentItem* GetEquipmentItem(ItemTypeE type)
	{
		return PlayerEquipment_.GetEquipmentItem(type);
	}

	/**
	* 装備するアイテムを設定.
	*
	* @param item	アイテム.
	*/
	void SetEquipmentItem(EquipmentItem* item)
	{
		PlayerEquipment_.SetEquipmentItem(item);
	}

	/**
	* アイテムが設定されているかのフラグを返します.
	*
	* @param type	アイテムタイプ.
	*
	* @return true or false.
	*/
	bool GetIsItemSet(ItemTypeE type) const
	{
		return PlayerEquipment_.GetIsItemSet(type);
	}

private:

	/**
	 * ステート更新関数.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param nextState State of the next.
	 */
	void ChangeState(StateCodeE nextState)
	{
		State_ = nextState;
	}

	/**
	 * アニメーション管理関数.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void AnimationControl();

	/**
	 * アニメーション切り替え関数.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param animCode		  The animation code.
	 * @param interpolateTime The interpolate time.
	 */
	void PlayAnimation(AnimationCodeE animCode, float interpolateTime);

	/**
	* リスポーン関数.
	*/
	void Respawn()
	{
		//待機状態に変化.
		ChangeState(StateCodeE::Waiting);
		PlayAnimation(AnimationCodeE::Idol, 0.0f);

		//現在の経験値の3分の1をロスト.
		float param  = Parameter_.Experience_ / 3;
		Parameter_.Experience_ -= param;

		//位置をリスポーン位置に変更.
		Transform_.Position_ = RespawnPosition_;

		//体力を1に設定.
		Parameter_.NowHp_ = 1;

		//インターバルのローカルタイムを初期化.
		InvincibleLT = 0.0f;
	}

private:

	/** モデルレンダー. */
	ModelRender ModelRender_;
	/** アニメーション. */
	Animation Animation_;
	/** 法線マップ. */
	Texture Normal_;
	/** スペキュラマップ. */
	Texture Specular_;

	/** 状態. */
	StateCodeE State_;

	/** The radius. */
	float Radius_ = 0.0f;
	/** The height. */
	float Height_ = 0.0f;
	/** キャラクターコントローラ. */
	CharacterController CharacterController_;

	/** アニメーションイベント. */
	AnimationEventController AnimationEvent_;

	/** プレイヤーのパラメータ. */
	PlayerParameterS Parameter_;

	/** ライフ回復時間用ローカルタイム. */
	float RecoveryLT_ = 0.0f;

	/** 無敵時間用ローカルタイム. */
	float InvincibleLT = 0.0f;

	/** コリジョンオブジェクト. */
	unique_ptr<btCollisionObject> CollisionObject_;
	/** 球体形状コライダー. */
	unique_ptr<SphereCollider> SphereShape_;

	/** 装備情報. */
	PlayerEquipment PlayerEquipment_;

	/** 再生のリクエストを出している攻撃モーション番号. */
	AnimationCodeE ReqAttackAnimCode_;
	/** 次の攻撃モーション番号. */
	AnimationCodeE NextAttackAnimCode_;

	/** リスポーン位置. */
	Vector3 RespawnPosition_;

};