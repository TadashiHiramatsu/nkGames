/***********************************************************************/
/*! @file  ClearBack.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once
#include "2DImage.h"

class CClearBack : public C2DImage
{
public:
	CClearBack();
	~CClearBack();
	void Initialize()override;
	void Update()override;
	double x;
};

