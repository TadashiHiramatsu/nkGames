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
	DropItem()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	~DropItem()
	{
	}

	/**
	* ������.
	* �I�[�o�[���C�h���Ă��Ȃ�.
	* �����ŌĂԕK�v����.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/16
	*
	* @param [in,out] item   If non-null, the item.
	* @param [in,out] pos    The position.
	*/
	void Start(IItem* item, D3DXVECTOR3& pos);

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
	void Render()override;

private:

	/** �A�C�e���̃X�v���C�g. */
	Sprite ItemSprite_;
	/** �A�C�e���f�[�^. */
	IItem* Item_;

};