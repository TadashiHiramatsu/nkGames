/***********************************************************************/
/*! @file  MainScene.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "MainScene.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CMainScene::Initialize()
{
	srand(unsigned int(time(NULL)));

	m_Dun = new(CDungeon);
	m_Dun->Initialize();
	num++;
	m_player = new(CPlayer);
	m_player->Initialize(m_Dun);
	setEnemy();
	this->CreateSprite();
	Life = new CLifeGage;
	Life->Initialize(m_player);

	ZeroMemory(&light1, sizeof(D3DLIGHT9));
	light1.Type = D3DLIGHT_DIRECTIONAL;
	light1.Diffuse.r = 0.3f;
	light1.Diffuse.g = 0.3f;
	light1.Diffuse.b = 0.3f;
	light1.Range = 1;
	light1.Direction = D3DXVECTOR3(0,-1,0);
	(*graphicsDevice()).SetLight(0, &light1);
	(*graphicsDevice()).LightEnable(0, true);
	light1.Direction = D3DXVECTOR3(1, 0, 0);
	(*graphicsDevice()).SetLight(1, &light1);
	(*graphicsDevice()).LightEnable(1, true);
	light1.Direction = D3DXVECTOR3(-1, 0, 0);
	(*graphicsDevice()).SetLight(2, &light1);
	(*graphicsDevice()).LightEnable(2, true);
	light1.Direction = D3DXVECTOR3(0, 0, 1);
	(*graphicsDevice()).SetLight(3, &light1);
	(*graphicsDevice()).LightEnable(3, true);
	light1.Direction = D3DXVECTOR3(0, 0, -1);
	(*graphicsDevice()).SetLight(4, &light1);
	(*graphicsDevice()).LightEnable(4, true);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CMainScene::Update()
{
	m_player->Updata();
	for (short idx = 0; idx < EnemyNum; idx++)
	{
		m_Enemy[idx]->Updata();
	}
	// éÀâeïœä∑
	D3DXMatrixPerspectiveFovLH(&Persp, D3DXToRadian(45), 640.0f / 480.0f, 1.0f, 10000.0f);
	// çsóÒìoò^
	(*graphicsDevice()).SetTransform(D3DTS_WORLD, &World);
	(*graphicsDevice()).SetTransform(D3DTS_PROJECTION, &Persp);
	if (m_Dun->getmapid(m_player->getTrans()) == MapID::MAP_STAIRS && GetAsyncKeyState(VK_SHIFT) & 0x8000&&flg==false)
	{
		flg = true;
		if (m_player->getEnemyI())
		{
			MessageBox(NULL, TEXT("ìGÇ…í«ÇÌÇÍÇƒÇ¢Ç‹Ç∑"), TEXT("écîO"), MB_OK);
		}
		else
		{
			num++;
			if (num > 5)
			{
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::CLEAR);
			}
			else
			{
			MessageBox(NULL, TEXT("â∫Ç÷ç~ÇËÇ‹Ç∑"), TEXT("äKíi"), MB_OK);
			delete m_Dun;
			m_Dun = new(CDungeon);
			m_Dun->Initialize();
			m_player->setTrans(m_Dun->getroom());
			m_player->setDD(m_Dun);
			setEnemy();
			}
			
		}
	}
	else
	{
		flg = false;
	}
	Cllision();
	Life->Update();

	if (m_player->getLife() <= 0.0f)
	{
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::OVER);
	}
	
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CMainScene::Draw()
{
	m_Dun->Draw();
	m_player->Draw();
	for (short idx = 0; idx < EnemyNum; idx++)
	{
		m_Enemy[idx]->Draw();
		if (m_Enemy[idx]->getLife() <= 0.0f)
		{
			it = m_Enemy.begin();
			it +=idx;
			m_Enemy.erase(it);
			EnemyNum--;
			m_player->setEnemyIF();
		}
		
	}
	Life->Draw(m_pSprite);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CMainScene::setEnemy()
{
	ZeroMemory(m_map, sizeof(m_map));
	m_Enemy.clear();
	EnemyNum = m_Dun->getroomnum() / 20;
	for (short idx = 0; idx < EnemyNum; idx++)
	{
		short App = rand() % 100;
		if (App < 30)
		{
			m_Enemy.push_back(new CEnemySlime);
		}
		else if (App < 50)
		{
			m_Enemy.push_back(new CEnemyFlower);
		}
		else if (App < 70)
		{
			m_Enemy.push_back(new CEnemyFox);
		}
		else if (App < 90)
		{
			m_Enemy.push_back(new CEnemyInsect);
		}
		else if (App < 100)
		{
			m_Enemy.push_back(new CEnemyLabrys);
		}
	}
	for (short idx = 0; idx < EnemyNum; idx++)
	{
		m_Enemy[idx]->Initialize(m_Dun,m_player);
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CMainScene::Cllision()
{
	CSphereCollision Collision;
	for (short idx = 0; idx < EnemyNum; idx++)
	{
		if (Collision.isCollision(m_player->getTrans(), m_player->getRadius(), m_Enemy[idx]->getTrans(), m_Enemy[idx]->getRadius()))
		{
			m_player->setLife(m_Enemy[idx]->getDamage());
			D3DXVECTOR3 knockback = D3DXVECTOR3(m_player->getTrans().x - m_Enemy[idx]->getTrans().x, 0, m_player->getTrans().z - m_Enemy[idx]->getTrans().z);
			float L = sqrt(knockback.x*knockback.x + knockback.z*knockback.z);
			knockback.x = knockback.x / L * 1.2f;
			knockback.z = knockback.z / L * 1.2f;
			if (!m_player->WallCollision(m_player->getTrans() + knockback))
			{
				m_player->setTrans(D3DXVECTOR3(m_player->getTrans() + knockback));
			}
			m_Enemy[idx]->setTrans(D3DXVECTOR3(m_Enemy[idx]->getTrans() - knockback));
		}
	}
	for (short idx = 0; idx < EnemyNum; idx++)
	{
		for (short idx2 = 0; idx2 < EnemyNum; idx2++)
		{
			if (idx != idx2)
			{
				if (Collision.isCollision(m_Enemy[idx]->getTrans(), m_Enemy[idx]->getRadius(), m_Enemy[idx2]->getTrans(), m_Enemy[idx2]->getRadius()))
				{
					D3DXVECTOR3 knockback = D3DXVECTOR3(m_Enemy[idx]->getTrans().x - m_Enemy[idx2]->getTrans().x, 0, m_Enemy[idx]->getTrans().z - m_Enemy[idx2]->getTrans().z);
					float L = sqrt(knockback.x*knockback.x + knockback.z*knockback.z);
					knockback.x = knockback.x / L;
					knockback.z = knockback.z / L;
				
					m_Enemy[idx]->setTrans(D3DXVECTOR3(m_Enemy[idx]->getTrans() + knockback));
					m_Enemy[idx2]->setTrans(D3DXVECTOR3(m_Enemy[idx2]->getTrans() - knockback));
				}
			}
		}
	}
	if (m_player->getflg() == true)
	{
		for (short idx = 0; idx < EnemyNum; idx++)
		{
			if (Collision.isCollision(m_player->getkou(),5.0f, m_Enemy[idx]->getTrans(), m_Enemy[idx]->getRadius()))
			{
 				m_Enemy[idx]->setLife(m_player->getDamage());
			}
 		}
		m_player->setflg();
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CMainScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(graphicsDevice(), &m_pSprite)))
	{
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}
