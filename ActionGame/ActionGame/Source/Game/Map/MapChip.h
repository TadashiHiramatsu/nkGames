#pragma once

struct SMapChipInfo
{
	const char* ModelName; //モデル
	D3DXVECTOR3 Pos; //座標
	D3DXQUATERNION Rot; //回転
	D3DXVECTOR3 Scale; //拡大
};

class MapChip : public IGameObject
{

};