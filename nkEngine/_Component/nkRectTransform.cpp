#include"nkEngine/nkstdafx.h"
#include"nkRectTransform.h"

namespace
{
	static const D3DXVECTOR3 AnchorOffset[] =
	{
		{ D3DXVECTOR3(-1, 1, 0) },
		{ D3DXVECTOR3(0	, 1, 0) },
		{ D3DXVECTOR3(1	, 1, 0) },
		{ D3DXVECTOR3(-1, 0, 0) },
		{ D3DXVECTOR3(0	, 0 ,0) },
		{ D3DXVECTOR3(1	, 0, 0) },
		{ D3DXVECTOR3(-1,-1, 0) },
		{ D3DXVECTOR3(0	,-1, 0) },
		{ D3DXVECTOR3(1	,-1, 0) }
	};
}

namespace nkEngine
{
	RectTransform::RectTransform() :
		Parent(nullptr),
		Anchor(AnchorPreset::MiddleCenter),
		Position(D3DXVECTOR2(0, 0)),
		Width(100),
		Height(100),
		Pivot(D3DXVECTOR2(0.5, 0.5)),
		Rotation(D3DXQUATERNION(0, 0, 0, 1)),
		Scale(D3DXVECTOR2(1, 1))
	{
		int screenW = Engine().GetScreenW();
		int screenH = Engine().GetScreenH();
		D3DXMatrixIdentity(&ProjectionMatrix);
		ProjectionMatrix._11 = 2.0f / screenW;
		ProjectionMatrix._22 = 2.0f / screenH;
	}

	RectTransform::~RectTransform()
	{

	}

	void RectTransform::Update()
	{
		D3DXMATRIX mScale;

		int screenW = Engine().GetScreenW() / 2;
		int screenH = Engine().GetScreenH() / 2;

		D3DXVECTOR3 trans;
		trans.x = Position.x;
		trans.y = Position.y;
		trans.z = 0;

		if (Parent)
		{
			//アンカー計算
			trans.x += AnchorOffset[Anchor].x * (Parent->Width /2);
			trans.y += AnchorOffset[Anchor].y * (Parent->Height / 2);
		}
		else
		{
			//アンカー計算
			trans.x += AnchorOffset[Anchor].x * screenW;
			trans.y += AnchorOffset[Anchor].y * screenH;
		}

		//ピボットの分のオフセットを計算。
		D3DXVECTOR3 pivotOffset;
		pivotOffset.x = (Width  * Scale.x) * (0.5f - Pivot.x);
		pivotOffset.y = (Height * Scale.y) * (0.5f - Pivot.y);
		pivotOffset.z = 0.0f;
		trans += pivotOffset;

		//移動行列作成
		D3DXMatrixTranslation(&TransMatrix, trans.x, trans.y, trans.z);

		//拡大
		D3DXVECTOR3 scale;
		scale.x = (Width * Scale.x);
		scale.y = (Height* Scale.y);
		scale.z = 1.0f;
		D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.x);
		D3DXMatrixScaling(&ScaleMatrix, Scale.x, Scale.y, 1.0f);

		D3DXMatrixRotationQuaternion(&RotationMatrix, &Rotation);

		WorldMatrix = mScale * RotationMatrix * TransMatrix;
		WorldSizeOffMatrix = ScaleMatrix * RotationMatrix * TransMatrix;

		if (Parent)
		{
			WorldMatrix *= Parent->WorldSizeOffMatrix;
			WorldSizeOffMatrix *= Parent->WorldSizeOffMatrix;
		}

		WorldProjMatrix = WorldMatrix * ProjectionMatrix;
	}
}