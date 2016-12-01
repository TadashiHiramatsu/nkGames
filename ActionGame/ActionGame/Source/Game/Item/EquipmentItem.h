#pragma once

#include"IItem.h"

//装備アイテム
class EquipmentItem : public IItem
{
public:

	enum EquipmentType
	{
		BUKI, //武器
		BOUGU, //防具
	};

public:

	//コンストラクタ
	EquipmentItem();

	//デストラクタ
	~EquipmentItem();

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