/***********************************************************************/
/*! @file  Enemy.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"Enemy.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pDun 
 *  @param[in,out] pPla 
 *  @retval void
 */
/***********************************************************************/
void CEnemy::Initialize(CDungeon* pDun, CPlayer* pPla)
{
	C3DCharacter::Initialize(pDun);
	pPlayer = pPla;
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CEnemy::Updata()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matRot);
	if (PlayerInfer())
	{
		pPlayer->setEnemyIT();
		this->setFront(vec3Trans, pPlayer->getTrans());
		vec3Front.x *= Speed;
		vec3Front.z *= Speed;
		vec3Trans -= D3DXVECTOR3(vec3Front.x, 0.0f, vec3Front.z);
		if (WallCollision(vec3Trans))
		{
			vec3Trans += D3DXVECTOR3(vec3Front.x, 0.0f, vec3Front.z);
		}
		D3DXMatrixLookAtLH(&matRot, &pPlayer->getTrans(), &vec3Trans, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixInverse(&matRot, NULL, &matRot);
		matRot._41 = 0.0f;   // オフセットを切る（回転行列だけにしてしまう）
		matRot._42 = 0.0f;
		matRot._43 = 0.0f;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL CEnemy::PlayerInfer()
{
	CSphereCollision Collision;
	if (Collision.isCollision(vec3Trans, InferRadius, pPlayer->getTrans(), pPlayer->getRadius()))
	{
		return true;
	}
	return false;
}

