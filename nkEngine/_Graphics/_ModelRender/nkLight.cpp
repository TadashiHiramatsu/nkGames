/**
 * @file _Graphics\_ModelRender\nkLight.cpp
 *
 * ライトクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkLight.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Light::Light()
	{
		//ディフューズライト方向
		DiffuseLightDirection_[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		DiffuseLightDirection_[1] = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		DiffuseLightDirection_[2] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		DiffuseLightDirection_[3] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		DiffuseLightDirection_[4] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		DiffuseLightDirection_[5] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//ディフューズライト色
		DiffuseLightColor_[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[4] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		DiffuseLightColor_[5] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		//環境光の設定
		AmbientLight_ = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
		
		//自己発光色の設定
		EmissionLightColor_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	}

}// namespace nkEngine