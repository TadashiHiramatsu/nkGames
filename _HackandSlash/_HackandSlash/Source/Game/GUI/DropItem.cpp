/**
 * @file Source\Game\Sprite\DropItem.cpp
 *
 * �h���b�v�A�C�e���N���X�̎���.
 */
#include"stdafx.h"
#include"DropItem.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param [in,out] item   If non-null, the item.
 * @param [in,out] camera If non-null, the camera.
 * @param [in,out] pos    The position.
 */
void DropItem::Start(IItem* item, Camera* camera, D3DXVECTOR3 & pos)
{
	//�A�C�e���f�[�^���R�s�[
	Item_ = item;

	//�A�C�R���̓ǂݍ���
	ItemSprite_.Load(Item_->GetIconFilePath());
	ItemSprite_.Start();

	//�J������ݒ�
	ItemSprite_.SetCamera(camera);
	Camera_ = camera;

	//�g�����X�t�H�[����ݒ�
	ItemSprite_.SetTransform(&Transform_);

	//�|�W�V������ݒ�
	Transform_.Position_ = pos + D3DXVECTOR3(0, 0.1f, 0);

	Transform_.Scale_ = D3DXVECTOR3(0.1f, 0.1f, 1);

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
	D3DXMATRIX rot = Camera_->GetRotationMatrix();

	//�g�����X�t�H�[���̍X�V
	Transform_.BillboardUpdate(rot);
}

/**
 * �|�X�g�G�t�F�N�g��̕`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
void DropItem::PostRender()
{
	//�X�v���C�g�̕\��
	ItemSprite_.Render();
}
