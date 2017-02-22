/**
 * @file	Source\Game\GameScene.cpp
 *
 * �Q�[���V�[���N���X�̎���.
 */
#include"stdafx.h"
#include"GameScene.h"

#include"AnimationEvent\CollisionWorld.h"

#include"GameCamera.h"
#include"GameLight.h"

#include"Player\Player.h"

#include"Map\Ground.h"
#include"Map\Skybox.h"
#include"Map\Map.h"

#include"HUD\LifeGage.h"
#include"HUD\ExpGage.h"

#include"Item\ItemDataResource.h"
#include"Window\MenuWindow\MenuSystem.h"

#include"DropItem\DropItemManager.h"


/** �R���W�������[���h�̃O���[�o���|�C���^. */
CollisionWorld* g_CollisionWorld = nullptr;

/** ���C���J�����̃O���[�o���|�C���^. */
GameCamera* g_MainCamera = nullptr;

/** ���j���[�V�X�e���̃O���[�o���|�C���^. */
MenuSystem* g_MenuSystem = nullptr;

/** �h���b�v�A�C�e���}�l�[�W���̃O���[�o���|�C���^. */
DropItemManager* g_DropItemManager = nullptr;

/** �Q�[�����C�g�N���X�̃O���[�o���|�C���^. */
GameLight* g_GameLight = nullptr;

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
	GraphicsConfig_.ShadowConfig_.Far_ = 40.0f;
	GraphicsConfig_.ShadowConfig_.Near_ = 2.0f;

	GraphicsConfig_.BloomConfig_.isEnable_ = true;
	GraphicsConfig_.AntiAliasingConfig_.isEnable_ = true;

	//�R���W�������[���h�̍쐬
	g_CollisionWorld = NewGO<CollisionWorld>();
	//���C���J�����̍쐬
	g_MainCamera = NewGO<GameCamera>(1);

	//�A�C�e���f�[�^�̃��[�h
	ItemDataResource().Load();

	//�Q�[�����C�g�̏�����
	g_GameLight = new GameLight();
	g_GameLight->Start();

	//�v���C���[�̍쐬
	Player* player = NewGO<Player>();

	//�Q�[���J�����Ƀv���C���[��ݒ�
	g_MainCamera->SetPlayer(player);
	
	//�n��
	NewGO<Ground>();

	//�X�J�C�{�b�N�X
	Skybox* skybox = NewGO<Skybox>();
	skybox->SetPlayer(player);

	NewGO<Map>();

	//���C�t�Q�[�W
	LifeGage* lifeGage = NewGO<LifeGage>();
	lifeGage->SetPlayer(player);

	//�o���l�o�[
	ExpGage* expGage = NewGO<ExpGage>();
	expGage->SetPlayer(player);

	//UI
	g_MenuSystem = NewGO<MenuSystem>();
	g_MenuSystem->Start(player);

	InventoryManager().Start();

	g_DropItemManager = NewGO<DropItemManager>();
	g_DropItemManager->SetPlayer(player);

}
