//�v���R���p�C���ς݃w�b�_�[
#pragma once

#include<SDKDDKVer.h>
#include<Windows.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory>
#include<memory.h>
#include<tchar.h>
#include<stdio.h>
#include<stdarg.h>
#include<map>
#include<vector>
#include<list>

using namespace std;

//DirectX9�֘A�̃C���N���[�h
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<XInput.h>

#ifdef _DEBUG
#include<DxErr.h>
#pragma comment(lib, "dxerr.lib")
#endif

//��ɃC���N���[�h
#include"btBulletDynamicsCommon.h"
#include"BulletCollision\CollisionDispatch\btGhostObject.h"
#include"_Physics\nkCollisionAttr.h"

//����w�b�_�̃C���N���[�h
#include"nkEngine.h"
#include"nkOriginalDefine.h"

#include"_Debug/nkAssert.h"
#include"_Debug/nkLog.h"

#include"_Math\nkHash.h"
#include"_Math\nkRandom.h"
#include"_Timer\nkTime.h"

//�R���|�[�l���g
#include"_Component\nkTransform.h"
#include"_Component\nkRectTransform.h"
#include"_Component\nkCharacterController.h"

//�J����
#include"_Graphics\nkCamera.h"

#include"_Graphics\nkPrimitive.h"
#include"_Graphics\nkTexture.h"
#include"_Graphics\nkRenderTarget.h"
#include"_Graphics\nkVertexBuffer.h"
#include"_Graphics\nkEffectManager.h"

//�p�[�e�B�N��
#include"_Graphics/_Particle/nkParticleEmitter.h"

//�V�[��
#include"_Scene\nkScene.h"
#include"_Scene\nkSceneManager.h"

//�v�������_�[
#include"_Graphics\_Prerender\nkShadow.h"

//�|�X�g�G�t�F�N�g
#include"_Graphics\nkBlur.h"

//UI
#include"_Graphics\_UI\nkImage.h"
#include"_Graphics\_UI\nkTestFont.h"

//�X�L�����f�������_�[
#include"_Graphics\_ModelRender\nkModelRender.h"
#include"_Graphics\_ModelRender\nkAnimation.h"
#include"_Resources\nkSkinModelDataHandle.h"
#include"_Resources\nkSkinModelDataResources.h"

//�Q�[���I�u�W�F�N�g
#include"_GameObject\nkGameObject.h"
#include"_GameObject\nkGameObjectManager.h"

//�C���v�b�g
#include"_Input\nkInput.h"
#include"_Input\nkXinput.h"

//�O���t�B�b�N�X�����ݒ�
#include"_Graphics\nkGraphicsConfig.h"

//�V�[�������_�[
#include"_Graphics\nkScreenRender.h"