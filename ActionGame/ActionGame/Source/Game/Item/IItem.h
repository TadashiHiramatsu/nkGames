#pragma once

class IItem
{
public:

	//アイテムの種類
	enum ItemType
	{
		Non, //設定なし
		UseItem, //消費アイテム
	};

	//アイテムパラメータ
	struct ItemParameter
	{
		ItemParameter()
		{
			ID = 0;
			Name = "名無しのアイテム";
			IconFilePath = "Icon/NonData.png";
		}
		int ID;
		char* Name;
		char* IconFilePath;
	};

public:

	//コンストラクタ
	IItem();

	//デストラクタ
	virtual ~IItem();

	//データのロード
	virtual void Load();

	//初期化
	virtual void Init();

	//更新
	virtual void Update(){}

	//描画
	virtual void Render();

	//解放
	virtual void Release();

	//クリックされた時の処理
	virtual void Click() = 0;

	ItemParameter GetParameter()
	{
		return IP;
	}

	void SetSTramsform(UITransform* _tf)
	{
		Image.SetTransform(_tf);
	}
		
protected:
	Image Image;

	ItemParameter IP;
};