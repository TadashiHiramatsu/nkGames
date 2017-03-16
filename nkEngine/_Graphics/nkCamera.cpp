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
		ProjMatrix_.MakeProjection(Angle_, Aspect_, Near_, Far_);

		//�|�W�V���������̌v�Z
		PosDirection_.Normalize();

		//����v�Z
		PosDirection_.y = fmin(UpperLimit_, PosDirection_.y);
		//�����v�Z
		PosDirection_.y = fmax(LowerLimit_, PosDirection_.y);

		//�|�W�V�����̌v�Z
		PosDirection_.Scale(Distance_);
		Position_.Add(PosDirection_, Target_);

		//�r���[�s��̌v�Z
		ViewMatrix_.MakeLookAt(Position_, Target_, Up_);

		//�r���[�s��̋t�s����v�Z
		ViewInvMatrix_.Inverse(ViewMatrix_);

		//��]�s����v�Z
		RotationMatrix_ = ViewInvMatrix_;
		RotationMatrix_.m[3][0] = 0.0f;
		RotationMatrix_.m[3][1] = 0.0f;
		RotationMatrix_.m[3][2] = 0.0f;
		RotationMatrix_.m[3][3] = 1.0f;

		//��]�s��̋t�s����v�Z
		RotationInvMatrix_.Transpose(RotationMatrix_);

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

		Matrix tmp = Matrix::Identity;
		
		//�s���Y�����ɉ�].
		tmp.MakeRotationY(rot);

		PosDirection_.Normalize();

		//�x�N�g���ɔ��f.
		PosDirection_.TransformCoord(tmp);

	}

	/**
	* �c��].
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param rot ��]��(�x).
	*/
	void Camera::SpinVertically(float rot)
	{
		//�N�H�[�^�j�I��.
		Quaternion qua = Quaternion::Identity;
		//��]�s��.
		Matrix tmp = Matrix::Identity;

		PosDirection_.Normalize();

		//�������x�N�g��.
		Vector3 side = Vector3::Zero;
		side.x = -PosDirection_.z;
		side.z = PosDirection_.x;

		//�N�H�[�^�j�I�����������ɉ�].
		qua.RotationAxis(side, rot);

		//�s����N�H�[�^�j�I���ɂ���].
		tmp.MakeRotationQuaternion(qua);

		//�x�N�g���ɔ��f.
		PosDirection_.TransformCoord(tmp);

	}

}// namespace nkEngine