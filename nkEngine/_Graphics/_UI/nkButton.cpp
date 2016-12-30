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
		//1フレーム前の結果をコピー
		isBefPushed = isPushed;

		CollisionRect col = rectTransform->ColRect;

	}

}