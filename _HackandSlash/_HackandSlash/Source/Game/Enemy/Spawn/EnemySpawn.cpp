/**
 * @file Source\Game\Monster\EnemySpawn.cpp
 *
 * 敵を生み出す機構クラスの実装.
 */
#include"stdafx.h"
#include"EnemySpawn.h"

#include"../Enemy_01.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Start()
{

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Update()
{
	if (EnemyList_.size() <= Parameter_.EnemyMax_)
	{
		//モンスターの出現数が最大に足しいていないので
		if (Parameter_.SpawnTime_ <= SpawnLT_)
		{
			//出現時間を経過しているので出現
			Appearance();
		}
		
		//出現時間のローカルタイムを加算
		SpawnLT_ += Time().DeltaTime();
	
	}

	//モンスターリストのイテレータを取得
	auto& it = EnemyList_.begin();

	while (it != EnemyList_.end())
	{

		if (!(*it)->GetActive())
		{
			//モンスターを削除
			delete (*it);

			//モンスターをリストから削除
			it = EnemyList_.erase(it);

		}

		//更新
		(*it)->Update();
	
		it++;
	}

}

/**
 * 描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Render()
{
	for (auto& it : EnemyList_)
	{
		it->Render();
	}
}

/**
 * モンスター出現関数.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Appearance()
{
	//モンスターを作成
	Enemy_01* enemy = new Enemy_01();

	//出現位置を計算
	D3DXVECTOR3 pos = D3DXVECTOR3((Random::value() - 0.5f) * Parameter_.Distance_, 0, (Random::value() - 0.5f) * Parameter_.Distance_);
	pos += Parameter_.Position_;
	
	//出現位置を設定
	enemy->SetPosition(pos);
	//モンスターにプレイヤーのポインタを設定
	enemy->SetPlayer(Player_);
	//モンスターの初期化
	enemy->Start();

	//リストにモンスターを登録
	EnemyList_.push_back(enemy);

	//出現時間のローカルタイムを初期化
	SpawnLT_ = 0;

}