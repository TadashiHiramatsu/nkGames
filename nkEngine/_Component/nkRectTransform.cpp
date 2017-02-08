/**
 * @file _Component\nkRectTransform.cpp
 *
 * ���N�g�g�����X�t�H�[���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkRectTransform.h"

//�������
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
	 * �R���X�g���N�^.
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
		//�X�N���[�������擾
		int screenW = Engine().GetScreenW();
		int screenH = Engine().GetScreenH();
		
		//�v���W�F�N�V�����s��̍쐬
		D3DXMatrixIdentity(&ProjectionMatrix_);
		ProjectionMatrix_._11 = 2.0f / screenW;
		ProjectionMatrix_._22 = 2.0f / screenH;

	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	RectTransform::~RectTransform()
	{
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void RectTransform::Update()
	{
		D3DXMATRIX mScale, mScaleSizeOff, mTrans, mRot;

		//�X�N���[���̒��S�n���擾
		int screenWCenter = Engine().GetScreenW() / 2;
		int screenHCenter = Engine().GetScreenH() / 2;

		D3DXVECTOR2 trans = Position_;

		//�A���J�[����ʂɐݒ�
		D3DXVECTOR2 AnchorValue;
		AnchorValue.x = screenWCenter;
		AnchorValue.y = screenHCenter;

		if (Parent_)
		{
			//�A���J�[��e�ɐݒ�
			AnchorValue.x = Parent_->Width_ / 2;
			AnchorValue.y = Parent_->Height_ / 2;
		}

		//�A���J�[�v�Z
		trans.x += AnchorOffset[Anchor_].x * AnchorValue.x;
		trans.y += AnchorOffset[Anchor_].y * AnchorValue.y;

		//�s�{�b�g�̕��̃I�t�Z�b�g���v�Z�B
		D3DXVECTOR2 pivotOffset;
		pivotOffset.x = (Width_  * Scale_.x) * (0.5f - Pivot_.x);
		pivotOffset.y = (Height_ * Scale_.y) * (0.5f - Pivot_.y);
		trans += pivotOffset;

		//�ړ��s��쐬
		D3DXMatrixTranslation(&mTrans, trans.x, trans.y, Position_.z);

		//�g��
		D3DXVECTOR3 scale;
		scale.x = (Width_  * Scale_.x);
		scale.y = (Height_ * Scale_.y);
		scale.z = 1.0f;

		//�T�C�Y���܂߂��X�P�[���s��̌v�Z
		D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.x);

		//�g��x�N�g���l�����̃X�P�[���s��̌v�Z
		D3DXMatrixScaling(&mScaleSizeOff, Scale_.x, Scale_.y, 1.0f);

		//��]�s��̌v�Z
		D3DXMatrixRotationQuaternion(&mRot, &Rotation_);

		//���[���h�s��̌v�Z
		WorldMatrix_ = mScale * mRot * mTrans;
		//�T�C�Y���܂܂Ȃ����[���h�s��̌v�Z
		WorldSizeOffMatrix_ = mScaleSizeOff * mRot * mTrans;

		//�e�q�֌W�̌v�Z
		if (Parent_)
		{
			WorldMatrix_ *= Parent_->WorldSizeOffMatrix_;
			WorldSizeOffMatrix_ *= Parent_->WorldSizeOffMatrix_;
		}

		//�R���W�����v�Z
		{
			//���S���W��ݒ�
			BoxCol_.Left_ = screenWCenter;
			BoxCol_.Top_ = screenHCenter;

			//���S�̈ʒu��ݒ�
			BoxCol_.Left_ += WorldMatrix_._41;
			BoxCol_.Top_ -= WorldMatrix_._42;

			//�摜�T�C�Y�����炷
			BoxCol_.Left_ -= WorldMatrix_._11 / 2;
			BoxCol_.Top_ -= WorldMatrix_._22 / 2;

			//�E�Ɖ����ݒ�
			BoxCol_.Right_ = BoxCol_.Left_ + WorldMatrix_._11;
			BoxCol_.Bottom_ = BoxCol_.Top_ + WorldMatrix_._22;
		}

		//�v���W�F�N�V�����s����v�Z
		WorldProjMatrix_ = WorldMatrix_ * ProjectionMatrix_;
	}
}