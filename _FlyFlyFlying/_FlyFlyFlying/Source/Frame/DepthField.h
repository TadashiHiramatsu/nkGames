#pragma once
#include"RenderTarget.h"
#include"C2DObject.h"
#include"Input.h"
using namespace Frame;

class DepthField
{
public:
	DepthField();
	~DepthField();
	void Create();
	void Render();
	void UpdateWeight(float);
	void Up()
	{
		(*GetKeyDevice()).GetDeviceState(
			sizeof(diks),	// パラメータ バッファサイズ
			&diks);
		if (KEYDOWN(diks, DIK_W))
		{
			Near += 0.01;
		}
		if (KEYDOWN(diks, DIK_S))
		{
			Near -= 0.01;
		}
		if (KEYDOWN(diks, DIK_A))
		{
			Far += 0.01;
		}
		if (KEYDOWN(diks, DIK_D))
		{
			Far -= 0.01;
		}
	}
private:
	static const int NUM_WEIGHTS = 8;
	ID3DXEffect* m_pEffect;
	CRenderTarget m_downSamplingRenderTarget[4];
	float m_weights[NUM_WEIGHTS];
	BYTE diks[256];

	float Near;
	float Far;

	C2DObject fullscreen;
};