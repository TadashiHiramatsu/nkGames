/**
 * @file _Graphics\_UI\nkButton.cpp
 *
 * �{�^���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkButton.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Button::Button():
		isPushedBef_(false),
		isPushed_(false),
		RectTransform_(nullptr)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Button::~Button()
	{
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Button::Update()
	{
		//1�t���[���O�̌��ʂ��R�s�[
		isPushedBef_ = isPushed_;

		BoxCollisionS col = RectTransform_->BoxCol_;

	}

}// namespace nkEngine