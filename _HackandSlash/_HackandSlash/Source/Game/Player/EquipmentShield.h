#pragma once

/**
*
* 左手に装備する盾のクラス
*
*/
class EquipmentShield : public IGameObject
{
public:

	//コンストラクタ
	EquipmentShield()
	{
	}

	//デストラクタ
	~EquipmentShield()
	{
	}

	//初期化
	void Start(ModelRender& parent);
	//更新
	void Update()override;
	//描画
	void Render()override;

private:

	/** モデルレンダリングクラス. */
	ModelRender ModelRender_;
	/** ライトクラス. */
	Light Light_;

	/** 法線マップ. */
	Texture Normal_;
	/** スペキュラマップ. */
	Texture Specular_;

};