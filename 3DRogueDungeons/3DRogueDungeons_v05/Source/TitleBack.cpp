#include "TitleBack.h"

CTitleBack::CTitleBack() { }
CTitleBack::~CTitleBack(){ }

void CTitleBack::Initialize()
{
	m_position = D3DXVECTOR2(0, 0);
	m_angle = 0;
	m_scale = D3DXVECTOR2(1, 1);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "Texture\\TitleBack.jpg";
	x = 0;
	C2DImage::Initialize();
	m_texCenter = D3DXVECTOR2(0, 0);
}

void CTitleBack::Update()
{
	this->SetupMatrices();
}