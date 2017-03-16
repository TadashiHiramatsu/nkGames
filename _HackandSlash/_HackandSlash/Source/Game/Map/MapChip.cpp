/**
* マップチッククラスの実装.
*/
#include"stdafx.h"
#include"MapChip.h"

#include"../GameCamera.h"
#include"../GameLight.h"

/**
* オーバーライドしていない初期化.
*
* @param[in] mapchipinfolist マップチップ情報のリスト
*/
void MapChip::Start(const vector<MapChipInfoS*>& mapchipinfolist)
{
	MapChipInfoList_ = mapchipinfolist;

	char filepath[1024];
	sprintf(filepath, "Map/%s.X", MapChipInfoList_[0]->ModelName_.c_str());

	//モデルをインスタンシングで読み込み
	SMDResources().Load(SkinModelData_, filepath, nullptr, true, MapChipInfoList_.size());

	ModelRender_.SetFogParam(ModelRender::FogFuncE::FogFuncDist, 350.0f, 600.0f, Vector4(1, 1, 1, 1));

}

/**
* 初期化.
*/
void MapChip::Start()
{

	//モデルの初期化
	ModelRender_.Load(SkinModelData_.GetBody());
	//ライトを設定
	ModelRender_.SetLight(g_GameLight->GetLight());
	//カメラを設定
	ModelRender_.SetCamera(g_MainCamera->GetCamera());

	//使わないけど登録
	ModelRender_.SetTransform(&Transform_);

	//シャドウ設定
	ModelRender_.SetShadowCasterFlag(true);
	ModelRender_.SetShadowReceiverFlag(true);

	//数を初期化
	NumMapChip_ = (int)MapChipInfoList_.size();

	//ワールド行列バッファをリセット
	WorldMatrixBuffer_.reset(new Matrix[NumMapChip_]);

	//メッシュコライダーをリセット
	MeshCollider_.reset(new MeshCollider[NumMapChip_]);
	//剛体をリセット
	RigidBody_.reset(new RigidBody[NumMapChip_]);

	int i = 0;
	for (auto& mapchipinfo : MapChipInfoList_)
	{
		mapchipinfo->Transform_.Update();

		//ワールド行列バッファにワールド行列を登録
		WorldMatrixBuffer_[i++] = mapchipinfo->Transform_.WorldMatrix_;
	}
	
	Transform_.Update();
	this->Update();

	//ルートボーン行列を取得
	RootBoneMatrix_ = SkinModelData_.GetBody()->GetRootBoneWorldMatrix();
	
	i = 0;
	for (auto& mapchipinfo : MapChipInfoList_)
	{
		//ワールド行列を作成
		Matrix world;
		world.Mul(*RootBoneMatrix_, WorldMatrixBuffer_[i]);

		//メッシュコライダーを作成
		MeshCollider_[i].Create(&ModelRender_, &world);

		//剛体情報の作成
		RigidBodyInfoS rbInfo;
		rbInfo.Collider_ = &MeshCollider_[i];
		rbInfo.Mass_ = 0;
		//剛体の作成
		RigidBody_[i].Create(rbInfo);

		//剛体登録
		Physics().AddRigidBody(&RigidBody_[i]);
		i++;
	}
}

/**
* 更新.
*/
void MapChip::Update()
{
	ModelRender_.UpdateInstancinfRenderData(WorldMatrixBuffer_.get());
	ModelRender_.Update();
}

/**
* 描画.
*/
void MapChip::Render()
{
	ModelRender_.Render();
}
