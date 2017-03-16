/**
 * @file _Component\nkRectTransform.cpp
 *
 * ���N�g�g�����X�t�H�[���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkRectTransform.h"

namespace nkEngine
{

	namespace
	{

		/** �A���J�[�I�t�Z�b�g. */
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
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	RectTransform::RectTransform()
	{
		//�X�N���[�������擾
		int screenW = Engine().GetScreenW();
		int screenH = Engine().GetScreenH();
		
		//�v���W�F�N�V�����s��̍쐬
		ProjectionMatrix_._11 = 2.0f / screenW;
		ProjectionMatrix_._22 = 2.0f / screenH;

	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void RectTransform::Update()
	{
		Matrix mScale, mScaleSizeOff, mTrans, mRot;

		//�X�N���[���̒��S�n���擾
		int screenWCenter = Engine().GetScreenW() / 2;
		int screenHCenter = Engine().GetScreenH() / 2;

		Vector2 trans;
		trans.x = Position_.x;
		trans.y = Position_.y;
		
		//�A���J�[����ʂɐݒ�
		Vector2 AnchorValue;
		AnchorValue.x = screenWCenter;
		AnchorValue.y = screenHCenter;

		if (Parent_)
		{
			//�A���J�[��e�ɐݒ�
			AnchorValue.x = Parent_->Width_ / 2;
			AnchorValue.y = Parent_->Height_ / 2;
		}

		//�A���J�[�v�Z
		trans.x += AnchorOffset[(int)Anchor_].x * AnchorValue.x;
		trans.y += AnchorOffset[(int)Anchor_].y * AnchorValue.y;

		//�s�{�b�g�̕��̃I�t�Z�b�g���v�Z�B
		Vector2 pivotOffset;
		pivotOffset.x = (Width_  * Scale_.x) * (0.5f - Pivot_.x);
		pivotOffset.y = (Height_ * Scale_.y) * (0.5f - Pivot_.y);
		trans.Add(pivotOffset);

		//�ړ��s��쐬
		mTrans.MakeTranslation(Vector3(trans.x, trans.y, Position_.z));

		//�g��
		Vector3 scale;
		scale.x = (Width_  * Scale_.x);
		scale.y = (Height_ * Scale_.y);
		scale.z = 1.0f;

		//�T�C�Y���܂߂��X�P�[���s��̌v�Z
		mScale.MakeScaling(scale);

		//�g��x�N�g���l�����̃X�P�[���s��̌v�Z
		mScaleSizeOff.MakeScaling(Vector3(Scale_.x, Scale_.y, 1.0f));

		//��]�s��̌v�Z
		mRot.MakeRotationQuaternion(Rotation_);

		//���[���h�s��̌v�Z
		WorldMatrix_.Mul(mScale, mRot);
		WorldMatrix_.Mul(WorldMatrix_, mTrans);

		//�T�C�Y���܂܂Ȃ����[���h�s��̌v�Z
		WorldSizeOffMatrix_.Mul(mScaleSizeOff, mRot);
		WorldSizeOffMatrix_.Mul(WorldSizeOffMatrix_, mTrans);

		//�e�q�֌W�̌v�Z
		if (Parent_)
		{
			WorldMatrix_.Mul(WorldMatrix_, Parent_->WorldSizeOffMatrix_);
			WorldSizeOffMatrix_.Mul(WorldSizeOffMatrix_, Parent_->WorldSizeOffMatrix_);
		}

		//�v���W�F�N�V�����s����v�Z
		WorldProjMatrix_.Mul(WorldMatrix_,ProjectionMatrix_);

	}
}