/**
 * @file _Graphics\_ModelRender\nkAnimation.cpp
 *
 * �A�j���[�V�����N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkAnimation.h"

namespace nkEngine
{

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] animcon If non-null, the animation.
	 */
	void Animation::Init(ID3DXAnimationController * animcon)
	{
		//�A�j���[�V�����R���g���[���󂯎��
		D3DAnimController_ = animcon;


		//�A�j���[�V�����Z�b�g�̍쐬
		ID3DXAnimationSet* animSet;
		D3DAnimController_->GetAnimationSet(0, &animSet);

		//�A�j���[�V�����̐���ݒ�
		AnimNum_ = D3DAnimController_->GetMaxNumAnimationSets();
		AnimationSets_.reset(new ID3DXAnimationSet*[AnimNum_]);
		AnimationEndTime_.reset(new double[AnimNum_]);
		isAnimationLoops_.reset(new bool[AnimNum_]);

		//�A�j���[�V�������ɐݒ�
		for (int i = 0; i < AnimNum_; i++)
		{
			D3DAnimController_->GetAnimationSet(i, &AnimationSets_[i]);
			AnimationEndTime_[i] = -1.0;
			isAnimationLoops_[i] = true;
		}

		D3DAnimController_->AddRef();

		//�A�j���[�V�����g���b�N�ݒ�
		NumMaxTracks_ = D3DAnimController_->GetMaxNumTracks();

		//�u�����h���[�g�e�[�u���̐ݒ�
		BlendRateTable_.reset(new float[NumMaxTracks_]);
		for (int i = 0; i < NumMaxTracks_; i++)
		{
			BlendRateTable_[i] = 1.0f;
		}

		//���[�J���A�j���[�V�����^�C���̏�����
		LocalAnimationTime_ = 0.0;

	}

	/**
	 * Play animation.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param aniSetIndex Zero-based index of the animation set.
	 */
	void Animation::PlayAnimation(int aniSetIndex)
	{
		//�A�j���[�V���������݂��Ă�����
		if (aniSetIndex < AnimNum_)
		{
			//�A�j���[�V�����R���g���[���[��nullptr�ȊO�Ȃ�
			if (D3DAnimController_)
			{

				//�A�j���[�V�����Đ����ɕύX
				isAnimEnd_ = false;

				//�A�j���[�V������Ԃ�ݒ�
				isInterpolate_ = false;

				//�A�j���[�V�������N�G�X�g���폜
				PlayAnimRequest_.clear();

				//�A�j���[�V�����i���o�[��ݒ�
				CurrentAnimationSetNo_ = aniSetIndex;

				CurrentTrackNo_ = 0;

				//0�ԖڈȊO�̃g���b�N�͖����ɂ���
				for (int i = 1; i < NumMaxTracks_; i++)
				{
					D3DAnimController_->SetTrackEnable(i, FALSE);
				}

				D3DAnimController_->SetTrackWeight(0, 1.0f);
				D3DAnimController_->SetTrackAnimationSet(CurrentTrackNo_, AnimationSets_[CurrentAnimationSetNo_]);
				D3DAnimController_->SetTrackEnable(0, TRUE);
				D3DAnimController_->SetTrackPosition(0, 0.0f);

				//���[�J���A�j���[�V�����^�C���̏�����
				LocalAnimationTime_ = 0.0;

			}

		}

	}

	/**
	 * Play animation.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param aniSetIndex	   Zero-based index of the animation set.
	 * @param interpolateTime The interpolate time.
	 */
	void Animation::PlayAnimation(int aniSetIndex, float interpolateTime)
	{
		//�A�j���[�V���������݂��Ă����
		if (aniSetIndex < AnimNum_)
		{
			//�A�j���[�V�����R���g���[����nullptr�ȊO�Ȃ�
			if (D3DAnimController_) 
			{

				//�A�j���[�V�����Đ����ɕύX
				isAnimEnd_ = false;

				//��ԊJ�n�ɐݒ�
				isInterpolate_ = true;
				//��Ԏ��Ԃ̏�����
				InterpolateTime_ = 0.0f;
				//��ԏI�����Ԃ̐ݒ�
				InterpolateEndTime_ = interpolateTime;

				//���݂̃g���b�N���擾
				int prevTrackNo = CurrentTrackNo_;

				//�g���b�N�̍X�V
				CurrentTrackNo_ = (CurrentTrackNo_ + 1) % NumMaxTracks_;

				D3DAnimController_->SetTrackAnimationSet(CurrentTrackNo_, AnimationSets_[aniSetIndex]);
				D3DAnimController_->SetTrackSpeed(prevTrackNo, 0.0f);
				D3DAnimController_->SetTrackEnable(CurrentTrackNo_, TRUE);
				D3DAnimController_->SetTrackSpeed(CurrentTrackNo_, 1.0f);
				D3DAnimController_->SetTrackPosition(CurrentTrackNo_, 0.0f);

				//���[�J���A�j���[�V�����^�C���̏�����
				LocalAnimationTime_ = 0.0;

				//���݂̃A�j���[�V�����i���o�[��ݒ�
				CurrentAnimationSetNo_ = aniSetIndex;

				//�ۊǎ��Ԃ����ƂɃg���b�N�̏d�݂��X�V
				UpdateTrackWeights();

			}

		}

	}

	/**
	* �ۊǎ��Ԃ����ƂɃg���b�N�̏d�݂��X�V.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/10
	*/
	void Animation::UpdateTrackWeights()
	{

		//�d��.
		float weight = 0.0f;

		//��Ԏ��ԓ��Ȃ�
		if (InterpolateTime_ < InterpolateEndTime_)
		{
			//�d�݂��v�Z
			weight = InterpolateTime_ / InterpolateEndTime_;

			//�d�݂̋t���v�Z
			float invWeight = 1.0f - weight;

			//�E�F�C�g��ݒ�
			for (int i = 0; i < NumMaxTracks_; i++)
			{
				//���݂̃g���b�N�łȂ�
				if (i != CurrentTrackNo_)
				{
					D3DAnimController_->SetTrackWeight(i, BlendRateTable_[i] * invWeight);
				}
				else
				{
					D3DAnimController_->SetTrackWeight(i, weight);
				}
			}
		}
		else
		{
			for (int i = 0; i < NumMaxTracks_; i++)
			{
				if (i != CurrentTrackNo_)
				{
					D3DAnimController_->SetTrackWeight(i, 0.0f);
				}
				else
				{
					D3DAnimController_->SetTrackWeight(i, 1.0f);
				}
			}
		}

	}

	/**
	* �A�j���[�V�����Đ����N�G�X�g���|�b�v.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/10
	*/
	void Animation::PopRequestPlayAnimation()
	{
		if (!PlayAnimRequest_.empty())
		{
			if (AnimationSets_[CurrentAnimationSetNo_]->GetPeriod() - PlayAnimRequest_.front().InterpolateTime_ < LocalAnimationTime_)
			{
				//�擪�̂��̂��擾.
				RequestPlayAnimationS& req = PlayAnimRequest_.front();
				//�ݒ�.
				PlayAnimation(req.AnimationSetIndex_, req.InterpolateTime_);
				//�r�o.
				PlayAnimRequest_.pop_front();
			}
		}
	}

	/**
	 * Updates the given deltaTime.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param deltaTime The delta time.
	 */
	void Animation::Update(float deltaTime)
	{
		if (D3DAnimController_ && !isAnimEnd_)
		{
			//���[�J���A�j���[�V�����^�C�����v�Z
			LocalAnimationTime_ += deltaTime;

			if (isInterpolate_)
			{
				//��Ԓ�
				InterpolateTime_ += deltaTime;

				float weight = 0.0f;
				if (InterpolateTime_ > InterpolateEndTime_)
				{
					//��ԏI��
					isInterpolate_ = false;

					weight = 1.0f;

					//���݂̃g���b�N�ȊO�𖳌��ɂ���
					for (int i = 0; i < NumMaxTracks_; i++)
					{
						if (i != CurrentTrackNo_)
						{
							D3DAnimController_->SetTrackEnable(i, FALSE);
						}
					}

				}
				else
				{
					//�d�݂��v�Z
					UpdateTrackWeights();
				}
			}

			if (AnimationEndTime_[CurrentAnimationSetNo_] > 0.0 && //�A�j���[�V�����̏I�����Ԃ��ݒ肳��Ă���. 
				LocalAnimationTime_ > AnimationEndTime_[CurrentAnimationSetNo_]) //�A�j���[�V�����̏I�����Ԃ𒴂���.
			{
				//���[�v����
				if (isAnimationLoops_[CurrentAnimationSetNo_])
				{
					//���[�J���A�j���[�V�����^�C�������Z
					LocalAnimationTime_ -= AnimationEndTime_[CurrentAnimationSetNo_];

					D3DAnimController_->SetTrackPosition(CurrentTrackNo_, LocalAnimationTime_);
					D3DAnimController_->AdvanceTime(0, NULL);
				}
				else
				{
					//�A�j���[�V�����̏I��
					isAnimEnd_ = true;
				}
			}
			else
			{
				//���ʂɍĐ��B
				if (AnimationSets_[CurrentAnimationSetNo_]->GetPeriod() < LocalAnimationTime_
					&& !isAnimationLoops_[CurrentAnimationSetNo_])
				{
					//�A�j���[�V�����I��
					LocalAnimationTime_ = AnimationSets_[CurrentAnimationSetNo_]->GetPeriod();
					isAnimEnd_ = true;
				}
				else
				{
					D3DAnimController_->AdvanceTime(deltaTime, NULL);
				}

				//���[�J���^�C�����g���b�N����擾���ē���
				D3DXTRACK_DESC trackDesk;
				D3DAnimController_->GetTrackDesc(CurrentTrackNo_, &trackDesk);

				//���[�J���A�j���[�V�����^�C���̌v�Z
				LocalAnimationTime_ = fmod(trackDesk.Position, AnimationSets_[CurrentAnimationSetNo_]->GetPeriod());

			}

			//�A�j���[�V�����I��
			//�A�j���[�V�����̘A���Đ��̃��N�G�X�g���|�b�v
			PopRequestPlayAnimation();

		}

	}

}// namespace nkEngine