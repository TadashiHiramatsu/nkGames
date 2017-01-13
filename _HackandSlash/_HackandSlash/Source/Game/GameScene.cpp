/**
 * @file	Source\Game\GameScene.cpp
 *
 * �Q�[���V�[���N���X�̎���.
 */
#include"stdafx.h"
#include"GameScene.h"

#include"Player\Player.h"
#include"AnimationEvent\CollisionWorld.h"
#include"GameCamera.h"
#include"Map\Ground.h"
#include"Map\Skybox.h"
#include"Monster\MonsterHabitat.h"
//#include"GUI\InventoryWindow.h"
#include"HUD\LifeGage.h"
#include"HUD\ExpGage.h"

#include"Item\ItemResource.h"

/** �R���W�������[���h. */
CollisionWorld* g_CollisionWorld = nullptr;

/** ���C���J����. */
GameCamera* g_MainCamera = nullptr;

/** �C���x���g���E�B���h�E. */
//InventoryWindow* g_Inventory = nullptr;

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void GameScene::Start()
{
	//�O���t�B�b�N�R���t�B�O�̐ݒ�
	GraphicsConfig_.ShadowConfig_.isEnable_ = true;
	GraphicsConfig_.ShadowConfig_.isSoftShadowMap_ = true;
	GraphicsConfig_.ShadowConfig_.ShadowMapW_ = 2048;
	GraphicsConfig_.ShadowConfig_.ShadowMapH_ = 2048;
	GraphicsConfig_.ShadowConfig_.Fur_ = 100.0f;

	//�R���W�������[���h�̍쐬
	g_CollisionWorld = NewGO<CollisionWorld>();
	//���C���J�����̍쐬
	g_MainCamera = NewGO<GameCamera>(1);

	//�A�C�e���f�[�^�̃��[�h
	ItemResource().Load();

	//�v���C���[�̍쐬
	Player* player = NewGO<Player>();

	//�Q�[���J�����Ƀv���C���[��ݒ�
	g_MainCamera->SetPlayer(player);
	
	//�n��
	NewGO<Ground>();

	//�X�J�C�{�b�N�X
	Skybox* skybox = NewGO<Skybox>();
	skybox->SetPlayer(player);

	//�����X�^�[�̏Z��
	MonsterHabitat* mh = NewGO<MonsterHabitat>();
	mh->SetPlayer(player);

	//UI
	//g_Inventory = NewGO<InventoryWindow>();
	
	//���C�t�Q�[�W
	LifeGage* lifeGage = NewGO<LifeGage>();
	lifeGage->SetPlayer(player);
	//�o���l�o�[
	ExpGage* expGage = NewGO<ExpGage>();
	expGage->SetPlayer(player);

}
