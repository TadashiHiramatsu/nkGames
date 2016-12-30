#include"nkEngine/nkstdafx.h"
#include"nkRectTransform.h"

namespace
{
	static const D3DXVECTOR2 AnchorOffset[] =
	{
		{ D3DXVECTOR2(-1, 1) },
		{ D3DXVECTOR2(0	, 1) },
		{ D3DXVECTOR2(1	, 1) },
		{ D3DXVECTOR2(-1, 0) },
		{ D3DXVECTOR2(0	, 0) },
		{ D3DXVECTOR2(1	, 0) },
		{ D3DXVECTOR2(-1,-1) },
		{ D3DXVECTOR2(0	,-1) },
		{ D3DXVECTOR2(1	,-1) }
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

		int screenWCenter = Engine().GetScreenW() / 2;
		int screenHCenter = Engine().GetScreenH() / 2;

		D3DXVECTOR2 trans = Position;

		//アンカーを画面に設定
		D3DXVECTOR2 AnchorValue;
		AnchorValue.x = screenWCenter;
		AnchorValue.y = screenHCenter;

		if (Parent)
		{
			//アンカーを親に設定
			AnchorValue.x = Parent->Width / 2;
			AnchorValue.y = Parent->Height / 2;
		}

		//アンカー計算
		trans.x += AnchorOffset[Anchor].x * AnchorValue.x;
		trans.y += AnchorOffset[Anchor].y * AnchorValue.y;

		//ピボットの分のオフセットを計算。
		D3DXVECTOR2 pivotOffset;
		pivotOffset.x = (Width  * Scale.x) * (0.5f - Pivot.x);
		pivotOffset.y = (Height * Scale.y) * (0.5f - Pivot.y);
		trans += pivotOffset;

		//移動行列作成
		D3DXMatrixTranslation(&TransMatrix, trans.x, trans.y, 0.0f);

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

		//コリジョン計算
		{
			//中心座標を設定
			ColRect.Left = screenWCenter;
			ColRect.Top = screenHCenter;

			//中心の位置を設定
			ColRect.Left += WorldMatrix._41;
			ColRect.Top -= WorldMatrix._42;

			//画像サイズ分ずらす
			ColRect.Left -= WorldMatrix._11 / 2;
			ColRect.Top -= WorldMatrix._22 / 2;

			//右と下も設定
			ColRect.Right = ColRect.Left + WorldMatrix._11;
			ColRect.Bottom = ColRect.Top + WorldMatrix._22;
		}

		//プロジェクション行列を計算
		WorldProjMatrix = WorldMatrix * ProjectionMatrix;
	}
}