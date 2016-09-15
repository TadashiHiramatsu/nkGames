#pragma once

class CACModelRender : public CModelRender
{
public:
	CACModelRender();
	~CACModelRender();
	
	//更新のオーバーライド
	void Update()override;
	
	//親行列の設定
	void SetParentMatrix(D3DXMATRIX* parent)
	{
		m_mParent = parent;
	}

private:
	D3DXMATRIX* m_mParent; //親のワールド行列
};