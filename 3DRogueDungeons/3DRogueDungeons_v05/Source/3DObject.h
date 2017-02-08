/***********************************************************************/
/*! @file  3DObject.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once
#include"3DData.h"

class C3DObject :public C3DData
{
public:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] XName 
	 *  @retval void
	 */
	/***********************************************************************/
	void Initialize(LPCTSTR XName){ XfileName = XName; C3DData::Initialize(); }
};