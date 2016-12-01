#pragma once

//ウィンドウの基底クラス
class IWindow
{
public:

	//コンストラクタ
	IWindow();
	//デストラクタ
	virtual ~IWindow();

	//初期化
	virtual void Init() {}

	//更新
	virtual void Update() {}

	//描画
	virtual void Render() {}

protected:

};