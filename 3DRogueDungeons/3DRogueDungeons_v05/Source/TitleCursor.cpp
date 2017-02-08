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
	//DOWN�L�[�������ꂽ������
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		//m_selectIndex��MAX_COMMAND_NUM�ȉ��Ȃ�dir�̒l�X�V
		if (m_selectIndex < MAX_COMMAND_NUM - 1)
		{
			dir = 1;
		}
	}
	//UP�L�[�������ꂽ������
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		//m_selectIndex��0�ȏ�Ȃ�dir�̒l�X�V
		if (m_selectIndex>0)
		{
			dir = -1;
		}
	}
	//m_selectIndex�̒l�X�V
	m_selectIndex += dir;
	m_position.y += 55 * (float)dir;


	//ENTER�L�[�������ꂽ�Ƃ�
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//�I������Ă��镨�����s
		switch (m_selectIndex)
		{
			//START���I������Ă����ꍇ
		case COMMAND_SELECT::START:
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::MAIN);
			break;
			//EXIT���I������Ă����ꍇ
		case COMMAND_SELECT::EXIT:
			PostQuitMessage(0);
			break;
		}
	}
	this->SetupMatrices();
}