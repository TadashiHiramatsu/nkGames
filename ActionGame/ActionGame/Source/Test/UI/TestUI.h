#pragma once

class TestUI : public IGameObject
{
public:

	TestUI();
	~TestUI();
	
	void Start()override;
	void Update()override;
	void Render()override;

private:
	Image imageP;
	RectTransform rectTransformP;

	TestFont Mouse_x;
	TestFont Mouse_y;

	TestFont Image_x;
	TestFont Image_y;
};