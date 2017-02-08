/***********************************************************************/
/*! @file  TitleCursor.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "TitleCursor.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTitleCursor::CTitleCursor() { }
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTitleCursor::~CTitleCursor(){ }

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTitleCursor::Initialize()
{
	m_selectIndex = COMMAND_SELECT::START;
	m_position = D3DXVECTOR2(100,500);
	m_angle = 0.0f;
	m_scale = D3DXVECTOR2(0.2f, 0.2f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_texFileName = "Texture\\TitleCursor.png";
	C2DImage::Initialize();
	m_texCenter = D3DXVECTOR2(0, 0);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTitleCursor::Update()
{
	int dir = 0;
	//DOWNキーが押されたか判定
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		//m_selectIndexがMAX_COMMAND_NUM以下ならdirの値更新
		if (m_selectIndex < MAX_COMMAND_NUM - 1)
		{
			dir = 1;
		}
	}
	//UPキーが押されたか判定
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		//m_selectIndexが0以上ならdirの値更新
		if (m_selectIndex>0)
		{
			dir = -1;
		}
	}
	//m_selectIndexの値更新
	m_selectIndex += dir;
	m_position.y += 55 * (float)dir;


	//ENTERキーが押されたとき
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//選択されている物を実行
		switch (m_selectIndex)
		{
			//STARTが選択されていた場合
		case COMMAND_SELECT::START:
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::MAIN);
			break;
			//EXITが選択されていた場合
		case COMMAND_SELECT::EXIT:
			PostQuitMessage(0);
			break;
		}
	}
	this->SetupMatrices();
}