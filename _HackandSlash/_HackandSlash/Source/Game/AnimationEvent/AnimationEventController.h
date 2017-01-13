/**
 * @file Source\Game\AnimationEvent\AnimationEventController.h
 *
 * アニメーションイベントコントローラクラスの定義.
 */
#pragma once

#include"AnimationEventMacro.h"

/** アニメーションイベントの最大数. */
const int ANIMATION_EVENT_MAX = 32;

/** アニメーションイベントの種類. */
enum AnimationEventTypeE
{
	Invalid = -1,					//!< 無効
	EmitDamageToEnemyCollision,		//!< 敵に対してダメージを与えるコリジョン
	EmitDamageToPlayerCollision,	//!< プレイヤーにダメージを与えるコリジョン
};

/**
 * アニメーションイベント構造体.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct AnimationEventS
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	AnimationEventS()
	{
	}
	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param type    The type.
	 * @param time    The time.
	 * @param fArg0   The argument 0.
	 * @param fArg1   The first f argument.
	 * @param fArg2   The second f argument.
	 * @param fArg3   The third f argument.
	 * @param iArg0   Zero-based index of the argument 0.
	 * @param iArg1   Zero-based index of the argument 1.
	 * @param iArg2   Zero-based index of the argument 2.
	 * @param iArg3   Zero-based index of the argument 3.
	 * @param strArg0 The argument 0.
	 * @param strArg1 The first string argument.
	 * @param strArg2 The second string argument.
	 * @param strArg3 The third string argument.
	 * @param vArg0   The argument 0.
	 * @param vArg1   The first v argument.
	 * @param vArg2   The second v argument.
	 * @param vArg3   The third v argument.
	 */
	AnimationEventS(
		AnimationEventTypeE type,
		float time,
		float fArg0, float fArg1, float fArg2, float fArg3,
		int iArg0, int iArg1, int iArg2, int iArg3,
		const char* strArg0, const char* strArg1, const char* strArg2, const char* strArg3,
		D3DXVECTOR3 vArg0, D3DXVECTOR3 vArg1, D3DXVECTOR3 vArg2, D3DXVECTOR3 vArg3)
	{
		EventType_ = type;
		Time_ = time;
		fArg_[0] = fArg0;
		fArg_[1] = fArg1;
		fArg_[2] = fArg2;
		fArg_[3] = fArg3;

		iArg_[0] = iArg0;
		iArg_[1] = iArg1;
		iArg_[2] = iArg2;
		iArg_[3] = iArg3;

		strArg_[0] = strArg0;
		strArg_[1] = strArg1;
		strArg_[2] = strArg2;
		strArg_[3] = strArg3;

		vArg_[0] = vArg0;
		vArg_[1] = vArg1;
		vArg_[2] = vArg2;
		vArg_[3] = vArg3;
	}

public:

	/** イベントのタイプ. */
	AnimationEventTypeE EventType_;
	/** イベントが発生する時間。該当するアニメーションが再生されて経過した時間。. */
	float Time_;
	/** 浮動小数点型の引数. */
	float fArg_[4];
	/** 整数型の引数. */
	int iArg_[4];
	/** 文字列の引数. */
	const char* strArg_[4];
	/** ベクトル型の引数. */
	D3DXVECTOR3 vArg_[4];

};

/**
 * アニメーショングループ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct AnimationEventGroupS
{
public:

	/** The event [animation event max]. */
	AnimationEventS Event_[ANIMATION_EVENT_MAX];

};

/**
 * アニメーションイベントコントローラ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class AnimationEventController
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	AnimationEventController();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~AnimationEventController();

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param [in,out] model		 モデルレンダクラス.
	 * @param [in,out] anim			 アニメーションクラス.
	 * @param [in,out] eventGroupTbl イベントグループ.
	 * @param 		   tblSize		 Size of the table.
	 */
	void Init(ModelRender* model, Animation* anim, AnimationEventGroupS* eventGroupTbl, int tblSize);

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update();

private:

	/**
	 * アニメーションイベントの発生.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param event The event.
	 */
	void InvokeAnimationEvent(const AnimationEventS& event);

private:

	/**
	 * アニメーションイベントテーブル.
	 * イベントが発生したかのフラグも扱う.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	struct AnimationEventGroupTableS
	{

		/** アニメーションイベントグループ. */
		AnimationEventGroupS EventGroup_;
		/** イベントの発生フラグ. */
		bool isInvokes_[ANIMATION_EVENT_MAX];

	};
	/** イベントテーブル. */
	vector<AnimationEventGroupTableS> EventGroupTableList_;

	/** 1フレーム前のアニメーション番号. */
	int AnimNoLastFrame_ = -1;
	/** アニメーション. */
	Animation* Animation_ = nullptr;
	/** スキンモデル. */
	ModelRender* ModelRender_ = nullptr;
	/** 1フレーム前のアニメーションタイム. */
	float LastFrameAnimTime_ = 0.0f;
	/** 初期化できたかどうかのフラグ. */
	bool isInited_ = false;

};