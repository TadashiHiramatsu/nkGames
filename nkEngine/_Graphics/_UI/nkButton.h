#pragma once

namespace nkEngine
{

	//UI�{�^���N���X
	class Button
	{
	public:

		//�R���X�g���N�^
		Button();
		//�f�X�g���N�^
		~Button();

		//�X�V
		void Update();

		//�����ꂽ
		bool PushDowm()
		{
			return (!isBefPushed && isPushed);
		}

		//������Ă���
		bool Push()
		{
			return isPushed;
		}

		//�����ꂽ
		bool PushUp()
		{
			return (isBefPushed && !isPushed);
		}

	private:
		RectTransform* rectTransform; //�g�����X�t�H�[���̃A�h���X

		bool isPushed; //������Ă���
		bool isBefPushed; //1�t���[���O������Ă���
	};

}