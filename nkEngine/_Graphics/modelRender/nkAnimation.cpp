#include"nkEngine/nkstdafx.h"
#include"nkAnimation.h"

namespace nkEngine
{
	CAnimation::CAnimation():
		pAnimController(nullptr),
		AnimNum(0),
		LocalAnimationTime(0.0),
		NumMaxTracks(0),
		isBlending(false),
		isInterpolate(false),
		InterpolateEndTime(0.0f),
		InterpolateTime(0.0f)
	{

	}

	CAnimation::~CAnimation()
	{

	}

	void CAnimation::Init(ID3DXAnimationController * _anim)
	{
		//�A�j���[�V�����R���g���[���󂯎��
		pAnimController = _anim;
		ID3DXAnimationSet* animSet;
		pAnimController->GetAnimationSet(0, &animSet);
		AnimNum = pAnimController->GetMaxNumAnimationSets();
		AnimationSets.reset(new ID3DXAnimationSet*[AnimNum]);
		AnimationEndTime.reset(new double[AnimNum]);
		AnimationLoopFlags.reset(new bool[AnimNum]);
		for (int i = 0; i < AnimNum; i++)
		{
			pAnimController->GetAnimationSet(i, &AnimationSets[i]);
			AnimationEndTime[i] = -1.0;
			AnimationLoopFlags[i] = true;
		}
		NumMaxTracks = pAnimController->GetMaxNumTracks();
		BlendRateTable.reset(new float[NumMaxTracks]);
		for (int i = 0; i < NumMaxTracks; i++) {
			BlendRateTable[i] = 1.0f;
		}
		LocalAnimationTime = 0.0;
	}

	void CAnimation::PlayAnimation(int _aniSetIndex)
	{
		//�A�j���[�V���������݂��Ă�����
		if (_aniSetIndex < AnimNum)
		{
			if (pAnimController)
			{
				isAnimEnd = false;
				isInterpolate = false;
				PlayAnimRequest.clear();
				CurrentAnimationSetNo = _aniSetIndex;
				CurrentTrackNo = 0;
				//0�ԖڈȊO�̃g���b�N�͖����ɂ���
				for (int i = 1; i < NumMaxTracks; i++)
				{
					pAnimController->SetTrackEnable(i, FALSE);
				}
				pAnimController->SetTrackWeight(0, 1.0f);
				pAnimController->SetTrackAnimationSet(CurrentTrackNo, AnimationSets[CurrentAnimationSetNo]);
				pAnimController->SetTrackEnable(0, TRUE);
				pAnimController->SetTrackPosition(0, 0.0f);
				LocalAnimationTime = 0.0;
			}
		}
	}

	void CAnimation::PlayAnimation(int _aniSetIndex, float _interpolateTime)
	{
		if (_aniSetIndex < AnimNum)
		{
			if (pAnimController) 
			{
				isAnimEnd = false;
				//��ԊJ�n�̈�B
				isInterpolate = true;
				InterpolateTime = 0.0f;
				InterpolateEndTime = _interpolateTime;
				int prevTrackNo = CurrentTrackNo;
				CurrentTrackNo = (CurrentTrackNo + 1) % NumMaxTracks;
				pAnimController->SetTrackAnimationSet(CurrentTrackNo, AnimationSets[_aniSetIndex]);
				pAnimController->SetTrackSpeed(prevTrackNo, 0.0f);
				pAnimController->SetTrackEnable(CurrentTrackNo, TRUE);
				pAnimController->SetTrackSpeed(CurrentTrackNo, 1.0f);
				pAnimController->SetTrackPosition(CurrentTrackNo, 0.0f);
				LocalAnimationTime = 0.0;
				CurrentAnimationSetNo = _aniSetIndex;
				UpdateTrackWeights();
			}
		}
	}

	void CAnimation::UpdateTrackWeights()
	{
		float weight = 0.0f;
		if (InterpolateTime < InterpolateEndTime)
		{
			weight = InterpolateTime / InterpolateEndTime;
			float invWeight = 1.0f - weight;
			//�E�F�C�g��ݒ�
			for (int i = 0; i < NumMaxTracks; i++)
			{
				if (i != CurrentTrackNo)
				{
					pAnimController->SetTrackWeight(i, BlendRateTable[i] * invWeight);
				}
				else
				{
					pAnimController->SetTrackWeight(i, weight);
				}
			}
		}
		else
		{
			for (int i = 0; i < NumMaxTracks; i++)
			{
				if (i != CurrentTrackNo)
				{
					pAnimController->SetTrackWeight(i, 0.0f);
				}
				else
				{
					pAnimController->SetTrackWeight(i, 1.0f);
				}
			}
		}
	}

	void CAnimation::PopRequestPlayAnimation()
	{
		if (!PlayAnimRequest.empty())
		{
			RequestPlayAnimation& req = PlayAnimRequest.front();
			PlayAnimation(req.AnimationSetIndex, req.InterpolateTime);
			PlayAnimRequest.pop_front();
		}
	}

	void CAnimation::Update(float deltaTime)
	{
		if (pAnimController && !isAnimEnd)
		{
			LocalAnimationTime += deltaTime;

			if (isInterpolate)
			{
				//��Ԓ�
				InterpolateTime += deltaTime;
				float weight = 0.0f;
				if (InterpolateTime > InterpolateEndTime)
				{
					//��ԏI��
					isInterpolate = false;
					weight = 1.0f;
					//���݂̃g���b�N�ȊO�𖳌��ɂ���
					for (int i = 0; i < NumMaxTracks; i++)
					{
						if (i != CurrentTrackNo)
						{
							pAnimController->SetTrackEnable(i, FALSE);
						}
					}
				}
				else
				{
					UpdateTrackWeights();
				}
			}

			if (AnimationEndTime[CurrentAnimationSetNo] > 0.0 //�A�j���[�V�����̏I�����Ԃ��ݒ肳��Ă���B
				&& LocalAnimationTime > AnimationEndTime[CurrentAnimationSetNo] /*�A�j���[�V�����̏I�����Ԃ𒴂����B*/)
			{
				if (AnimationLoopFlags[CurrentAnimationSetNo])
				{
					LocalAnimationTime -= AnimationEndTime[CurrentAnimationSetNo];
					pAnimController->SetTrackPosition(CurrentTrackNo, LocalAnimationTime);
					pAnimController->AdvanceTime(0, NULL);
				}
				else
				{
					isAnimEnd = true;
				}
			}
			else {
				//���ʂɍĐ��B
				if (AnimationSets[CurrentAnimationSetNo]->GetPeriod() < LocalAnimationTime
					&& !AnimationLoopFlags[CurrentAnimationSetNo])
				{
					LocalAnimationTime = AnimationSets[CurrentAnimationSetNo]->GetPeriod();
					isAnimEnd = true;
				}
				else
				{
					pAnimController->AdvanceTime(deltaTime, NULL);
				}

				//���[�J���^�C�����g���b�N����擾���ē���
				D3DXTRACK_DESC trackDesk;
				pAnimController->GetTrackDesc(CurrentTrackNo, &trackDesk);
				LocalAnimationTime = fmod(trackDesk.Position, AnimationSets[CurrentAnimationSetNo]->GetPeriod());
			}
			
			if (isAnimEnd)
			{
				//�A�j���[�V�����I��
				//�A�j���[�V�����̘A���Đ��̃��N�G�X�g���|�b�v
				PopRequestPlayAnimation();
			}
		}
	}
}