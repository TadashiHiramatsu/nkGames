#pragma once

#include"MenuBar.h"

#include"Inventory/Inventory.h"
#include"../../Player/Player.h"

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
	void Start(Player* player);

	//�X�V
	void Update()override;
	
	//�`��
	void PostRender()override;

	bool GetEffectiveness()
	{
		return isEffectiveness_;
	}

private:

	/** �L���t���O. */
	bool isEffectiveness_ = false;

	/** ���j���[�o�[. */
	MenuBar MenuBar_;

	/** �E�B���h�E*/
	unique_ptr<IMenuWindow> IMenuWindow_;

};

extern MenuSystem* g_MenuSystem;