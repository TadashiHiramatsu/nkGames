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
	Image image;
	RectTransform rectTransform;

	Image imageP;
	RectTransform rectTransformP;

	Image imageC;
	RectTransform rectTransformC;
};