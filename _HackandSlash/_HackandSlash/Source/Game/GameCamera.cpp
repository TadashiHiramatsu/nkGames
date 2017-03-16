/**
 * @file	Source\Game\GameCamera.cpp
 *
 * ゲームカメラクラスの実装.
 */
#include"stdafx.h"
#include"GameCamera.h"

#include"Window\MenuWindow\MenuSystem.h"

/**
 * Starts this object.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
void GameCamera::Start()
{

	//調整値を設定.
	PlusPosition_ = Vector3(0, 1.4f, 0);

	//カメラの視点の方向を設定.
	Camera_.SetPosDirection(Vector3(0.0f, 0.2f, -1.0f));

	//カメラの注視点を設定.
	Vector3 target;
	target.Add(Player_->Transform_.Position_ , PlusPosition_);
	Camera_.SetTarget(target);

	//距離を設定.
	DistanceMax_ = Distance_ = 8.0f;
	Camera_.SetDistance(Distance_);

	//更新
	Camera_.Update();

	//ビュー行列の逆行列を取得.
	ViewInvMatrix_ = &Camera_.GetViewInvMatrix();

	//カメラコリジョンを初期化.
	CameraCollision_.Start(0.1f,&Camera_.GetPosDirection(), &Camera_.GetTarget());
	CameraCollision_.SetDefaultDistance(DistanceMax_);

}

/**
 * 更新.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
void GameCamera::Update()
{
	//カメラまわすよー

	Vector2 Rstick = Vector2::Zero;
	Vector2 Lstick = Vector2::Zero;

	if (!g_MenuSystem->GetEffectiveness())
	{
		//メニューが開かれていないので回転できる.
		
		//スティックの情報を取得.
		Rstick = XInput().GetRightStick();
		Lstick = XInput().GetLeftStick();

		//横回転.
		Camera_.SpinHorizontally(Rstick.x* SpinSpeed * Time().DeltaTime());

		//縦回転.
		Camera_.SpinVertically(Rstick.y * SpinSpeed * Time().DeltaTime() * -1);

	}

	//カメラの注視点を設定.
	Vector3 target;
	target.Add(Player_->Transform_.Position_, PlusPosition_);
	Camera_.SetTarget(target);

	//カメラコリジョンの更新.
	CameraCollision_.Update();

	//距離を取得.
	float dis = CameraCollision_.GetDistance();

	//距離を計算.
	if (dis > Distance_)
	{
		//伸びているので感性を付ける.

		//戻る速度.
		float speed = 2.0f *  Time().DeltaTime();
		float movement = Rstick.Length() + Lstick.Length();
		Distance_ += (dis - Distance_) * movement * speed;

	}
	else
	{
		//縮まっているのでそのまま設定.
		Distance_ = dis;
	}

	//最大距離を超えないようにする.
	Distance_ = fmin(Distance_, DistanceMax_);
	//距離を設定.
	Camera_.SetDistance(Distance_);

	//カメラの更新.
	Camera_.Update();

}