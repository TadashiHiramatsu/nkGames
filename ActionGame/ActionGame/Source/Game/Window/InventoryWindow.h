#pragma once

#include"ItemSlot.h"

//GUIWindow�N���X�����A�C�e����������ݒ肵����ł���
class InventoryWindow : public IGameObject
{
public:

	//�R���X�g���N�^
	InventoryWindow();
	//�f�X�g���N�^
	~InventoryWindow();

public:

	//������
	void Start()override;
	//�X�V
	void Update()override;
	//�`��
	void Render()override;

	bool SetItem(IItem* _item);

private:
	Image IWSkin;
	RectTransform rectTransform;

	int ISlotNum;
	shared_ptr<CTexture> IFrameTex;
	vector<ItemSlot*> ISlotVec;

	bool isRender;
};

extern InventoryWindow* g_Inventory;