/**
 * @file Source\Game\Monster\IMonster.h
 *
 * モンスターの基底クラスの定義.
 */
#pragma once

#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\Player\Player.h"
#include"..\Item\DropItem.h"

//
class IMonster : public IGameObject
{
protected:
	enum StateCode
	{
		StateSpawn, //出現
		StateWaiting, //立ち止まり
		StateLoitering, //徘徊
		StateChase, //追いかけ
		StateAttack, //攻撃
		StateDamage, //ダメージ
		StateDead, //そして死
	};

public:
	IMonster();
	virtual ~IMonster();
	virtual void Start()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

	virtual void Damage(){}

	void SetPosition(D3DXVECTOR3& _pos)
	{
		transform.Position = _pos;
	}

protected:

	//Stateを変更する
	//param[in] 変更後のStateCode
	void ChangeState(StateCode _NextState)
	{
		State = _NextState;
	}

	//アニメーション管理
	virtual void AnimationControl() {}

	//プレイヤーへの方向ベクトルを計算
	D3DXVECTOR2& GetToPlayerDir()
	{
		D3DXVECTOR2 toP = D3DXVECTOR2(pPlayerPos->x,pPlayerPos->z) - D3DXVECTOR2(transform.Position.x, transform.Position.z);
		D3DXVec2Normalize(&toP, &toP);
		return toP;
	}

	//プレイヤーとの距離を計算
	//高さを考慮しない距離を返します
	float GetToPlayerDis()
	{
		D3DXVECTOR3 toP = *pPlayerPos - transform.Position;
		return D3DXVec2Length(&D3DXVECTOR2(toP.x, toP.z));
	}


	//目的地までの方向ベクトルを取得
	D3DXVECTOR2& GetToDestination()
	{
		D3DXVECTOR2 toD = Destination - D3DXVECTOR2(transform.Position.x, transform.Position.z);
		D3DXVec2Normalize(&toD, &toD);
		return toD;
	}

	//目的地までの距離を計算
	//高さを考慮しない距離を返します
	float GetToDestinationDis()
	{
		D3DXVECTOR2 toD = Destination - D3DXVECTOR2(transform.Position.x, transform.Position.z);
		return D3DXVec2Length(&toD);
	}



protected:
	CSkinModelDataHandle SkinModelData;
	CModelRender Model;
	CLight Light;
	CAnimation Animation;

	float Radius;
	float Height;

	int Hp;

	//スポーン位置
	//ここからの距離移動できる
	D3DXVECTOR3 DefaultPosition;
	float Distance; //距離
	D3DXVECTOR2 Destination; //目的地

	//プレイヤーを追いかける最大距離
	//見つける距離も兼用
	float toPlayerMaxDis; 

	D3DXVECTOR3* pPlayerPos;//プレイヤーのポジションのアドレス
	float PlayerAttackDis;

	float WaitingTime; //立ち止まる時間
	float LocalTime; //ローカルタイム

	StateCode State;
	CharacterController m_CharacterController;

	AnimationEventController animEvent;
};