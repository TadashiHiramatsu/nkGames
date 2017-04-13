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

#include"Enemy\Spawn\EnemySpawnManager.h"

#include"../Common/SceneEffect/Fade.h"

#include"Boss/Warlock/Boss_Warlock.h"


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

	//�A�C�e���f�[�^�̃��[�h
	ItemDataResource().Load();

	//�R���W�������[���h�̍쐬
	g_CollisionWorld = NewGO<CollisionWorld>();
	
	//���C���J�����̍쐬
	g_MainCamera = NewGO<GameCamera>(1);

	//�Q�[�����C�g�̏�����
	g_GameLight = new GameLight();
	g_GameLight->Start();

	//�n�ʍ쐬
	NewGO<Ground>();
	//�}�b�v�쐬
	NewGO<Map>();
	//�X�J�C�{�b�N�X
	Skybox* skybox = NewGO<Skybox>();

	//�v���C���[�̍쐬
	Player* player = NewGO<Player>();

	//�Q�[���J�����Ƀv���C���[��ݒ�
	g_MainCamera->SetPlayer(player);
	
	//�X�J�C�{�b�N�X�Ƀv���C���[�̃|�C���^��ݒ�.
	skybox->SetPlayer(player);

	//�G�l�~�[�X�|�i�[�N���X�̏�����
	EnemySpawnManager* esm = NewGO<EnemySpawnManager>();
	esm->SetPlayer(player);

	//���C�t�Q�[�W
	LifeGage* lifeGage = NewGO<LifeGage>();
	lifeGage->SetPlayer(player);

	//�o���l�o�[
	ExpGage* expGage = NewGO<ExpGage>();
	expGage->SetPlayer(player);

	//UI
	g_MenuSystem = NewGO<MenuSystem>();
	g_MenuSystem->Start(player);

	//�C���x���g���̏�����
	InventoryManager().Start();

	//�h���b�v�A�C�e���}�l�[�W���̍쐬
	g_DropItemManager = NewGO<DropItemManager>(3);
	g_DropItemManager->SetPlayer(player);

	Boss_Warlock* boss = NewGO<Boss_Warlock>();
	boss->SetPlayer(player);

	SoundSource* BGM = NewGO<SoundSource>();
	BGM->InitStreaming("Game/BGM");
	BGM->Play(true);

	//�t�F�[�h�N���X�̍쐬
	Fade* fade = NewGO<Fade>(5);
	fade->StartFadeIn();
	
}
