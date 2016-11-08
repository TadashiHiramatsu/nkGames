//�X�L�����f���̃A�j���[�V�������Ǘ�����N���X
#pragma once

#include <deque>

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
			if (animationIndex < AnimNum)
			{
				AnimationEndTime[animationIndex] = endTime;
			}
		}

		//�A�j���[�V�����̃��[�v�t���O��ݒ肷��
		//��P���� �A�j���[�V�����i���o�[
		//��Q���� ���[�v�t���O
		void SetAnimationLoopFlags(int animationIndex, bool _loopflag)
		{
			if (animationIndex < AnimNum)
			{
				AnimationLoopFlags[animationIndex] = _loopflag;
			}
		}

		//�A�j���[�V�����̍Đ�
		void PlayAnimation(int aniSetIndex);

		//�A�j���[�V�����̍Đ�
		//��Ԏ���
		void PlayAnimation(int aniSetIndex, float interpolateTime);
		
		
		//�A�j���[�V�����Z�b�g�̎擾
		int GetNumAnimationSet()const
		{
			return AnimNum;
		}

		//�A�j���[�V�����̍X�V
		void Update(float deltaTime);

		//���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ����擾
		int GetNowAnimationNo()
		{
			return CurrentAnimationSetNo;
		}

		//�A�j���[�V�������Đ�������
		bool IsPlayAnim()
		{
			return !isAnimEnd;
		}

		//���[�J���A�j���[�V�����^�C�����擾
		float GetLocalAnimationTime()const
		{
			return(float)LocalAnimationTime;
		}
		
	private:
		//�ۊǎ��Ԃ����ƂɃg���b�N�̏d�݂��X�V
		void UpdateTrackWeights();

		//�A�j���[�V�����Đ����N�G�X�g���|�b�v
		void PopRequestPlayAnimation();

	private:
		//�A�j���[�V�����Đ����N�G�X�g
		struct RequestPlayAnimation
		{
			int AnimationSetIndex;
			float InterpolateTime;
		};
		//�A�j���[�V�����R���g���[��
		ID3DXAnimationController* pAnimController;
		//�A�j���[�V�����̐�
		int AnimNum;
		//�A�j���[�V�����Z�b�g�̔z��
		unique_ptr<ID3DXAnimationSet*[]> AnimationSets;
		//�u�����f�B���O���[�g�̃e�[�u���B
		unique_ptr<float[]> BlendRateTable;
		//�A�j���[�V�����̃G���h�^�C��
		unique_ptr<double[]> AnimationEndTime;
		//�A�j���[�V�������[�v�t���O
		unique_ptr<bool[]> AnimationLoopFlags;
		//���[�J���A�j���[�V�����^�C��
		double LocalAnimationTime; 
		//���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ�
		int CurrentAnimationSetNo; 
		//���݂̃g���b�N�̔ԍ�
		int CurrentTrackNo;
		//�A�j���[�V�����g���b�N�̍ő吔
		int NumMaxTracks; 
		//�A�j���[�V�����u�����f�B���O
		bool isBlending;
		//�A�j���[�V�����̏I���t���O
		bool isAnimEnd;
		//��Ԓ����H�o��Ԓ��Ftrue�A����ԁFfalse�p
		bool isInterpolate; 
		//��ԏI������
		float InterpolateEndTime; 
		//��Ԏ���
		float InterpolateTime;
		//�A�j���[�V�����Đ��̃��N�G�X�g
		deque<RequestPlayAnimation> PlayAnimRequest;
	};
}