/**
 * @file _Graphics\nkCamera.cpp
 *
 * カメラクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkCamera.h"

namespace nkEngine
{

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Camera::Update()
	{
			
		//アスペクト比の計算
		Aspect_ = (float)Engine().GetFrameW() / (float)Engine().GetFrameH();

		//プロジェクション行列の計算
		ProjMatrix_.MakeProjection(Angle_, Aspect_, Near_, Far_);

		//ポジション方向の計算
		PosDirection_.Normalize();

		//上限計算
		PosDirection_.y = fmin(UpperLimit_, PosDirection_.y);
		//下限計算
		PosDirection_.y = fmax(LowerLimit_, PosDirection_.y);

		//ポジションの計算
		PosDirection_.Scale(Distance_);
		Position_.Add(PosDirection_, Target_);

		//ビュー行列の計算
		ViewMatrix_.MakeLookAt(Position_, Target_, Up_);

		//ビュー行列の逆行列を計算
		ViewInvMatrix_.Inverse(ViewMatrix_);

		//回転行列を計算
		RotationMatrix_ = ViewInvMatrix_;
		RotationMatrix_.m[3][0] = 0.0f;
		RotationMatrix_.m[3][1] = 0.0f;
		RotationMatrix_.m[3][2] = 0.0f;
		RotationMatrix_.m[3][3] = 1.0f;

		//回転行列の逆行列を計算
		RotationInvMatrix_.Transpose(RotationMatrix_);

	}

	/**
	* 横回転.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param rot 回転量。度.
	*/
	void Camera::SpinHorizontally(float rot)
	{

		Matrix tmp = Matrix::Identity;
		
		//行列をY軸回りに回転.
		tmp.MakeRotationY(rot);

		PosDirection_.Normalize();

		//ベクトルに反映.
		PosDirection_.TransformCoord(tmp);

	}

	/**
	* 縦回転.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param rot 回転量(度).
	*/
	void Camera::SpinVertically(float rot)
	{
		//クォータニオン.
		Quaternion qua = Quaternion::Identity;
		//回転行列.
		Matrix tmp = Matrix::Identity;

		PosDirection_.Normalize();

		//横方向ベクトル.
		Vector3 side = Vector3::Zero;
		side.x = -PosDirection_.z;
		side.z = PosDirection_.x;

		//クォータニオンを横軸回りに回転.
		qua.RotationAxis(side, rot);

		//行列をクォータニオンにより回転.
		tmp.MakeRotationQuaternion(qua);

		//ベクトルに反映.
		PosDirection_.TransformCoord(tmp);

	}

}// namespace nkEngine