/**
 * @file Source\Game\Monster\MonsterHabitat.cpp
 *
 * モンスターの住処クラスの実装.
 */
#include"stdafx.h"
#include"MonsterHabitat.h"

#include"Monster_01.h"

/**
 * コンストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
MonsterHabitat::MonsterHabitat()
{
}

/**
 * デストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
MonsterHabitat::~MonsterHabitat()
{
}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void MonsterHabitat::Start()
{
	for (int i = 0; i < Parameter_.InitMonsterNum_; i++)
	{
		Appearance();
	}
}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void MonsterHabitat::Update()
{
	if (MonsterList_.size() <= Parameter_.MonsterMax_)
	{
		//モンスターの出現数が最大に足しいていないので
		if (Parameter_.AppearanceTime_ <= AppearanceLT_)
		{
			//出現時間を経過しているので出現
			Appearance();
		}
		
		//出現時間のローカルタイムを加算
		AppearanceLT_ += Time().DeltaTime();
	
	}

	//モンスターリストのイテレータを取得
	auto it = MonsterList_.begin();

	while (it != MonsterList_.end())
	{

		if (!(*it)->GetActive())
		{
			//モンスターを削除
			delete (*it);

			//モンスターをリストから削除
			it = MonsterList_.erase(it);

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
void MonsterHabitat::Render()
{
	for (auto it : MonsterList_)
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
void MonsterHabitat::Appearance()
{
	//モンスターを作成
	Monster_01* m = new Monster_01;

	//出現位置を計算
	D3DXVECTOR3 pos = D3DXVECTOR3(Random().GetRandDouble0() * Parameter_.Distance_, 0, Random().GetRandDouble0() * Parameter_.Distance_);
	pos += Parameter_.Position_;
	//出現位置を設定
	m->SetPosition(pos);
	//モンスターにプレイヤーのポインタを設定
	m->SetPlayer(Player_);
	//モンスターの初期化
	m->Start();

	//リストにモンスターを登録
	MonsterList_.push_back(m);

	//出現時間のローカルタイムを初期化
	AppearanceLT_ = 0;

}