#pragma once

#include"MenuBar.h"

#include"Inventory/Inventory.h"

class MenuSystem : public IGameObject
{
public:

	/** �R���X�g���N�^. */
	MenuSystem()
	{
	}

	/** �f�X�g���N�^. */
	~MenuSystem()
	{
	}

	//������
	void Start()override;

	//�X�V
	void Update()override;
	
	//�`��
	void PostRender()override;

private:

	/** �L���t���O. */
	bool isEffectiveness_ = false;

	/** ���j���[�o�[. */
	MenuBar MenuBar_;

	/** �E�B���h�E*/
	unique_ptr<IMenuWindow> IMenuWindow_;

};