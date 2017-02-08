/***********************************************************************/
/*! @file  TitleCursor.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once
#include "2DImage.h"
#include"IncludeManagers.h"
#include"SceneManager.h"

#define MAX_COMMAND_NUM 2	//COMMANDÇÃMAXêî
enum COMMAND_SELECT { START = 0, EXIT }; ///<enumÇ≈óÒãìå^COMMAND_SELECTÇçÏê¨


class CTitleCursor : public C2DImage
{
public:
	CTitleCursor();
	~CTitleCursor();
	void Initialize()override;
	void Update()override;
private:
	int m_selectIndex;
};

