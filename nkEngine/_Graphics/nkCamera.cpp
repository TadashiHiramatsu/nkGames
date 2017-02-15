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
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Camera::Camera() :
		Target_(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		PosDirection_(D3DXVECTOR3(0.0f, 0.0f, -1.0f)),
		Up_(D3DXVECTOR3(0.0f,1.0f,0.0f)),
		Distance_(1),
		Fovy_(D3DXToRadian(45.0f)),
		Aspect_(0.0f),
		Near_(0.1f),
		Far_(1200.0f),
		LowerLimit_(-0.8f),
		UpperLimit_(0.8f)
	{

		D3DXMatrixIdentity(&ViewMatrix_);
		D3DXMatrixIdentity(&ProjMatrix_);
		D3DXMatrixIdentity(&RotationMatrix_);
		D3DXMatrixIdentity(&RotationInvMatrix_);

	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Camera::~Camera()
	{
	}

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
		D3DXMatrixPerspectiveFovLH(&ProjMatrix_, Fovy_, Aspect_, Near_, Far_);

		//ポジション方向の計算
		D3DXVec3Normalize(&PosDirection_, &PosDirection_);

		//上限計算
		PosDirection_.y = min(UpperLimit_, PosDirection_.y);
		//下限計算
		PosDirection_.y = max(LowerLimit_, PosDirection_.y);

		//ポジションの計算
		Position_ = PosDirection_ * Distance_ + Target_;

		//ビュー行列の計算
		D3DXMatrixLookAtLH(&ViewMatrix_, &Position_, &Target_, &Up_);

		//ビュー行列の逆行列を計算
		D3DXMatrixInverse(&ViewInvMatrix_, NULL, &ViewMatrix_);

		//回転行列を計算
		RotationMatrix_ = ViewInvMatrix_;
		RotationMatrix_.m[3][0] = 0.0f;
		RotationMatrix_.m[3][1] = 0.0f;
		RotationMatrix_.m[3][2] = 0.0f;
		RotationMatrix_.m[3][3] = 1.0f;

		//回転行列の逆行列を計算
		D3DXMatrixTranspose(&RotationInvMatrix_, &RotationMatrix_);

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

		D3DXMATRIX tmp;
		
		D3DXMatrixRotationY(&tmp, D3DXToRadian(rot));

		D3DXVec3TransformCoord(&PosDirection_, &PosDirection_, &tmp);

	}

	/**
	* 縦回転.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param rot 回転量。度.
	*/
	void Camera::SpinVertically(float rot)
	{
		
		D3DXQUATERNION qua;
		D3DXMATRIX tmp;

		//横方向を計算
		D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-PosDirection_.z, 0, PosDirection_.x), D3DXToRadian(rot));

		D3DXMatrixRotationQuaternion(&tmp, &qua);
		D3DXVec3TransformCoord(&PosDirection_, &PosDirection_, &tmp);

	}

}// namespace nkEngine