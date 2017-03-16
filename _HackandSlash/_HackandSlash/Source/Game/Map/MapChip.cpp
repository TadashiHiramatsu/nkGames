/**
* �}�b�v�`�b�N�N���X�̎���.
*/
#include"stdafx.h"
#include"MapChip.h"

#include"../GameCamera.h"
#include"../GameLight.h"

/**
* �I�[�o�[���C�h���Ă��Ȃ�������.
*
* @param[in] mapchipinfolist �}�b�v�`�b�v���̃��X�g
*/
void MapChip::Start(const vector<MapChipInfoS*>& mapchipinfolist)
{
	MapChipInfoList_ = mapchipinfolist;

	char filepath[1024];
	sprintf(filepath, "Map/%s.X", MapChipInfoList_[0]->ModelName_.c_str());

	//���f�����C���X�^���V���O�œǂݍ���
	SMDResources().Load(SkinModelData_, filepath, nullptr, true, MapChipInfoList_.size());

	ModelRender_.SetFogParam(ModelRender::FogFuncE::FogFuncDist, 350.0f, 600.0f, Vector4(1, 1, 1, 1));

}

/**
* ������.
*/
void MapChip::Start()
{

	//���f���̏�����
	ModelRender_.Load(SkinModelData_.GetBody());
	//���C�g��ݒ�
	ModelRender_.SetLight(g_GameLight->GetLight());
	//�J������ݒ�
	ModelRender_.SetCamera(g_MainCamera->GetCamera());

	//�g��Ȃ����Ǔo�^
	ModelRender_.SetTransform(&Transform_);

	//�V���h�E�ݒ�
	ModelRender_.SetShadowCasterFlag(true);
	ModelRender_.SetShadowReceiverFlag(true);

	//����������
	NumMapChip_ = (int)MapChipInfoList_.size();

	//���[���h�s��o�b�t�@�����Z�b�g
	WorldMatrixBuffer_.reset(new Matrix[NumMapChip_]);

	//���b�V���R���C�_�[�����Z�b�g
	MeshCollider_.reset(new MeshCollider[NumMapChip_]);
	//���̂����Z�b�g
	RigidBody_.reset(new RigidBody[NumMapChip_]);

	int i = 0;
	for (auto& mapchipinfo : MapChipInfoList_)
	{
		mapchipinfo->Transform_.Update();

		//���[���h�s��o�b�t�@�Ƀ��[���h�s���o�^
		WorldMatrixBuffer_[i++] = mapchipinfo->Transform_.WorldMatrix_;
	}
	
	Transform_.Update();
	this->Update();

	//���[�g�{�[���s����擾
	RootBoneMatrix_ = SkinModelData_.GetBody()->GetRootBoneWorldMatrix();
	
	i = 0;
	for (auto& mapchipinfo : MapChipInfoList_)
	{
		//���[���h�s����쐬
		Matrix world;
		world.Mul(*RootBoneMatrix_, WorldMatrixBuffer_[i]);

		//���b�V���R���C�_�[���쐬
		MeshCollider_[i].Create(&ModelRender_, &world);

		//���̏��̍쐬
		RigidBodyInfoS rbInfo;
		rbInfo.Collider_ = &MeshCollider_[i];
		rbInfo.Mass_ = 0;
		//���̂̍쐬
		RigidBody_[i].Create(rbInfo);

		//���̓o�^
		Physics().AddRigidBody(&RigidBody_[i]);
		i++;
	}
}

/**
* �X�V.
*/
void MapChip::Update()
{
	ModelRender_.UpdateInstancinfRenderData(WorldMatrixBuffer_.get());
	ModelRender_.Update();
}

/**
* �`��.
*/
void MapChip::Render()
{
	ModelRender_.Render();
}
