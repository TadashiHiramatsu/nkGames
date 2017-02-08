/***********************************************************************/
/*! @file  Dungeon.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<vector>
#include"IncludeManagers.h"

#include"3DObject.h"

#define MIN_ROOM_WIDTH 8
#define MIN_ROOM_HEIGHT 8
#define MAP_WIDTH 30
#define MAP_HEIGHT 20
struct RoomInfo{
	int baseX;
	int baseY;
	int width;
	int height;
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval  
	 */
	/***********************************************************************/
	RoomInfo(){
		baseX = baseY = 0;
		width = height = 0;
	}
};

struct Space{
	int baseX;
	int baseY;
	int width;
	int height;
	RoomInfo room;
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval  
	 */
	/***********************************************************************/
	Space(){
		baseX = baseY = 0;
		width = height = 0;
	}
};

//mapID
enum MapID {
	MAP_NOT_OBJECT =-1,
	MAP_WALL,
	MAP_ROOM,
	MAP_STAIRS,
	MAP_FLOOR,
	MAP_BOUNDARY
};


class CDungeon
{
public:
	CDungeon();
	//ƒZƒbƒ^
	void Initialize();
	void DivideX(Space&, Space&, Space&);
	void DivideY(Space&, Space&, Space&);
	void Divide(Space&);
	void MakeRoom();
	void MakeFloor();
	void MakeStairs();

	void Draw();

	D3DXVECTOR3 getroom();
	MapID getmapid(D3DXVECTOR3);
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval short 
	 */
	/***********************************************************************/
	short getroomnum(){ return roomnum; }
private:
	D3DXMATRIX World;
	D3DXMATRIX Offset;
	Space m_space;
	std::vector<Space> m_spaceVec;
	std::vector<Space>::iterator it;

	short m_map[MAP_HEIGHT][MAP_WIDTH];
	short roomnum;

	C3DObject m_Floor;
	C3DObject m_Wall;
	C3DObject m_Stairs;
};
