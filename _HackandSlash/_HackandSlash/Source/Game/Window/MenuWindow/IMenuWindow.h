#pragma once

#include"../../Player/Player.h"

class IMenuWindow
{
public:

	//初期化
	virtual void Start(RectTransform* rt, float namepos) = 0;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Render() = 0;

	void NameStart(RectTransform* parent, const char* filepath, float pos);

	//表示名の更新
	void NameUpdate()
	{
		NameTransform_.Update();
	}

	//表示名の描画
	void NameRender()
	{
		NameImage_.Render();
	}

	RectTransform& GetNameTransform()
	{
		return NameTransform_;
	}

	virtual void Close() 
	{
	}

	void SetPlayer(Player* player)
	{
		Player_ = player;
	}

protected:

	Image NameImage_;
	RectTransform NameTransform_;

	Player* Player_;

};
