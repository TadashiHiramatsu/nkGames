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
		DiffuseLightDirection_[0] = Vector3::Zero;
		DiffuseLightDirection_[1] = Vector3::Zero;
		DiffuseLightDirection_[2] = Vector3::Zero;
		DiffuseLightDirection_[3] = Vector3::Zero;
		DiffuseLightDirection_[4] = Vector3::Zero;
		DiffuseLightDirection_[5] = Vector3::Zero;

		//ディフューズライト色
		DiffuseLightColor_[0] = Vector4::Zero;
		DiffuseLightColor_[1] = Vector4::Zero;
		DiffuseLightColor_[2] = Vector4::Zero;
		DiffuseLightColor_[3] = Vector4::Zero;
		DiffuseLightColor_[4] = Vector4::Zero;
		DiffuseLightColor_[5] = Vector4::Zero;

		//環境光の設定
		AmbientLight_ = Vector3(0.2f, 0.2f, 0.2f);
		
		//自己発光色の設定
		EmissionLightColor_ = Vector3::Zero;
	
	}

}// namespace nkEngine