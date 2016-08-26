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
		//�A�j���[�V���������݂��Ă�����
		if (aniSetIndex < m_numAnimSet)
		{
			if (m_pAnimationController)
			{
				m_currentAnimationSetNo = aniSetIndex;
				m_currentTrackNo = 0;
				//0�ԖڈȊO�̃g���b�N�͖����ɂ���
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
				//��ԊJ�n�̈�B
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

			if (m_animationEndTime[m_currentAnimationSetNo] > 0.0 //�A�j���[�V�����̏I�����Ԃ��ݒ肳��Ă���B
				&& m_localAnimationTime > m_animationEndTime[m_currentAnimationSetNo] //�A�j���[�V�����̏I�����Ԃ𒴂����B
				) {
				m_localAnimationTime -= m_animationEndTime[m_currentAnimationSetNo];
				m_pAnimationController->SetTrackPosition(m_currentTrackNo, m_localAnimationTime);
				m_pAnimationController->AdvanceTime(0, NULL);
			}
			else {
				//���ʂɍĐ��B
				m_pAnimationController->AdvanceTime(deltaTime, NULL);
			}
			if (m_isInterpolate) {
				ID3DXAnimationSet* animSet = m_animationSets[2];
				float period = animSet->GetPeriod();
				//��Ԓ��B
				m_interpolateTime += deltaTime;
				float weight = 0.0f;
				if (m_interpolateTime > m_interpolateEndTime) {
					//��ԏI���B
					m_isInterpolate = false;
					weight = 1.0f;
					//���݂̃g���b�N�ȊO�𖳌��ɂ���B
					for (int i = 0; i < m_numMaxTracks; i++) {
						if (i != m_currentTrackNo) {
							m_pAnimationController->SetTrackEnable(i, FALSE);
						}
					}
				}
				else {
					weight = m_interpolateTime / m_interpolateEndTime;
					float invWeight = 1.0f - weight;
					//�E�F�C�g��ݒ肵�Ă����B
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