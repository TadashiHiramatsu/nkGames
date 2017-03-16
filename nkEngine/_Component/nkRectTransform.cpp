/**
 * @file _Component\nkRectTransform.cpp
 *
 * レクトトランスフォームクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkRectTransform.h"

namespace nkEngine
{

	namespace
	{

		/** アンカーオフセット. */
		static const Vector2 AnchorOffset[] =
		{
			{ Vector2(-1, 1) },
			{ Vector2(0	, 1) },
			{ Vector2(1	, 1) },
			{ Vector2(-1, 0) },
			{ Vector2(0	, 0) },
			{ Vector2(1	, 0) },
			{ Vector2(-1,-1) },
			{ Vector2(0	,-1) },
			{ Vector2(1	,-1) }
		};
	}

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	RectTransform::RectTransform()
	{
		//スクリーン幅を取得
		int screenW = Engine().GetScreenW();
		int screenH = Engine().GetScreenH();
		
		//プロジェクション行列の作成
		ProjectionMatrix_._11 = 2.0f / screenW;
		ProjectionMatrix_._22 = 2.0f / screenH;

	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void RectTransform::Update()
	{
		Matrix mScale, mScaleSizeOff, mTrans, mRot;

		//スクリーンの中心地を取得
		int screenWCenter = Engine().GetScreenW() / 2;
		int screenHCenter = Engine().GetScreenH() / 2;

		Vector2 trans;
		trans.x = Position_.x;
		trans.y = Position_.y;
		
		//アンカーを画面に設定
		Vector2 AnchorValue;
		AnchorValue.x = screenWCenter;
		AnchorValue.y = screenHCenter;

		if (Parent_)
		{
			//アンカーを親に設定
			AnchorValue.x = Parent_->Width_ / 2;
			AnchorValue.y = Parent_->Height_ / 2;
		}

		//アンカー計算
		trans.x += AnchorOffset[(int)Anchor_].x * AnchorValue.x;
		trans.y += AnchorOffset[(int)Anchor_].y * AnchorValue.y;

		//ピボットの分のオフセットを計算。
		Vector2 pivotOffset;
		pivotOffset.x = (Width_  * Scale_.x) * (0.5f - Pivot_.x);
		pivotOffset.y = (Height_ * Scale_.y) * (0.5f - Pivot_.y);
		trans.Add(pivotOffset);

		//移動行列作成
		mTrans.MakeTranslation(Vector3(trans.x, trans.y, Position_.z));

		//拡大
		Vector3 scale;
		scale.x = (Width_  * Scale_.x);
		scale.y = (Height_ * Scale_.y);
		scale.z = 1.0f;

		//サイズを含めたスケール行列の計算
		mScale.MakeScaling(scale);

		//拡大ベクトル値だけのスケール行列の計算
		mScaleSizeOff.MakeScaling(Vector3(Scale_.x, Scale_.y, 1.0f));

		//回転行列の計算
		mRot.MakeRotationQuaternion(Rotation_);

		//ワールド行列の計算
		WorldMatrix_.Mul(mScale, mRot);
		WorldMatrix_.Mul(WorldMatrix_, mTrans);

		//サイズを含まないワールド行列の計算
		WorldSizeOffMatrix_.Mul(mScaleSizeOff, mRot);
		WorldSizeOffMatrix_.Mul(WorldSizeOffMatrix_, mTrans);

		//親子関係の計算
		if (Parent_)
		{
			WorldMatrix_.Mul(WorldMatrix_, Parent_->WorldSizeOffMatrix_);
			WorldSizeOffMatrix_.Mul(WorldSizeOffMatrix_, Parent_->WorldSizeOffMatrix_);
		}

		//プロジェクション行列を計算
		WorldProjMatrix_.Mul(WorldMatrix_,ProjectionMatrix_);

	}
}