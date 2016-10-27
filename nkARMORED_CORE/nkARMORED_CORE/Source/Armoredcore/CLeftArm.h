#pragma once

class CLeftArm : public CParts
{
public:
	//コンストラクタ
	CLeftArm();

	//デストラクタ
	~CLeftArm();

	void Update()override;

private:
	D3DXMATRIX rot;
};