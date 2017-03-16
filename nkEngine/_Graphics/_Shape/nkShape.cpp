/**
 * @file _Graphics\_Shape\nkShape.cpp
 *
 * 形状の基底クラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkShape.h"

namespace nkEngine
{
	
	//スタティック変数の定義
	Light IShape::DefaultLight_;
	bool IShape::isInitDefaultLight_ = false;

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	IShape::IShape()
	{
		if (!isInitDefaultLight_) {
			//デフォルトライトの初期化。
			DefaultLight_.SetAmbientLight(Vector3(1.0f, 1.0f, 1.0f));
			isInitDefaultLight_ = true;
		}
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	IShape::~IShape()
	{
		Release();
	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	void IShape::Update()
	{
	}

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	void IShape::Render()
	{
	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	void IShape::Release()
	{
	}

}