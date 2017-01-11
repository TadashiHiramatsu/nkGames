/**
 * @file _Graphics\_ModelRender\nkAnimation.h
 *
 * �X�L�����f���̃A�j���[�V�������Ǘ�����N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �A�j���[�V�����N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class Animation
	{
	private:

		/**
		* �A�j���[�V�����Đ����N�G�X�g.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/10
		*/
		struct RequestPlayAnimationS
		{
			int AnimationSetIndex_;
			float InterpolateTime_;
		};

	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		Animation();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~Animation();

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] animcon �A�j���[�V�����R���g���[��.
		 */
		void Init(ID3DXAnimationController* animcon);

		/**
		 * �A�j���[�V�����̏I���^�C����ݒ肷��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param animationIndex �A�j���[�V�����i���o�[.
		 * @param endTime		 �G���h�^�C��.
		 */
		void SetAnimationEndTime(int animationIndex, double endTime)
		{
			//�A�j���[�V���������݂��Ă����
			if (animationIndex < AnimNum_)
			{
				AnimationEndTime_[animationIndex] = endTime;
			}
		}

		/**
		 * �A�j���[�V�����̃��[�v�t���O��ݒ肷��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param animationIndex �A�j���[�V�����i���o�[.
		 * @param _loopflag		 ���[�v�t���O.
		 */
		void SetAnimationLoopFlags(int animationIndex, bool _loopflag)
		{
			//�A�j���[�V���������݂��Ă����
			if (animationIndex < AnimNum_)
			{
				isAnimationLoops_[animationIndex] = _loopflag;
			}
		}

		/**
		 * �A�j���[�V�����̍Đ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param aniSetIndex �A�j���[�V�����i���o�[.
		 */
		void PlayAnimation(int aniSetIndex);

		/**
		 * �A�j���[�V�����̍Đ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param aniSetIndex	  �A�j���[�V�����i���o�[.
		 * @param interpolateTime ��Ԏ���.
		 */
		void PlayAnimation(int aniSetIndex, float interpolateTime);

		/**
		 * �A�j���[�V�����Z�b�g�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The number animation set.
		 */
		int GetNumAnimationSet() const
		{
			return AnimNum_;
		}

		/**
		 * �A�j���[�V�����̍X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param deltaTime The delta time.
		 */
		void Update(float deltaTime);

		/**
		 * ���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The now animation no.
		 */
		int GetNowAnimationNo()
		{
			return CurrentAnimationSetNo_;
		}

		/**
		 * �A�j���[�V�������Đ�������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return True if play animation, false if not.
		 */
		bool IsPlayAnim()
		{
			return !isAnimEnd_;
		}

		/**
		 * ���[�J���A�j���[�V�����^�C�����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The local animation time.
		 */
		float GetLocalAnimationTime()const
		{
			return (float)LocalAnimationTime_;
		}

		/**
		 * �A�j���[�V�����R���g���[���̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the animation con.
		 */
		ID3DXAnimationController* GetAnimCon()
		{
			return D3DAnimController_;
		}
		
	private:

		/**
		 * �ۊǎ��Ԃ����ƂɃg���b�N�̏d�݂��X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void UpdateTrackWeights();

		/**
		 * �A�j���[�V�����Đ����N�G�X�g���|�b�v.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PopRequestPlayAnimation();

	private:

		/** �A�j���[�V�����R���g���[��. */
		ID3DXAnimationController* D3DAnimController_;
		/** �A�j���[�V�����̐�. */
		int AnimNum_;
		/** �A�j���[�V�����Z�b�g�̔z��. */
		unique_ptr<ID3DXAnimationSet*[]> AnimationSets_;
		/** �u�����f�B���O���[�g�̃e�[�u��. */
		unique_ptr<float[]> BlendRateTable_;
		/** �A�j���[�V�����̃G���h�^�C��. */
		unique_ptr<double[]> AnimationEndTime_;
		/** �A�j���[�V�������[�v�t���O. */
		unique_ptr<bool[]> isAnimationLoops_;
		/** ���[�J���A�j���[�V�����^�C��. */
		double LocalAnimationTime_; 
		/** ���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ�. */
		int CurrentAnimationSetNo_;
		/** ���݂̃g���b�N�̔ԍ�. */
		int CurrentTrackNo_;
		/** �A�j���[�V�����g���b�N�̍ő吔. */
		int NumMaxTracks_; 
		/** �A�j���[�V�����u�����f�B���O. */
		bool isBlending_;
		/** �A�j���[�V�����̏I���t���O. */
		bool isAnimEnd_;
		/** ��Ԓ����H�o��Ԓ��Ftrue�A����ԁFfalse�p. */
		bool isInterpolate_;
		/** ��ԏI������. */
		float InterpolateEndTime_; 
		/** ��Ԏ���. */
		float InterpolateTime_;
		/** �A�j���[�V�����Đ��̃��N�G�X�g. */
		deque<RequestPlayAnimationS> PlayAnimRequest_;
	};
}