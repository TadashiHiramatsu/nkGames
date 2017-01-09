/**
 * @file	_Timer\nkTime.h
 *
 * �^�C���N���X�̒�`.
 */
#pragma once

#include"nkStopwatch.h"

namespace nkEngine
{
	/**
	 * �^�C���N���X.
	 * �V���O���g���N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CTime
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CTime() :
			FrameDeltaTime_(0.0f),
			isReady_(false)
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CTime()
		{
		}

	public:

		/**
		 * �C���X�^���X���擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The instance.
		 */
		static CTime& GetInstance()
		{
			static CTime instance;
			return instance;
		}

		/**
		 * 1�t���[���̌o�ߎ��Ԃ��擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	A float.
		 */
		float DeltaTime() const
		{
			return min(1.0f / 10.0f, FrameDeltaTime_);
		}

		/**
		 * �X�V.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Update()
		{
			if (isReady_) {
				sw_.Stop();
				FrameDeltaTime_ = s_cast<float>(sw_.GetElapsed());
			}
			sw_.Start();
			isReady_ = true;
		}

	private:
		/** 1�t���[���̌o�ߎ���. */
		float FrameDeltaTime_;
		/** �X�g�b�v�E�H�b�`. */
		Stopwatch sw_;
		/** �v�����n�܂��Ă��邩�t���O. */
		bool isReady_;
	};

	/**
	 * �^�C���N���X�̃C���X�^���X���擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	�C���X�^���X.
	 */
	static CTime& Time()
	{
		return CTime::GetInstance();
	}

}// namespace nkEngine