#pragma once

/**
*
* ����ɑ������镐��̃N���X
*
*/
class EquipmentWeapon : public IGameObject
{
public:

	//�R���X�g���N�^
	EquipmentWeapon()
	{
	}
	
	//�f�X�g���N�^
	~EquipmentWeapon()
	{
	}

	//������
	void Start(ModelRender& parent);
	//�X�V
	void Update()override;
	//�`��
	void Render()override;

	//���f�������_�[�N���X�̎擾
	ModelRender& GetModelRender()
	{
		return ModelRender_;
	}

private:

	/** ���f�������_�����O�N���X. */
	ModelRender ModelRender_;
	/** ���C�g�N���X. */
	Light Light_;

	/** �@���}�b�v. */
	Texture Normal_;
	/** �X�y�L�����}�b�v. */
	Texture Specular_;

};