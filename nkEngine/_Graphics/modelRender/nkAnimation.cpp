#include"nkEngine/nkstdafx.h"
#include"nkAnimation.h"

namespace nkEngine
{
	CAnimation::CAnimation():
		m_pAnimationController(nullptr),
		m_numAnimSet(0),
		m_localAnimationTime(0.0),
		m_currentAnimationSetNo(0),
		m_currentTrackNo(0),
		m_numMaxTracks(0),
		m_isInterpolate(false),
		m_interpolateEndTime(0.0f),
		m_interpolateTime(0.0f)
	{

	}

	CAnimation::~CAnimation()
	{

	}

	void CAnimation::Init(ID3DXAnimationController * animcon)
	{
		m_pAnimationController = animcon;
		ID3DXAnimationSet* animSet;
		m_pAnimationController->GetAnimationSet(0, &animSet);
		m_numAnimSet = m_pAnimationController->GetMaxNumAnimationSets();
		m_numMaxTracks = m_pAnimationController->GetMaxNumTracks();
		m_animationEndTime.reset(new double[m_numAnimSet]);
		m_animationSets.reset(new ID3DXAnimationSet*[m_numAnimSet]);
		blendRateTable.reset(new float[m_numMaxTracks]);
		for (int i = 0; i < m_numMaxTracks; i++) {
			blendRateTable[i] = 1.0f;
		}
		for (int i = 0; i < m_numAnimSet; i++)
		{
			m_pAnimationController->GetAnimationSet(i, &m_animationSets[i]);
			m_animationEndTime[i] = -1.0;
		}
		m_localAnimationTime = 0.0;
	}

	void CAnimation::PlayAnimation(int aniSetIndex)
	{
		//アニメーションが存在していたら
		if (aniSetIndex < m_numAnimSet)
		{
			if (m_pAnimationController)
			{
				m_currentAnimationSetNo = aniSetIndex;
				m_currentTrackNo = 0;
				//0番目以外のトラックは無効にする
				m_pAnimationController->SetTrackEnable(0, TRUE);
				for (int i = 1; i < m_numMaxTracks; i++)
				{
					m_pAnimationController->SetTrackEnable(i, FALSE);
				}
				m_pAnimationController->SetTrackWeight(0, 1.0f);
				m_pAnimationController->SetTrackAnimationSet(m_currentAnimationSetNo, m_animationSets[m_currentAnimationSetNo]);
				m_pAnimationController->SetTrackPosition(0, 0.0f);
				m_localAnimationTime = 0.0;
			}
		}
	}

	void CAnimation::PlayAnimation(int aniSetIndex, float interpolateTime)
	{
		if (aniSetIndex < m_numAnimSet) {
			if (m_pAnimationController) {
				//補間開始の印。
				m_isInterpolate = true;
				m_interpolateTime = 0.0f;
				m_interpolateEndTime = interpolateTime;
				m_currentTrackNo = (m_currentTrackNo + 1) % m_numMaxTracks;
				m_pAnimationController->SetTrackAnimationSet(m_currentTrackNo, m_animationSets[aniSetIndex]);
				m_pAnimationController->SetTrackSpeed(m_currentTrackNo, 1.0f);
				m_pAnimationController->SetTrackPosition(m_currentTrackNo, 0.0f);
				m_localAnimationTime = 0.0;
				m_currentAnimationSetNo = aniSetIndex;
			}
		}
	}

	void CAnimation::Update(float deltaTime)
	{
		if (m_pAnimationController) {
			m_localAnimationTime += deltaTime;

			if (m_animationEndTime[m_currentAnimationSetNo] > 0.0 //アニメーションの終了時間が設定されている。
				&& m_localAnimationTime > m_animationEndTime[m_currentAnimationSetNo] //アニメーションの終了時間を超えた。
				) {
				m_localAnimationTime -= m_animationEndTime[m_currentAnimationSetNo];
				m_pAnimationController->SetTrackPosition(m_currentTrackNo, m_localAnimationTime);
				m_pAnimationController->AdvanceTime(0, NULL);
			}
			else {
				//普通に再生。
				m_pAnimationController->AdvanceTime(deltaTime, NULL);
			}
			if (m_isInterpolate) {
				ID3DXAnimationSet* animSet = m_animationSets[2];
				float period = animSet->GetPeriod();
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
							m_pAnimationController->SetTrackEnable(i, FALSE);
						}
					}
				}
				else {
					weight = m_interpolateTime / m_interpolateEndTime;
					float invWeight = 1.0f - weight;
					//ウェイトを設定していく。
					for (int i = 0; i < m_numMaxTracks; i++) {
						if (i != m_currentTrackNo) {
							m_pAnimationController->SetTrackWeight(i, blendRateTable[i] * invWeight);
						}
						else {
							m_pAnimationController->SetTrackWeight(i, weight);
						}
					}
				}
			}
		}
	}
}