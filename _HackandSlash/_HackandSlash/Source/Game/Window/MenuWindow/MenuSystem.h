/**
* ���j���[�V�X�e���N���X�̒�`.
*/
#pragma once

#include"MenuBar.h"

#include"Inventory/InventoryWindow.h"
#include"Option\OptionWindow.h"

#include"../../Player/Player.h"

/**
* ���j���[�V�X�e���N���X.
*/
class MenuSystem : public IGameObject
{
private:

	/** �E�B���h�E�̏��. */
	enum WindowStateE
	{
		WindowBegin = 0,			//!< �擪.
		Inventory = WindowBegin,	//!< �����i.
		Option,						//!< �ݒ�.
		WindowEnd = Option,			//!< �I�[.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	MenuSystem()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~MenuSystem()
	{
	}

	/** 
	* ������.
	*/
	void Start(Player* player);

	/** 
	* �X�V.
	*/
	void Update()override;
	
	/**
	* �`��.
	*/
	void PostRender()override;

	/**
	* �L���t���O�̎擾.
	*/
	bool GetEffectiveness() const
	{
		return isEffectiveness_;
	}

private:

	/** �L���t���O. */
	bool isEffectiveness_ = false;

	/** ���j���[�o�[. */
	MenuBar MenuBar_;

	Image SelectImage_;
	RectTransform SelectRT_;

	/** �E�B���h�E�̐�. */
	static const int WINDOW_NUM = 2;

	/** �E�B���h�E�̏��. */
	int WindowState_ = WindowStateE::Inventory;

	/** �E�B���h�E. */
	unique_ptr<IMenuWindow> IMenuWindow_[WINDOW_NUM];

};

extern MenuSystem* g_MenuSystem;