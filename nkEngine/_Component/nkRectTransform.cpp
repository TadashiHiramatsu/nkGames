/**
 * @file _Component\nkRectTransform.cpp
 *
 * レクトトランスフォームクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkRectTransform.h"

//無名空間
namespace
{

	/** The anchor offset[]. */
	static const D3DXVECTOR2 AnchorOffset[] =
	{
		{ D3DXVECTOR2(-1, -1) },
		{ D3DXVECTOR2(0	, -1) },
		{ D3DXVECTOR2(1	, -1) },
		{ D3DXVECTOR2(-1, 0) },
		{ D3DXVECTOR2(0	, 0) },
		{ D3DXVECTOR2(1	, 0) },
		{ D3DXVECTOR2(-1,1) },
		{ D3DXVECTOR2(0	,1) },
		{ D3DXVECTOR2(1	,1) }
	};
}

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	RectTransform::RectTransform() :
		Parent_(nullptr),
		Anchor_(AnchorPresetE::MiddleCenter),
		Position_(D3DXVECTOR3(0, 0, 0)),
		Width_(100),
		Height_(100),
		Pivot_(D3DXVECTOR2(0.5, 0.5)),
		Rotation_(D3DXQUATERNION(0, 0, 0, 1)),
		Scale_(D3DXVECTOR2(1, 1))
	{
		//スクリーン幅を取得
		int screenW = Engine().GetScreenW();
		int screenH = Engine().GetScreenH();
		
		//プロジェクション行列の作成
		D3DXMatrixIdentity(&ProjectionMatrix_);
		ProjectionMatrix_._11 = 2.0f / screenW;
		ProjectionMatrix_._22 = 2.0f / screenH;

	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	RectTransform::~RectTransform()
	{
	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void RectTransform::Update()
	{
		D3DXMATRIX mScale, mScaleSizeOff, mTrans, mRot;

		//スクリーンの中心地を取得
		int screenWCenter = Engine().GetScreenW() / 2;
		int screenHCenter = Engine().GetScreenH() / 2;

		D3DXVECTOR2 trans = Position_;

		//アンカーを画面に設定
		D3DXVECTOR2 AnchorValue;
		AnchorValue.x = screenWCenter;
		AnchorValue.y = screenHCenter;

		if (Parent_)
		{
			//アンカーを親に設定
			AnchorValue.x = Parent_->Width_ / 2;
			AnchorValue.y = Parent_->Height_ / 2;
		}

		//アンカー計算
		trans.x += AnchorOffset[Anchor_].x * AnchorValue.x;
		trans.y += AnchorOffset[Anchor_].y * AnchorValue.y;

		//ピボットの分のオフセットを計算。
		D3DXVECTOR2 pivotOffset;
		pivotOffset.x = (Width_  * Scale_.x) * (0.5f - Pivot_.x);
		pivotOffset.y = (Height_ * Scale_.y) * (0.5f - Pivot_.y);
		trans += pivotOffset;

		//移動行列作成
		D3DXMatrixTranslation(&mTrans, trans.x, trans.y, Position_.z);

		//拡大
		D3DXVECTOR3 scale;
		scale.x = (Width_  * Scale_.x);
		scale.y = (Height_ * Scale_.y);
		scale.z = 1.0f;

		//サイズを含めたスケール行列の計算
		D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.x);

		//拡大ベクトル値だけのスケール行列の計算
		D3DXMatrixScaling(&mScaleSizeOff, Scale_.x, Scale_.y, 1.0f);

		//回転行列の計算
		D3DXMatrixRotationQuaternion(&mRot, &Rotation_);

		//ワールド行列の計算
		WorldMatrix_ = mScale * mRot * mTrans;
		//サイズを含まないワールド行列の計算
		WorldSizeOffMatrix_ = mScaleSizeOff * mRot * mTrans;

		//親子関係の計算
		if (Parent_)
		{
			WorldMatrix_ *= Parent_->WorldSizeOffMatrix_;
			WorldSizeOffMatrix_ *= Parent_->WorldSizeOffMatrix_;
		}

		//コリジョン計算
		{
			//中心座標を設定
			BoxCol_.Left_ = screenWCenter;
			BoxCol_.Top_ = screenHCenter;

			//中心の位置を設定
			BoxCol_.Left_ += WorldMatrix_._41;
			BoxCol_.Top_ -= WorldMatrix_._42;

			//画像サイズ分ずらす
			BoxCol_.Left_ -= WorldMatrix_._11 / 2;
			BoxCol_.Top_ -= WorldMatrix_._22 / 2;

			//右と下も設定
			BoxCol_.Right_ = BoxCol_.Left_ + WorldMatrix_._11;
			BoxCol_.Bottom_ = BoxCol_.Top_ + WorldMatrix_._22;
		}

		//プロジェクション行列を計算
		WorldProjMatrix_ = WorldMatrix_ * ProjectionMatrix_;
	}
}