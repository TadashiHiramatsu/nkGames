/**
 * @file Source\Game\Map\Ground.h
 *
 * �O���E���h�N���X�̒�`.
 */
#pragma once

/**
 * �O���E���h�N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class Ground : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Ground();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~Ground();

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Update()override;

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Render()override;

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Release()override;

private:

	/** ���f�������_�[. */
	ModelRender ModelRender_;
	/** ���C�g. */
	Light Light_;


	/** ����. */
	RigidBody RigidBody_;
	/** ���b�V���`��̃R���C�_�[. */
	MeshCollider MeshCollider_;

	/** ���[���h�s��̃|�C���^. */
	D3DXMATRIX* WorldMatrix_;

	/** �@���}�b�v. */
	Texture Normal_;
	/** �X�y�L�����}�b�v. */
	Texture Specular_;

};