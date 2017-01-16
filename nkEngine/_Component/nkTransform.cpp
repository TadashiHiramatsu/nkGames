/**
 * @file _Component\nkTransform.cpp
 *
 * �g�����X�t�H�[���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkTransform.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Transform::Transform() :
		Parent_(nullptr),
		ParentMatrix_(nullptr),
		Position_(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		Scale_(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
		Rotation_(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Transform::~Transform()
	{
	}

	/**
	 * Updates this object.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Transform::Update()
	{
		D3DXMATRIX mTrans, mScale;

		//�ړ��s��̌v�Z
		D3DXMatrixTranslation(&mTrans, Position_.x, Position_.y, Position_.z);
		//��]�s��̌v�Z
		D3DXMatrixRotationQuaternion(&RotationMatrix_, &Rotation_);
		//�g��s��̌v�Z
		D3DXMatrixScaling(&mScale, Scale_.x, Scale_.y, Scale_.z);

		//���[�J���s����v�Z
		LocalMatrix_ = mScale * RotationMatrix_ * mTrans;

		//�e�q�֌W���v�Z
		if (ParentMatrix_)
		{
			D3DXMatrixMultiply(&WorldMatrix_, &LocalMatrix_, ParentMatrix_);
		}
		else
		{
			WorldMatrix_ = LocalMatrix_;
		}

		//���[���h�s��̋t�s����v�Z
		D3DXMatrixInverse(&WorldInvMatrix_, NULL, &WorldMatrix_);
	
	}

	void Transform::BillboardUpdate(const D3DXMATRIX& rot)
	{
		D3DXMATRIX mTrans, mScale;

		//�ړ��s��̌v�Z
		D3DXMatrixTranslation(&mTrans, Position_.x, Position_.y, Position_.z);

		//��]�s��̌v�Z
		D3DXQUATERNION qRot;

		float s;
		s = sin(0);
		qRot.x = rot.m[2][0] * s;
		qRot.y = rot.m[2][1] * s;
		qRot.z = rot.m[2][2] * s;
		qRot.w = cos(0);

		D3DXMATRIX rota;
		D3DXMatrixRotationQuaternion(&rota, &qRot);

		D3DXMatrixMultiply(&RotationMatrix_, &rot, &rota);

		//�g��s��̌v�Z
		D3DXMatrixScaling(&mScale, Scale_.x, Scale_.y, Scale_.z);

		//���[�J���s����v�Z
		LocalMatrix_ = mScale * RotationMatrix_ * mTrans;

		//�e�q�֌W���v�Z
		if (ParentMatrix_)
		{
			D3DXMatrixMultiply(&WorldMatrix_, &LocalMatrix_, ParentMatrix_);
		}
		else
		{
			WorldMatrix_ = LocalMatrix_;
		}

		//���[���h�s��̋t�s����v�Z
		D3DXMatrixInverse(&WorldInvMatrix_, NULL, &WorldMatrix_);
	}

}// namespace nkEngine