#pragma once

class IWindow
{
public:

	//コンストラクタ
	IWindow();

	//デストラクタ
	virtual ~IWindow();

	//初期化
	virtual void Init();

	//更新
	virtual void Update();

	//描画
	virtual void Render();

	//解放
	virtual void Release();

protected:


};