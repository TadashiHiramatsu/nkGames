//�X�L�����f���̃A�j���[�V�������Ǘ�����N���X
#pragma once

namespace nkEngine
{
	//�A�j���[�V�����N���X
	class CAnimation
	{
	public:
		//�R���X�g���N�^
		CAnimation();
		//�f�X�g���N�^
		~CAnimation();
		//������
		//���� �A�j���[�V�����R���g���[��
		void Init(ID3DXAnimationController* animcon);
		//�A�j���[�V�����̏I���^�C����ݒ肷��
		//��P���� �A�j���[�V�����i���o�[
		//��Q���� �G���h�^�C��
		void SetAnimationEndTime(int animationIndex, double endTime)
		{
			m_animationEndTime[animationIndex] = endTime;
		}
		//�A�j���[�V�����̍Đ�
		void PlayAnimation(int aniSetIndex);
		//�A�j���[�V�����̍Đ�
		//��Ԏ���
		void PlayAnimation(int aniSetIndex, float interpolateTime);
		//�A�j���[�V�����Z�b�g�̎擾
		int GetNumAnimationSet()const
		{
			return m_numAnimSet;
		}
		//�A�j���[�V�����̍X�V
		void Update(float deltaTime);
	private:
		ID3DXAnimationController* m_pAnimationController; //�A�j���[�V�����R���g���[��
		int m_numAnimSet; //�A�j���[�V�����̐�
		unique_ptr<ID3DXAnimationSet*[]> m_animationSets; //�A�j���[�V�����Z�b�g�̔z��
		unique_ptr<float[]> blendRateTable; //�u�����f�B���O���[�g�̃e�[�u���B
		unique_ptr<double[]> m_animationEndTime; //�A�j���[�V�����̃G���h�^�C��
		double m_localAnimationTime; //���[�J���A�j���[�V�����^�C��
		int m_currentAnimationSetNo; //���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ�
		int m_currentTrackNo; //���݂̃g���b�N�̔ԍ�
		int m_numMaxTracks; //�A�j���[�V�����g���b�N�̍ő吔

		bool m_isInterpolate; //��Ԓ����H�o��Ԓ��Ftrue�A����ԁFfalse�p
		float m_interpolateEndTime; //��ԏI������
		float m_interpolateTime; //��Ԏ���
	};
}