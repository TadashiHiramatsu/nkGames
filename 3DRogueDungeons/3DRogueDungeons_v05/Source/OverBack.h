/***********************************************************************/
/*! @file  OverBack.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once
#include "2DImage.h"

class COverBack : public C2DImage
{
public:
	COverBack();
	~COverBack();
	void Initialize()override;
	void Update()override;
	double x;
};

