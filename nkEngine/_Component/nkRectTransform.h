#pragma once

namespace nkEngine
{
	//UI専用トランスフォーム
	class RectTransform
	{
	public:

		//アンカープリセット
		//アンカーの位置からの位置になる
		enum AnchorPreset
		{
			TopLeft,		//左上
			TopCenter,		//上中央
			TopRight,		//右上
			MiddleLeft,		//左中央
			MiddleCenter,	//中心
			MiddleRight,	//右中央
			BottomLeft,		//左下
			BottomCenter,	//下中央
			BottomRight,	//右下
			AnchorPresetNum, //数
		};



	public:

		//コンストラクタ
		RectTransform();
		//デストラクタ
		~RectTransform();

		//更新
		void Update();

		void RotationZ(float _value)
		{
			float z = D3DXToRadian(_value);
			D3DXQuaternionRotationAxis(&Rotation, &D3DXVECTOR3(0, 0, 1), z);
		}

	public:
		AnchorPreset Anchor; //アンカー初期値は中心
		D3DXVECTOR2 Position; //ポジション
		float Width; //横幅
		float Height; //立幅
		D3DXVECTOR2 Pivot; //中心
		D3DXQUATERNION Rotation; //回転		
		D3DXVECTOR2 Scale; //サイズ

	public:
		RectTransform* Parent; //親

		D3DXMATRIX WorldMatrix; //ワールド行列
		D3DXMATRIX WorldSizeOffMatrix; //ワールド行列(サイズなし)
		D3DXMATRIX TransMatrix; //平行移動行列
		D3DXMATRIX ScaleMatrix; //拡大行列
		D3DXMATRIX RotationMatrix; //回転行列

		D3DXMATRIX ProjectionMatrix; //プロジェクション行列
		D3DXMATRIX WorldProjMatrix; //ワールドプロジェクション行列
	};
}