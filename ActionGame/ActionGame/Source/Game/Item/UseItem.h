#pragma once

#include"IItem.h"

//使用アイテム
class UseItem : public IItem
{
public:

	//コンストラクタ
	UseItem();

	//デストラクタ
	~UseItem();

	//データのロード
	void Load()override;

	//初期化
	void Init()override;

	//更新
	 void Update()override;

	//描画
	 void Render()override;

	//解放
	 void Release()override;

	//クリックされた時の処理
	 void Click()override;

private:

};