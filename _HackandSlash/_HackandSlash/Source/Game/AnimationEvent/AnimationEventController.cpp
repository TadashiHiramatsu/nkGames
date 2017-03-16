/**
 * @file Source\Game\AnimationEvent\AnimationEventController.cpp
 *
 * アニメーションイベントコントローラクラスの定義.
 */
#include"stdafx.h"
#include"AnimationEventController.h"
#include"CollisionWorld.h"

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
void AnimationEventController::Init(ModelRender* model, Animation* anim, AnimationEventGroupS* eventGroupTbl, int tblSize)
{
	//イベントグループがないよ
	if (eventGroupTbl == NULL)
	{
		return;
	}

	ModelRender_ = model;
	Animation_ = anim;

	//イベントグループの初期化
	EventGroupTableList_.resize(tblSize);
	for (int i = 0; i < tblSize; i++)
	{
		EventGroupTableList_[i].EventGroup_ = &eventGroupTbl[i];
		memset(EventGroupTableList_[i].isInvokes_, 0, sizeof(EventGroupTableList_[i].isInvokes_));
	}

	//初期化できた
	isInited_ = true;

}

void AnimationEventController::Update()
{

	if (!isInited_)
	{
		//初期化できてない
		return;
	}

	//現在再生中のアニメーション番号を取得
	int currentAnimNo = Animation_->GetNowAnimationNo();

	//ローカルアニメーションタイムを取得
	float animTime = Animation_->GetLocalAnimationTime();

	//1フレームのアニメーションタイムが-1又は現在じゃない
	if (AnimNoLastFrame_ != -1 && AnimNoLastFrame_ != currentAnimNo)
	{
		//アニメーションが切り替わった
		//前のアニメーションのイベント発生フラグを初期化する
		memset(EventGroupTableList_[AnimNoLastFrame_].isInvokes_, 0, sizeof(EventGroupTableList_[AnimNoLastFrame_].isInvokes_));
	}
	else if (animTime < LastFrameAnimTime_)
	{
		//前のフレームよりもアニメーション時間が小さくなった(ループした)
		//残ってるイベントを全部発生させてから初期化
		
		//現在再生中のアニメーションのアニメーションイベントを取得
		AnimationEventGroupTableS& eventGroupTable = EventGroupTableList_[currentAnimNo];

		//イベントタイプが無効になるまで
		for (int i = 0; eventGroupTable.EventGroup_->Event_[i].EventType_ != AnimationEventTypeE::Invalid;i++)
		{
			//発生したことがなければ
			if (eventGroupTable.isInvokes_[i] == false)
			{
				InvokeAnimationEvent(eventGroupTable.EventGroup_->Event_[i]);
				//発生済みに変更
				eventGroupTable.isInvokes_[i] = true;
			}
		}

		//フラグをすべて初期化
		memset(EventGroupTableList_[AnimNoLastFrame_].isInvokes_, 0, sizeof(EventGroupTableList_[AnimNoLastFrame_].isInvokes_));
	}

	//1フレーム前のアニメーションタイムをコピー
	LastFrameAnimTime_ = animTime;

	//現在再生中のアニメーションのアニメーションイベントを取得
	AnimationEventGroupTableS& eventGroupTable = EventGroupTableList_[currentAnimNo];

	//イベントタイプが無効になるまで更新
	for (int i = 0;eventGroupTable.EventGroup_->Event_[i].EventType_ != AnimationEventTypeE::Invalid;i++)
	{
		//発生させたことがなければ
		if (eventGroupTable.isInvokes_[i] == false)
		{
			//まだイベントが発生していない
			if (eventGroupTable.EventGroup_->Event_[i].Time_ <= animTime)
			{
				//イベント発生する時間が経過した
				InvokeAnimationEvent(eventGroupTable.EventGroup_->Event_[i]);
				//発生済みに変更
				eventGroupTable.isInvokes_[i] = true;

			}

		}

	}

	//アニメーショントラック番号の更新
	AnimNoLastFrame_ = currentAnimNo;

}

/**
* アニメーションイベントの発生.
*
* @author HiramatsuTadashi
* @date 2017/01/11
*
* @param event The event.
*/
void AnimationEventController::InvokeAnimationEvent(const AnimationEventS& event)
{
	//タイプ事に違う処理を
	switch (event.EventType_)
	{
	case AnimationEventTypeE::EmitDamageToEnemyCollision:
		//敵にダメージを与えるコリジョン発生
	{
		//ボーンを取得 この動作重くね？
		Matrix* bone = ModelRender_->FindBoneWorldMatrix(event.strArg_[0]);

		//ボーンが存在していれば
		if (bone != nullptr)
		{
			//ポジションの移動を取得
			Vector3 pos = event.vArg_[0];

			//ポジションの移動分を計算
			pos.TransformCoord(*bone);

			//コリジョンワールドに登録
			g_CollisionWorld->Add(event.fArg_[1], pos, event.fArg_[0], event.iArg_[0], CollisionWorld::AttributeE::DamageToEnemy, event.iArg_[1]);
		
			bone = nullptr;
		}
	}
	break;

	case AnimationEventTypeE::EmitDamageToPlayerCollision:
		//プレイヤーにダメージを与えるコリジョン発生.
	{
		//ボーンを取得 この動作重くね？
		Matrix* bone = ModelRender_->FindBoneWorldMatrix(event.strArg_[0]);
		
		//ボーンが存在していれば
		if (bone != NULL)
		{

			//ポジションの移動分を取得
			Vector3 pos = event.vArg_[0];

			//ポジションの移動分を計算
			pos.TransformCoord(*bone);

			//コリジョンワールドに登録
			g_CollisionWorld->Add(event.fArg_[1], pos, event.fArg_[0], event.iArg_[0], CollisionWorld::AttributeE::DamageToPlayer, event.iArg_[1]);
		}
	}
	break;

	default:
		break;
	}

}