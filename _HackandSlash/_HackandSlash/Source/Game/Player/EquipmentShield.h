#pragma once

/**
*
* ����ɑ������鏂�̃N���X
*
*/
class EquipmentShield : public IGameObject
{
public:

	//�R���X�g���N�^
	EquipmentShield()
	{
	}

	//�f�X�g���N�^
	~EquipmentShield()
	{
	}

	//������
	void Start(ModelRender& parent);
	//�X�V
	void Update()override;
	//�`��
	void Render()override;

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