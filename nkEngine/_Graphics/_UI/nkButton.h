#pragma once

namespace nkEngine
{

	//UIボタンクラス
	class Button
	{
	public:

		//コンストラクタ
		Button();
		//デストラクタ
		~Button();

		//更新
		void Update();

		//押された
		bool PushDowm()
		{
			return (!isBefPushed && isPushed);
		}

		//押されている
		bool Push()
		{
			return isPushed;
		}

		//離された
		bool PushUp()
		{
			return (isBefPushed && !isPushed);
		}

	private:
		RectTransform* rectTransform; //トランスフォームのアドレス

		bool isPushed; //押されている
		bool isBefPushed; //1フレーム前押されている
	};

}