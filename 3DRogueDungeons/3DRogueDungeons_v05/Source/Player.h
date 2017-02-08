/***********************************************************************/
/*! @file  Player.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"3DCharacter.h"
#include"camera.h"
#include"Input.h"

class CPlayer :public C3DCharacter
{
public:
	void Initialize(CDungeon*);
	void Updata();
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval true 
	 *  @retval false 
	 */
	/***********************************************************************/
	bool getflg(){ return flg; }
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval void
	 */
	/***********************************************************************/
	void setflg(){ flg = false; }
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval D3DXVECTOR3 
	 */
	/***********************************************************************/
	D3DXVECTOR3 getkou(){ return D3DXVECTOR3(vec3Trans.x + (vec3Front.x*15), 30, vec3Trans.z + (vec3Front.z*15) ); }
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval void
	 */
	/***********************************************************************/
	void setEnemyIT(){ EnemyI=true; }
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval void
	 */
	/***********************************************************************/
	void setEnemyIF(){ EnemyI = false; }
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval true 
	 *  @retval false 
	 */
	/***********************************************************************/
	bool getEnemyI(){ return EnemyI; }
protected:
	CCamera m_camesa;
	bool flg = false;
	bool Key = false;
	bool Key2 = false;
	bool EnemyI = false;
	float cameras;
};