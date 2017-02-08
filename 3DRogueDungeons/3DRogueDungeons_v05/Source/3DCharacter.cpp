/***********************************************************************/
/*! @file  3DCharacter.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"3DCharacter.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pDun 
 *  @retval void
 */
/***********************************************************************/
void C3DCharacter::Initialize(CDungeon* pDun)
{
	vec3Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vec3Trans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vec3Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	setDD(pDun);
	setTrans(DD->getroom());
	C3DData::Initialize();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void C3DCharacter::Draw()
{
	D3DXMatrixScaling(&matScale, vec3Scale.x, vec3Scale.y, vec3Scale.z);
	D3DXMatrixTranslation(&matTrans, vec3Trans.x, vec3Trans.y, vec3Trans.z);
	matWorld = matWorld * matScale * matRot * matTrans;
	(*graphicsDevice()).SetTransform(D3DTS_WORLD, &matWorld);
	C3DData::Draw();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pos 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL C3DCharacter::WallCollision(D3DXVECTOR3 pos)
{
	if (DD->getmapid(pos) == MapID::MAP_WALL)
	{
		return true;
	}
	return false;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] APos 
 *  @param[in,out] BPos 
 *  @retval void
 */
/***********************************************************************/
void C3DCharacter::setFront(D3DXVECTOR3 APos, D3DXVECTOR3 BPos)
{
	vec3Front.x = APos.x - BPos.x;
	vec3Front.y = 0.0f;
	vec3Front.z = APos.z - BPos.z;
	L = sqrt(vec3Front.x*vec3Front.x + vec3Front.z*vec3Front.z);
	vec3Front.x = vec3Front.x / L;
	vec3Front.z = vec3Front.z / L;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] trans 
 *  @retval void
 */
/***********************************************************************/
void C3DCharacter::setTrans(D3DXVECTOR3 trans)
{
	vec3Trans = D3DXVECTOR3(trans);
}