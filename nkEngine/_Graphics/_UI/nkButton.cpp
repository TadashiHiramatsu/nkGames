/**
 * @file _Graphics\_UI\nkButton.cpp
 *
 * ボタンクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkButton.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
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
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Button::~Button()
	{
	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Button::Update()
	{
		//1フレーム前の結果をコピー
		isPushedBef_ = isPushed_;

		BoxCollisionS col = RectTransform_->BoxCol_;

	}

}// namespace nkEngine