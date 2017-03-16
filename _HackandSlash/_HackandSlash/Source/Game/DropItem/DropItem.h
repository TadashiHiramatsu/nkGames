/**
 * @file Source\Game\Sprite\DropItem.h
 *
 * �h���b�v�A�C�e���N���X�̒�`.
 */
#pragma once

#include"../Item/EquipmentItem.h"
#include"../Player/Player.h"

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
	* @param [in] player     �v���C���[�̃|�C���^
	*/
	void Start(EquipmentItem* item,const Vector3& pos, Player* player);

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

	/**
	* ���X�g�Ń\�[�g���邽�߂̊֐�.
	*/
	static bool Comp(DropItem* d1, DropItem* d2)
	{
		if (d1->toPlayerLength_ < d2->toPlayerLength_)
		{
			return true;
		}
		else
		{
			return (d1->toPlayerLength_ < d1->toPlayerLength_);
		}

		// NOTREACHED
		return false;
	}
	
	/** �v���C���[�Ƃ̋������擾. */
	float GettoPlayerLength()
	{
		return toPlayerLength_;
	}

	/** �A�C�e�����擾. */
	EquipmentItem* GetEquipmentItem()
	{
		return Item_;
	}

private:

	/** �A�C�e���̃X�v���C�g. */
	Sprite ItemSprite_;
	/** �A�C�e���f�[�^. */
	EquipmentItem* Item_;

	/** �v���C���[�̈ʒu�x�N�g���̃|�C���^. */
	Vector3* PlayerPos_;

	/** �v���C���[�Ƃ̋���. */
	float toPlayerLength_ = 0;

};