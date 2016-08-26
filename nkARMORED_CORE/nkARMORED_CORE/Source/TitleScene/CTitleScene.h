#pragma once

class CTitleScene : public CScene
{
public:
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;
private:
	CSprite title;
};