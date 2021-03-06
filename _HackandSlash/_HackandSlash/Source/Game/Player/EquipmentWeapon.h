#pragma once

/**
*
* 左手に装備する武器のクラス
*
*/
class EquipmentWeapon : public IGameObject
{
public:

	//コンストラクタ
	EquipmentWeapon()
	{
	}
	
	//デストラクタ
	~EquipmentWeapon()
	{
	}

	//初期化
	void Start(ModelRender& parent);
	//更新
	void Update()override;
	//描画
	void Render()override;

	//モデルレンダークラスの取得
	ModelRender& GetModelRender()
	{
		return ModelRender_;
	}

private:

	/** モデルレンダリングクラス. */
	ModelRender ModelRender_;

	/** 法線マップ. */
	Texture Normal_;
	/** スペキュラマップ. */
	Texture Specular_;

};