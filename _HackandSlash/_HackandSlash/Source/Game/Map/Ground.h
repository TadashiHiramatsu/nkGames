/**
 * @file Source\Game\Map\Ground.h
 *
 * グラウンドクラスの定義.
 */
#pragma once

/**
 * グラウンドクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class Ground : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Ground();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~Ground();

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Update()override;

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Render()override;

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Release()override;

private:

	/** モデルレンダー. */
	ModelRender ModelRender_;
	/** ライト. */
	Light Light_;


	/** 剛体. */
	RigidBody RigidBody_;
	/** メッシュ形状のコライダー. */
	MeshCollider MeshCollider_;

	/** ワールド行列のポインタ. */
	D3DXMATRIX* WorldMatrix_;

	/** 法線マップ. */
	Texture Normal_;
	/** スペキュラマップ. */
	Texture Specular_;

};