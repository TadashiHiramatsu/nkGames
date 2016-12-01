#include"nkEngine/nkstdafx.h"
#include"nkUITransform.h"

namespace nkEngine
{
	UITransform::UITransform():
		mParent(nullptr)
	{

	}

	void UITransform::Update()
	{
		D3DXMATRIX  mScale, mRot, mTrans;

		int screenBufferW = Engine().GetScreenW();
		int screenBufferH = Engine().GetScreenH();
		int screenBufferHalfW = screenBufferW / 2;
		int screenBufferHalfH = screenBufferH / 2;

		D3DXVECTOR3 scale;
		scale.x = Size.x / screenBufferW;
		scale.y = Size.y / screenBufferH;
		scale.z = 1.0f;

		D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.x);

		//移動
		D3DXVECTOR3 trans;
		trans.x = Position.x / screenBufferHalfW - 1;
		trans.y = Position.y / screenBufferHalfH - 1;
		trans.z = 0.0f;

		//ピボットの分のオフセットを計算。
		D3DXVECTOR3 pivotOffset;
		pivotOffset.x = (Size.x * (0.5f - Pivot.x)) / screenBufferHalfW;
		pivotOffset.y = (Size.y * (0.5f - Pivot.y)) / screenBufferHalfH;
		pivotOffset.z = 0.0f;
		trans += pivotOffset;

		D3DXMatrixTranslation(&mTrans, trans.x, trans.y, trans.z);

		D3DXMatrixRotationQuaternion(&mRot, &Rotation);

		mLocal = mScale * mRot * mTrans;

		if (mParent)
		{
			D3DXMatrixMultiply(&mWorld, &mLocal, mParent);
		}
		else
		{
			mWorld = mLocal;
		}
	}
}