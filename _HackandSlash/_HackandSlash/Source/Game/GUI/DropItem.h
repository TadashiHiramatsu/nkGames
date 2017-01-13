/**
 * @file Source\Game\Sprite\DropItem.h
 *
 * �h���b�v�A�C�e���N���X�̒�`.
 */
#pragma once

#include"../Item/IItem.h"

/**
 * �h���b�v�A�C�e���N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
class DropItem : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	DropItem();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	~DropItem();

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void Start(IItem* item, Camera* camera, D3DXVECTOR3& pos);

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void Update()override;

	/**
	 * �|�X�g�G�t�F�N�g��̕`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void PostRender()override;

private:

	/** �A�C�e���̃X�v���C�g. */
	Sprite ItemSprite_;
	/** �A�C�e���f�[�^. */
	IItem* Item_;

};