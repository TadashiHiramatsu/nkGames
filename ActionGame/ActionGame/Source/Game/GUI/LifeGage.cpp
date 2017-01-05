#include"stdafx.h"
#include"LifeGage.h"

/**
 * Default constructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
LifeGage::LifeGage()
{
}

/**
 * Destructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
LifeGage::~LifeGage()
{
}

/**
 * Starts this object.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::Start()
{
	LifeFrameImage.Load("Image/LifeFrame.png");
	LifeFrameImage.SetTransform(&LifeFrameTransform);

	LifeImage.Load("Image/Life.png");
	LifeImage.SetTransform(&LifeTransform);

	//�e�q�֌W�ݒ�
	LifeTransform.Parent = &LifeFrameTransform;

	LifeFrameTransform.Width = LifeFrameTransform.Height = 150;
	LifeTransform.Width = LifeTransform.Height = 140;

	LifeFrameTransform.Anchor = RectTransform::AnchorPreset::BottomLeft;
	LifeFrameTransform.Pivot = D3DXVECTOR2(0, 0);

	LifeTransform.Anchor = RectTransform::AnchorPreset::BottomCenter;
	LifeTransform.Pivot = D3DXVECTOR2(0.5, 0);
	LifeTransform.Position.y = 5;

	MaxLife = &player->GetPlayerParameter().MaxHp;
	NowLife = &player->GetPlayerParameter().NowHp;

	Life.Create(20, 15);
}

/**
 * Updates this object.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::Update()
{
	LifeImage.uvRect.y = 1.0f - (float)*NowLife / (float)*MaxLife;
	LifeTransform.Height = (float)*NowLife / (float)*MaxLife * 140;

	LifeFrameTransform.Update();
	LifeTransform.Update();
}

/**
 * Renders this object.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::Render()
{
	LifeFrameImage.Render();
	LifeImage.Render();

	char Now[10];
	sprintf_s(Now, "%d", *NowLife);
	char Max[10];
	sprintf_s(Max, "%d", *MaxLife);

	char str[30] = { 0 };
	strcat_s(str, "Life:");
	strcat_s(str, Now);
	strcat_s(str, "/");
	strcat_s(str, Max);

	Life.Render(str,D3DXVECTOR2(10,500));
}