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
		//アニメーションコントローラ受け取り
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
		//アニメーションが存在していたら
		if (_aniSetIndex < AnimNum)
		{
			if (pAnimController)
			{
				isAnimEnd = false;
				isInterpolate = false;
				PlayAnimRequest.clear();
				CurrentAnimationSetNo = _aniSetIndex;
				CurrentTrackNo = 0;
				//0番目以外のトラックは無効にする
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
				//補間開始の印。
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
			//ウェイトを設定
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
				//補間中
				InterpolateTime += deltaTime;
				float weight = 0.0f;
				if (InterpolateTime > InterpolateEndTime)
				{
					//補間終了
					isInterpolate = false;
					weight = 1.0f;
					//現在のトラック以外を無効にする
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

			if (AnimationEndTime[CurrentAnimationSetNo] > 0.0 //アニメーションの終了時間が設定されている。
				&& LocalAnimationTime > AnimationEndTime[CurrentAnimationSetNo] /*アニメーションの終了時間を超えた。*/)
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
				//普通に再生。
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

				//ローカルタイムをトラックから取得して同期
				D3DXTRACK_DESC trackDesk;
				pAnimController->GetTrackDesc(CurrentTrackNo, &trackDesk);
				LocalAnimationTime = fmod(trackDesk.Position, AnimationSets[CurrentAnimationSetNo]->GetPeriod());
			}
			
			if (isAnimEnd)
			{
				//アニメーション終了
				//アニメーションの連続再生のリクエストをポップ
				PopRequestPlayAnimation();
			}
		}
	}
}