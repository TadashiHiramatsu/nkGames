/**
 * @file _Graphics\nkCamera.cpp
 *
 * �J�����N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkCamera.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
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
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Camera::~Camera()
	{
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Camera::Update()
	{
			
		//�A�X�y�N�g��̌v�Z
		Aspect_ = (float)Engine().GetFrameW() / (float)Engine().GetFrameH();

		//�v���W�F�N�V�����s��̌v�Z
		D3DXMatrixPerspectiveFovLH(&ProjMatrix_, Fovy_, Aspect_, Near_, Far_);

		//�|�W�V���������̌v�Z
		D3DXVec3Normalize(&PosDirection_, &PosDirection_);

		//����v�Z
		PosDirection_.y = min(UpperLimit_, PosDirection_.y);
		//�����v�Z
		PosDirection_.y = max(LowerLimit_, PosDirection_.y);

		//�|�W�V�����̌v�Z
		Position_ = PosDirection_ * Distance_ + Target_;

		//�r���[�s��̌v�Z
		D3DXMatrixLookAtLH(&ViewMatrix_, &Position_, &Target_, &Up_);

		//�r���[�s��̋t�s����v�Z
		D3DXMatrixInverse(&ViewInvMatrix_, NULL, &ViewMatrix_);

		//��]�s����v�Z
		RotationMatrix_ = ViewInvMatrix_;
		RotationMatrix_.m[3][0] = 0.0f;
		RotationMatrix_.m[3][1] = 0.0f;
		RotationMatrix_.m[3][2] = 0.0f;
		RotationMatrix_.m[3][3] = 1.0f;

		//��]�s��̋t�s����v�Z
		D3DXMatrixTranspose(&RotationInvMatrix_, &RotationMatrix_);

	}

	/**
	* ����].
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param rot ��]�ʁB�x.
	*/
	void Camera::SpinHorizontally(float rot)
	{

		D3DXMATRIX tmp;
		
		D3DXMatrixRotationY(&tmp, D3DXToRadian(rot));

		D3DXVec3TransformCoord(&PosDirection_, &PosDirection_, &tmp);

	}

	/**
	* �c��].
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param rot ��]�ʁB�x.
	*/
	void Camera::SpinVertically(float rot)
	{
		
		D3DXQUATERNION qua;
		D3DXMATRIX tmp;

		//���������v�Z
		D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-PosDirection_.z, 0, PosDirection_.x), D3DXToRadian(rot));

		D3DXMatrixRotationQuaternion(&tmp, &qua);
		D3DXVec3TransformCoord(&PosDirection_, &PosDirection_, &tmp);

	}

}// namespace nkEngine