#pragma once

struct MapChipInfoS
{
	/** モデル名. */
	string ModelName_;
	/** トランスフォーム. */
	Transform Transform_;
};

/** ファイル読み込みコード. */
enum MapChipInfoCode
{
	ModelName,  //!< モデル名
	PositionX,	//!< 位置X
	PositionY,	//!< 位置Y
	PositionZ,	//!< 位置Z
	RotationX,  //!< 回転X
	RotationY,  //!< 回転Y
	RotationZ,  //!< 回転Z
	RotationW,  //!< 回転W
	ScaleX,		//!< 拡大X
	ScaleY,		//!< 拡大Y
	ScaleZ,		//!< 拡大Z
};

/**
* マップチップクラス.
* マップクラスがこのオブジェクトを作成する.
*/
class MapChip : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	MapChip()
	{
	}

	/**
	* デストラクタ.
	*/
	~MapChip()
	{
	}

	/**
	* オーバーライドしていない初期化.
	*/
	void Start(const vector<MapChipInfoS*>& mapchipinfolist);

	/**
	* 初期化.
	*/
	void Start()override;

	/**
	* 更新.
	*/
	void Update()override;

	/**
	* 描画.
	*/
	void Render()override;

private:

	/** マップチップ情報リスト. */
	vector<MapChipInfoS*> MapChipInfoList_;

	/** スキンモデルデータ. */
	SkinModelDataHandle SkinModelData_;
	/** モデル描画クラス*/
	ModelRender ModelRender_;
	/** ワールド行列のバッファ. */
	unique_ptr<D3DXMATRIX[]> WorldMatrixBuffer_;
	/** メッシュコライダー. */
	unique_ptr<MeshCollider[]> MeshCollider_;
	/** 剛体. */
	unique_ptr<RigidBody[]> RigidBody_;

	/** 先頭ボーン行列*/
	D3DXMATRIX* RootBoneMatrix_ = nullptr;

	/** マップチップの数. */
	int NumMapChip_ = 0;

};