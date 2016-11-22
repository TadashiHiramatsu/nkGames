#pragma once

#include"AnimationEventMacro.h"

const int ANIMATION_EVENT_MAX = 32;

//アニメーションイベントの種類
enum EAnimationEventType
{
	eAnimationEventType_EmitDamageToEnemyCollision, //敵に対してダメージを与えるコリジョン
	eAnimationEventType_EmitDamageToPlayerCollision, //プレイヤーにダメージを与えるコリジョン
	eAnimationEventType_Invalid = 0xffffffff,
};

//アニメーションイベント
struct AnimationEvent
{
public:
	AnimationEvent() {}
	AnimationEvent(
		EAnimationEventType type,
		float time,
		float fArg0, float fArg1, float fArg2, float fArg3,
		int iArg0, int iArg1, int iArg2, int iArg3,
		const char* strArg0, const char* strArg1, const char* strArg2, const char* strArg3,
		D3DXVECTOR3 vArg0, D3DXVECTOR3 vArg1, D3DXVECTOR3 vArg2, D3DXVECTOR3 vArg3)
	{
		this->eventType = type;
		this->time = time;
		fArg[0] = fArg0;
		fArg[1] = fArg1;
		fArg[2] = fArg2;
		fArg[3] = fArg3;

		iArg[0] = iArg0;
		iArg[1] = iArg1;
		iArg[2] = iArg2;
		iArg[3] = iArg3;

		strArg[0] = strArg0;
		strArg[1] = strArg1;
		strArg[2] = strArg2;
		strArg[3] = strArg3;

		vArg[0] = vArg0;
		vArg[1] = vArg1;
		vArg[2] = vArg2;
		vArg[3] = vArg3;
	}

public:
	EAnimationEventType eventType; //イベントのタイプ
	float time; //イベントが発生する時間。該当するアニメーションが再生されて経過した時間。
	float fArg[4]; //浮動小数点型の引数
	int iArg[4]; //整数型の引数
	const char* strArg[4]; //文字列の引数
	D3DXVECTOR3 vArg[4]; //ベクトル型の引数
};

//アニメーショングループ
struct AnimationEventGroup
{
	AnimationEvent event[ANIMATION_EVENT_MAX];
};

//アニメーションイベントコントローラ
class AnimationEventController
{
public:
	//コンストラクタ
	AnimationEventController();

	//デストラクタ
	~AnimationEventController();
	
	//初期化
	void Init(CModelRender* _skinModel, CAnimation* _anim, AnimationEventGroup* _eventGroupTbl, int _tblSize);

	//更新
	void Update();

private:

	//アニメーションイベントの発生
	void InvokeAnimationEvent(const AnimationEvent& _event);

private:
	struct AnimationEventGroupEx
	{
		AnimationEventGroup eventGroup;
		bool invokeFlags[ANIMATION_EVENT_MAX]; //イベントの発生フラグ
	};
	//1フレーム前のアニメーション番号
	int animNoLastFrame = -1;
	//アニメーション
	CAnimation* animation = nullptr;
	//イベントテーブル
	vector<AnimationEventGroupEx> eventGroupTbl;
	//スキンモデル
	CModelRender* skinModel = nullptr;
	//1フレーム前のアニメーションタイム
	float lastFrameAnimTime = 0.0f;
	//初期化できたかどうかのフラグ
	bool isInited = false;
};