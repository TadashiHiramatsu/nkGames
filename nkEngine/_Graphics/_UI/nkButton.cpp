#include"nkEngine/nkstdafx.h"
#include"nkButton.h"

namespace nkEngine
{
	Button::Button():
		isBefPushed(false),
		isPushed(false),
		rectTransform(nullptr)
	{
	}

	Button::~Button()
	{
	}
	
	void Button::Update()
	{
		//1�t���[���O�̌��ʂ��R�s�[
		isBefPushed = isPushed;

		CollisionRect col = rectTransform->ColRect;

	}

}