#pragma once

/** 
* �}�b�v�`�b�v�N���X�̓ǂݍ��݃f�[�^.
*/
struct MapChipInfoS
{
	/** ���f����. */
	string ModelName_;
	/** �g�����X�t�H�[��. */
	Transform Transform_;
};

/**
* �}�b�v�`�b�v�N���X.
* �}�b�v�N���X�����̃I�u�W�F�N�g���쐬����.
*/
class MapChip : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	MapChip()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~MapChip()
	{
	}

	/**
	* �I�[�o�[���C�h���Ă��Ȃ�������.
	*/
	void Start(const vector<MapChipInfoS*>& mapchipinfolist);

	/**
	* ������.
	*/
	void Start()override;

	/**
	* �X�V.
	*/
	void Update()override;

	/**
	* �`��.
	*/
	void Render()override;

private:

	/** �}�b�v�`�b�v��񃊃X�g. */
	vector<MapChipInfoS*> MapChipInfoList_;

	/** �X�L�����f���f�[�^. */
	SkinModelDataHandle SkinModelData_;
	/** ���f���`��N���X*/
	ModelRender ModelRender_;
	/** ���[���h�s��̃o�b�t�@. */
	unique_ptr<D3DXMATRIX[]> WorldMatrixBuffer_;
	/** ���b�V���R���C�_�[. */
	unique_ptr<MeshCollider[]> MeshCollider_;
	/** ����. */
	unique_ptr<RigidBody[]> RigidBody_;

	/** �擪�{�[���s��*/
	D3DXMATRIX* RootBoneMatrix_ = nullptr;

	/** �}�b�v�`�b�v�̐�. */
	int NumMapChip_ = 0;

};