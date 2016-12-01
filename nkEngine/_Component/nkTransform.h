#pragma once

namespace nkEngine
{
	class Transform
	{
	public:

		//コンストラクタ
		Transform();

		//デストラクタ
		~Transform();

		//ワールド行列などの更新
		void Update();
	
	public:
		//メンバ変数(外部から見える)
		Transform* Parent; //親
		D3DXMATRIX* ParentMatrix;

		D3DXVECTOR3 Position;
		D3DXVECTOR3 Scale;
		D3DXQUATERNION Rotation;

		D3DXMATRIX LocalMatrix; //ローカルのワールド行列
		D3DXMATRIX WorldMatrix; //ワールド行列
		D3DXMATRIX WorldMatrixInv; //ワールド行列の逆行列
		D3DXMATRIX RotationMatrix; //回転行列
	};
}