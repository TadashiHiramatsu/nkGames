/**
 * @file _Graphics\_UI\nkButton.h
 *
 * ボタンクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ボタンクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Button
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Button();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Button();

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();

		/**
		 * 押された.
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
		 * 押されている.
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
		 * 離された.
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

		/** トランスフォームのアドレス. */
		RectTransform* RectTransform_;
		/** 押されている. */
		bool isPushed_;
		/** 1フレーム前の結果. */
		bool isPushedBef_;

	};

}// namespace nkEngine