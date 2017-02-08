/**
 * @file Source\Game\Sprite\DropItem.cpp
 *
 * �h���b�v�A�C�e���N���X�̎���.
 */
#include"stdafx.h"
#include"DropItem.h"

#include"../GameCamera.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param [in,out] item   If non-null, the item.
 * @param [in,out] pos    The position.
 */
void DropItem::Start(IItem* item, D3DXVECTOR3 & pos)
{
	//�A�C�e���f�[�^���R�s�[
	Item_ = item;

	//�A�C�R���̓ǂݍ���
	ItemSprite_.Load(Item_->GetIconFilePath());
	ItemSprite_.Start();

	//�J������ݒ�
	ItemSprite_.SetCamera(g_MainCamera->GetCamera());

	//�g�����X�t�H�[����ݒ�
	ItemSprite_.SetTransform(&Transform_);

	//�|�W�V������ݒ�
	Transform_.Position_ = pos + D3DXVECTOR3(0, 0.1f, 0);

	//�傫���𒲐�
	Transform_.Scale_ = D3DXVECTOR3(0.1f, 0.1f, 1.0f);

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
void DropItem::Update()
{
	//�J�����̉�]�s����擾
	D3DXMATRIX rot = g_MainCamera->GetCamera()->GetRotationMatrix();

	//�g�����X�t�H�[���̍X�V
	Transform_.BillboardUpdate(rot);
}

/**
 * �|�X�g�G�t�F�N�g��̕`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
void DropItem::Render()
{
	//�X�v���C�g�̕\��
	ItemSprite_.Render();
}
