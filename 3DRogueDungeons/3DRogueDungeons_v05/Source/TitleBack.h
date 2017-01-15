#pragma once
#include "2DImage.h"

class CTitleBack : public C2DImage
{
public:
	CTitleBack();
	~CTitleBack();
	void Initialize()override;
	void Update()override;
	double x;
};

