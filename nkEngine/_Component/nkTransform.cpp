/**
 * @file _Component\nkTransform.cpp
 *
 * トランスフォームクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkTransform.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
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
	 * デストラクタ.
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

		//移動行列の計算
		D3DXMatrixTranslation(&mTrans, Position_.x, Position_.y, Position_.z);
		//回転行列の計算
		D3DXMatrixRotationQuaternion(&RotationMatrix_, &Rotation_);
		//拡大行列の計算
		D3DXMatrixScaling(&mScale, Scale_.x, Scale_.y, Scale_.z);

		//ローカル行列を計算
		LocalMatrix_ = mScale * RotationMatrix_ * mTrans;

		//親子関係を計算
		if (ParentMatrix_)
		{
			D3DXMatrixMultiply(&WorldMatrix_, &LocalMatrix_, ParentMatrix_);
		}
		else
		{
			WorldMatrix_ = LocalMatrix_;
		}

		//ワールド行列の逆行列を計算
		D3DXMatrixInverse(&WorldInvMatrix_, NULL, &WorldMatrix_);
	
	}

	void Transform::BillboardUpdate(const D3DXMATRIX& rot)
	{
		D3DXMATRIX mTrans, mScale;

		//移動行列の計算
		D3DXMatrixTranslation(&mTrans, Position_.x, Position_.y, Position_.z);

		//回転行列の計算
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

		//拡大行列の計算
		D3DXMatrixScaling(&mScale, Scale_.x, Scale_.y, Scale_.z);

		//ローカル行列を計算
		LocalMatrix_ = mScale * RotationMatrix_ * mTrans;

		//親子関係を計算
		if (ParentMatrix_)
		{
			D3DXMatrixMultiply(&WorldMatrix_, &LocalMatrix_, ParentMatrix_);
		}
		else
		{
			WorldMatrix_ = LocalMatrix_;
		}

		//ワールド行列の逆行列を計算
		D3DXMatrixInverse(&WorldInvMatrix_, NULL, &WorldMatrix_);
	}

}// namespace nkEngine