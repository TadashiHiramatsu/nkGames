/***********************************************************************/
/*! @file  MainScene.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"IncludeManagers.h"

#include"Scene.h"
#include"SceneManager.h"

#include"Dungeon.h"
#include"Player.h"

#include"SceCommon.h"
#include<vector>

#include"Enemy.h"
#include"EnemyInclude.h"

#include"LifeGage.h"

class CSceneManager;

class CMainScene :public CScene
{
public:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] name 
	 *  @retval  
	 */
	/***********************************************************************/
	CMainScene(const string& name) : CScene(name){ }
	void Initialize();
	void Update();
	void Draw();
	void setEnemy();
	void Cllision();

	HRESULT CreateSprite();	///<�X�v���C�g�����֐�
private:
	CDungeon* m_Dun;
	CPlayer* m_player;

	vector<CEnemy*> m_Enemy;
	vector<CEnemy*>::iterator it;
	short m_map[MAP_HEIGHT][MAP_WIDTH];
	short EnemyNum;

	D3DLIGHT9 light1;

	D3DXMATRIX World;          ///< �����̃��[���h�ϊ��s��
	D3DXMATRIX Persp;   ///< �ˉe�ϊ��s��

	LPD3DXSPRITE m_pSprite;	///<�X�v���C�g
	CLifeGage* Life;

	short num=0;
	bool flg = false;
};