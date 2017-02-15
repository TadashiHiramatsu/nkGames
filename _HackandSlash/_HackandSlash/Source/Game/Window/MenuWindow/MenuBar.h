#pragma once

class MenuBar
{
public:

	void Start();
	void Update();
	void Render();

	/** トランスフォームの取得. */
	RectTransform* GetTransform()
	{
		return &BarTransform_;
	}

private:

	/** 本体の画像. */
	Image BarImage_;
	/** 本体のトランスフォーム. */
	RectTransform BarTransform_;

};