#pragma once

class CCore : public CParts
{
public:
	//コンストラクタ
	CCore();

	//デストラクタ
	~CCore();

	//初期化
	void Init()override;

	//更新
	void Update()override;

private:

};