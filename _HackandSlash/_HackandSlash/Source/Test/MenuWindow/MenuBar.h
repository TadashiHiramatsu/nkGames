#pragma once

class MenuBar
{
public:

	void Start();
	void Update();
	void Render();

	/** �g�����X�t�H�[���̎擾. */
	RectTransform* GetTransform()
	{
		return &BarTransform_;
	}

private:

	/** �{�̂̉摜. */
	Image BarImage_;
	/** �{�̂̃g�����X�t�H�[��. */
	RectTransform BarTransform_;

};