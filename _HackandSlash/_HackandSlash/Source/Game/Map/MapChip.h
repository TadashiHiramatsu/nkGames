#pragma once

struct SMapChipInfo
{
	const char* ModelName; //���f��
	D3DXVECTOR3 Pos; //���W
	D3DXQUATERNION Rot; //��]
	D3DXVECTOR3 Scale; //�g��
};

class MapChip : public IGameObject
{

};