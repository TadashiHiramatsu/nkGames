/**
 * @file _Graphics\_UI\nkButton.h
 *
 * �{�^���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �{�^���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Button
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Button();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Button();

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();

		/**
		 * �����ꂽ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool PushDowm()
		{
			return (!isPushedBef_ && isPushed_);
		}

		/**
		 * ������Ă���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool Push()
		{
			return isPushed_;
		}

		/**
		 * �����ꂽ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool PushUp()
		{
			return (isPushedBef_ && !isPushed_);
		}

	private:

		/** �g�����X�t�H�[���̃A�h���X. */
		RectTransform* RectTransform_;
		/** ������Ă���. */
		bool isPushed_;
		/** 1�t���[���O�̌���. */
		bool isPushedBef_;

	};

}// namespace nkEngine