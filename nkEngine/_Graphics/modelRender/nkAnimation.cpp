#include"nkEngine/nkstdafx.h"
#include"nkAnimation.h"

namespace nkEngine
{
	CAnimation::CAnimation():
		pAnimController(nullptr),
		AnimNum(0),
		LocalAnimationTime(0.0),
		CurrentAnimationSetNo(0),
		CurrentTrackNo(0),
		NumMaxTracks(0),
		isInterpolate(false),
		InterpolateEndTime(0.0f),
		InterpolateTime(0.0f)
	{

	}

	CAnimation::~CAnimation()
	{

	}

	void CAnimation::Init(ID3DXAnimationController * animcon)
	{
		pAnimController = animcon;
		ID3DXAnimationSet* animSet;
		pAnimController->GetAnimationSet(0, &animSet);
		AnimNum = pAnimController->GetMaxNumAnimationSets();
		m_numMaxTracks = pAnimController->GetMaxNumTracks();
		m_animationEndTime.reset(new double[AnimNum]);
		m_animationSets.reset(new ID3DXAnimationSet*[AnimNum]);
		blendRateTable.reset(new float[m_numMaxTracks]);
		for (int i = 0; i < m_numMaxTracks; i++) {
			blendRateTable[i] = 1.0f;
		}
		for (int i = 0; i < AnimNum; i++)
		{
			pAnimController->GetAnimationSet(i, &m_animationSets[i]);
			m_animationEndTime[i] = -1.0;
		}
		m_localAnimationTime = 0.0;
	}

	void CAnimation::PlayAnimation(int aniSetIndex)
	{
		//アニメーションが存在していたら
		if (aniSetIndex < AnimNum)
		{
			NowAnimation = aniSetIndex;
			if (pAnimController)
			{
				m_isInterpolate = false;
				m_currentAnimationSetNo = aniSetIndex;
				m_currentTrackNo = 0;
				//0番目以外のトラックは無効にする
				for (int i = 1; i < m_numMaxTracks; i++)
				{
					pAnimController->SetTrackEnable(i, FALSE);
				}
				pAnimController->SetTrackWeight(0, 1.0f);
				pAnimController->SetTrackAnimationSet(m_currentTrackNo, m_animationSets[m_currentAnimationSetNo]);
				pAnimController->SetTrackEnable(0, TRUE);
				pAnimController->SetTrackPosition(0, 0.0f);
				m_localAnimationTime = 0.0;
			}
		}
	}

	void CAnimation::PlayAnimation(int aniSetIndex, float interpolateTime)
	{
		if (aniSetIndex < AnimNum)
		{
			NowAnimation = aniSetIndex;
			if (pAnimController) 
			{
				//補間開始の印。
				m_isInterpolate = true;
				m_interpolateTime = 0.0f;
				m_interpolateEndTime = interpolateTime;
				m_currentTrackNo = (m_currentTrackNo + 1) % m_numMaxTracks;
				pAnimController->SetTrackAnimationSet(m_currentTrackNo, m_animationSets[aniSetIndex]);
				pAnimController->SetTrackSpeed(m_currentTrackNo, 1.0f);
				pAnimController->SetTrackPosition(m_currentTrackNo, 0.0f);
				m_localAnimationTime = 0.0;
				m_currentAnimationSetNo = aniSetIndex;
			}
		}
	}

	void CAnimation::Update(float deltaTime)
	{
		if (pAnimController) {
			m_localAnimationTime += deltaTime;

			if (m_animationEndTime[m_currentAnimationSetNo] > 0.0 //アニメーションの終了時間が設定されている。
				&& m_localAnimationTime > m_animationEndTime[m_currentAnimationSetNo] //アニメーションの終了時間を超えた。
				) {
				m_localAnimationTime -= m_animationEndTime[m_currentAnimationSetNo];
				pAnimController->SetTrackPosition(m_currentTrackNo, m_localAnimationTime);
				pAnimController->AdvanceTime(0, NULL);
			}
			else {
				//普通に再生。
				pAnimController->AdvanceTime(deltaTime, NULL);
			}
			if (m_isInterpolate) {
				/*ID3DXAnimationSet* animSet = m_animationSets[2];
				double period = animSet->GetPeriod();*/
				//補間中。
				m_interpolateTime += deltaTime;
				float weight = 0.0f;
				if (m_interpolateTime > m_interpolateEndTime) {
					//補間終了。
					m_isInterpolate = false;
					weight = 1.0f;
					//現在のトラック以外を無効にする。
					for (int i = 0; i < m_numMaxTracks; i++) {
						if (i != m_currentTrackNo) {
							pAnimController->SetTrackEnable(i, FALSE);
						}
					}
				}
				else {
					weight = m_interpolateTime / m_interpolateEndTime;
					float invWeight = 1.0f - weight;
					//ウェイトを設定していく。
					for (int i = 0; i < m_numMaxTracks; i++) {
						if (i != m_currentTrackNo) {
							pAnimController->SetTrackWeight(i, blendRateTable[i] * invWeight);
						}
						else {
							pAnimController->SetTrackWeight(i, weight);
						}
					}
				}
			}
		}
	}
}