#include"Dungeon.h"

CDungeon::CDungeon()
{
	m_space.height = MAP_HEIGHT;
	m_space.width = MAP_WIDTH;
	m_Wall.Initialize("XFile\\Wall.x");
	m_Floor.Initialize("XFile\\Floor.x");
	m_Stairs.Initialize("XFile\\Stairs.x");
}

void CDungeon::Initialize()
{
	memset(m_map, MAP_WALL, sizeof(m_map));
	

	this->Divide(m_space);
	this->MakeRoom();
	this->MakeFloor();
	this->MakeStairs();
}
void CDungeon::DivideX(Space& t_room, Space& splited_room1, Space& splited_room2)
{
	if (t_room.width > MIN_ROOM_WIDTH * 2){
		int num = t_room.baseX + (rand() % (t_room.width - MIN_ROOM_WIDTH * 2) + MIN_ROOM_WIDTH);

		for (int i = t_room.baseY; i < t_room.baseY + t_room.height; i++)
		{
			m_map[i][num] = MAP_BOUNDARY;
		}
		splited_room1.baseX = t_room.baseX;
		splited_room1.baseY = t_room.baseY;
		splited_room1.width = num - t_room.baseX;
		splited_room1.height = t_room.height;

		splited_room2.baseX = num + 1;
		splited_room2.baseY = t_room.baseY;
		splited_room2.width = t_room.width + t_room.baseX - (num + 1);
		splited_room2.height = t_room.height;
	}
}
void CDungeon::DivideY(Space& t_room, Space& splited_room1, Space& splited_room2)
{
	if (t_room.height > MIN_ROOM_HEIGHT * 2){
		int num = t_room.baseY + (rand() % (t_room.height - MIN_ROOM_HEIGHT * 2) + MIN_ROOM_HEIGHT);

		for (int i = t_room.baseX; i < t_room.baseX + t_room.width; i++)
		{
			m_map[num][i] = MAP_BOUNDARY;
		}
		splited_room1.baseX = t_room.baseX;
		splited_room1.baseY = t_room.baseY;
		splited_room1.width = t_room.width;
		splited_room1.height = num - t_room.baseY;

		splited_room2.baseX = t_room.baseX;
		splited_room2.baseY = num + 1;
		splited_room2.width = t_room.width;
		splited_room2.height = t_room.height + t_room.baseY - (num + 1);
	}
}
void CDungeon::Divide(Space& t_room)
{
	Space splited_room1, splited_room2;
	bool flag = 0;

	if (rand() % 2 == 0){
		if (t_room.width > MIN_ROOM_WIDTH * 2){
			this->DivideX(t_room, splited_room1, splited_room2);
			flag = 1;
		}
	}
	else{
		if (t_room.height > MIN_ROOM_HEIGHT * 2){
			this->DivideY(t_room, splited_room1, splited_room2);
			flag = 1;
		}
	}

	if (flag == 1){
		this->Divide(splited_room1);
		this->Divide(splited_room2);
	}
	else{
		this->m_spaceVec.push_back(t_room);
	}
}
void CDungeon::MakeRoom()
{
	for (it = m_spaceVec.begin(); it != m_spaceVec.end(); it++)
	{
		it->room.width = rand() % (it->width - MIN_ROOM_WIDTH + 1) + MIN_ROOM_WIDTH;
		it->room.height = rand() % (it->height - MIN_ROOM_HEIGHT + 1) + MIN_ROOM_HEIGHT;
		it->room.baseX = it->baseX + (rand() % (it->width - it->room.width + 1));
		it->room.baseY = it->baseY + (rand() % (it->height - it->room.height + 1));

		for (int i = it->room.baseY; i < it->room.baseY + it->room.height; i++)
		{
			for (int j = it->room.baseX; j < it->room.baseX + it->room.width; j++)
			{
				if (i != it->room.baseY &&
					i != it->room.baseY + it->room.height - 1 &&
					j != it->room.baseX &&
					j != it->room.baseX + it->room.width - 1)
				{
					m_map[i][j] = MAP_ROOM;
					roomnum++;
				}
			}
		}
	}
}
void CDungeon::MakeFloor()
{
	//用意されたスペースすべて
	for (it = m_spaceVec.begin(); it != m_spaceVec.end(); it++)
	{
		int trailX, trailY;
		if (it->baseX > 0){
			trailY = it->room.baseY + (rand() % (it->room.height - 2) + 1);
			for (int i = it->room.baseX; i >= it->baseX - 1; i--){
				m_map[trailY][i] = MAP_FLOOR;
			}
		}
		if (it->baseX + it->width < MAP_WIDTH){
			trailX = it->room.baseX + it->room.width - 1;
			trailY = it->room.baseY + (rand() % (it->room.height - 2) + 1);
			for (int i = trailX; i <= it->baseX + it->width; i++){
				m_map[trailY][i] = MAP_FLOOR;
			}
		}
		if (it->baseY > 0){
			trailX = it->room.baseX + (rand() % (it->room.width - 2) + 1);
			for (int i = it->room.baseY; i >= it->baseY - 1; i--){
				m_map[i][trailX] = MAP_FLOOR;
			}
		}
		if (it->baseY + it->height < MAP_HEIGHT){
			trailX = it->room.baseX + (rand() % (it->room.width - 2) + 1);
			trailY = it->room.baseY + it->room.height - 1;
			for (int i = trailY; i <= it->baseY + it->height; i++){
				m_map[i][trailX] = MAP_FLOOR;
			}
		}
	}
	//縦方向
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		if (m_map[0][i] == MAP_BOUNDARY){
			for (int j = 0; m_map[j][i] == MAP_BOUNDARY; j++){
				m_map[j][i] = MAP_WALL;
			}
		}
		if (m_map[MAP_HEIGHT - 1][i] == MAP_BOUNDARY){
			for (int j = MAP_HEIGHT - 1; m_map[j][i] == MAP_BOUNDARY; j--){
				m_map[j][i] = MAP_WALL;
			}
		}
	}
	//横方向
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		if (m_map[i][0] == MAP_BOUNDARY){
			for (int j = 0; m_map[i][j] == MAP_BOUNDARY; j++){
				m_map[i][j] = MAP_WALL;
			}
		}
		if (m_map[i][MAP_WIDTH - 1] == MAP_BOUNDARY){
			for (int j = MAP_WIDTH - 1; m_map[i][j] == MAP_BOUNDARY; j--){
				m_map[i][j] = MAP_WALL;
			}
		}
	}
	for (short i = 0; i < MAP_HEIGHT; i++)
	{
		for (short j = 0; j < MAP_WIDTH; j++)
		{
			if (m_map[i][j] == MAP_BOUNDARY)
			{
				m_map[i][j] = MAP_FLOOR;
			}
		}
	}
}

void CDungeon::MakeStairs()
{
	bool f = false;
	short xi = 0, zj = 0;
	while (f==false)
	{
		xi = rand() % MAP_HEIGHT + 1;
		zj = rand() % MAP_WIDTH + 1;
		if (m_map[xi][zj] == MAP_ROOM)
		{
			if (m_map[xi - 1][zj] != MAP_FLOOR && m_map[xi + 1][zj] != MAP_FLOOR && m_map[xi][zj - 1] != MAP_FLOOR && m_map[xi][zj + 1] != MAP_FLOOR)
			{
				m_map[xi][zj] = MAP_STAIRS;
				roomnum--;
				f = true;
			}
		}
	}
}


void CDungeon::Draw()
{
	for (short j = 0, x = 0; j < MAP_HEIGHT; j++, x += 32)
	{
		for (short i = 0, z = 0; i < MAP_WIDTH; i++, z += 32)
		{
			D3DXMatrixIdentity(&World);
			D3DXMatrixTranslation(&Offset, x, 0, z);
			D3DXMatrixMultiply(&World, &World, &Offset);
			(*graphicsDevice()).SetTransform(D3DTS_WORLD, &World);
			switch (m_map[j][i])
			{
			case MAP_WALL:
				m_Wall.Draw();
				break;
			case MAP_FLOOR:
				m_Floor.Draw();
				break;
			case MAP_ROOM:
				m_Floor.Draw();
				break;
			case MAP_STAIRS:
				m_Stairs.Draw();
				break;
			default:
				break;
			}
		}
	}
}

D3DXVECTOR3 CDungeon::getroom()
{
	D3DXVECTOR3 pos;
	do
	{
		pos.x = (float)(rand() % MAP_HEIGHT);
		pos.z = (float)(rand() % MAP_WIDTH);
	} 
	while (m_map[(int)pos.x][(int)pos.z] != MAP_ROOM);
	pos.x *= 32.0f;
	pos.y = 32.0f;
	pos.z *= 32.0f;
	return pos;
}

MapID CDungeon::getmapid(D3DXVECTOR3 pos)
{
	short x = (short)(pos.x + 16.0f) / 32;
	short z = (short)(pos.z + 16.0f) / 32;
	switch (m_map[x][z])
	{
	case 0:
		return MapID::MAP_WALL;
	case 2:
		return MapID::MAP_STAIRS;
	default:
		return MapID::MAP_ROOM;
	}
}