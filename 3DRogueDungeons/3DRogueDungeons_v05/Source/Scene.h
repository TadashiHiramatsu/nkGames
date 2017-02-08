/***********************************************************************/
/*! @file  Scene.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once
#include"SceCommon.h"

class CScene
{
public:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] name 
	 *  @retval  
	 */
	/***********************************************************************/
	CScene(const string& name)
	{
		m_name = name;
	}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval string 
	 */
	/***********************************************************************/
	string GetName()const{ return m_name; }
private:
	string m_name;
};
