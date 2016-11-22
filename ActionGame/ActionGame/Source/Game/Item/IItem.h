#pragma once

class IItem
{
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
	virtual void Update();

	//描画
	virtual void Render();

	//解放
	virtual void Release();

	int GetID()
	{
		return ID;
	}

	void SetSTramsform(SpriteTransform* _st)
	{
		Sprite.SetSTransform(_st);
	}

	//クリックされた時の処理
	virtual void Click();
		
protected:
	CSprite Sprite;

	int ID;
	char* Name;
};