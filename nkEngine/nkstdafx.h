/**
 * @file	nkstdafx.h
 *
 * プリコンパイル済みヘッダーの定義.
 */
#pragma once

// 既存ヘッダのインクルード
#include<SDKDDKVer.h>
#include<Windows.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory>
#include<memory.h>
#include<tchar.h>
#include<stdio.h>
#include<stdarg.h>
#include<algorithm>
#include<time.h>

//STL
#include<map>
#include<vector>
#include<list>
#include<deque>

#include<thread>

using namespace std;

// DirectX9関連のインクルード
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<XInput.h>
#include<xaudio2.h>
#include<x3daudio.h>
#include<xaudio2fx.h>

#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#include<DxErr.h>
#pragma comment(lib, "dxerr.lib")
#endif

// 先にインクルードしなければならない
// 物理エンジンのヘッダインクルード
#include"btBulletDynamicsCommon.h"
#include"BulletCollision\CollisionDispatch\btGhostObject.h"
#include"_Physics\nkCollisionAttr.h"

//ポリシーのインクルード
#include"_Policy\nkNoncopyable.h"

//自作ヘッダのインクルード
#include"nkOriginalDefine.h"

#include"_Debug/nkAssert.h"
#include"_Debug/nkLog.h"

#include"_Math\nkHash.h"
#include"_Math\nkRandom.h"
#include"_Timer\nkTime.h"

#include"_Math\nkMatrix.h"
#include"_Math\nkVector.h"

#include"nkEngine.h"

//コンポーネント
#include"_Component\nkTransform.h"
#include"_Component\nkRectTransform.h"
#include"_Component\nkCharacterController.h"

//ゲームオブジェクト
#include"_GameObject\nkGameObject.h"
#include"_GameObject\nkGameObjectManager.h"

//物理エンジン
#include"_Physics\nkPhysics.h"
#include"_Physics\nkRigidBody.h"
#include"_Physics\nkMeshCollider.h"
#include"_Physics\nkBoxCollider.h"
#include"_Physics\nkCapsuleCollider.h"
#include"_Physics\nkSphereCollider.h"

//カメラ
#include"_Graphics\nkCamera.h"
#include"_Component\nkCameraCollision.h"

#include"_Graphics\_Effect\nkEffectManager.h"

#include"_Graphics\_Shape\nkShapeVertex.h"
#include"_Graphics\nkPrimitive.h"
#include"_Graphics\nkTexture.h"
#include"_Graphics\nkRenderTarget.h"
#include"_Graphics\_Buffer\nkVertexBuffer.h"
#include"_Graphics\_Buffer\nkIndexBuffer.h"

//パーティクル
#include"_Graphics/_Particle/nkParticleEmitter.h"

//2D Object
#include"_Graphics\_2DObject\nkSprite.h"

//シーン
#include"_Scene\nkScene.h"
#include"_Scene\nkSceneManager.h"

//プリレンダー
#include"_Graphics\_Prerender\nkShadow.h"

//UI
#include"_Graphics\_UI\nkImage.h"
#include"_Graphics\_UI\nkText.h"

//スキンモデルレンダー
#include"_Graphics\_ModelRender\nkAnimation.h"
#include"_Graphics\_ModelRender\nkModelRender.h"
#include"_Resources\nkSkinModelDataHandle.h"
#include"_Resources\nkSkinModelDataResources.h"

//インプット
#include"_Input\nkInput.h"
#include"_Input\nkXinput.h"

//グラフィックス初期設定
#include"_Graphics\nkGraphicsConfig.h"

//シーンレンダー
#include"_Graphics\nkScreenRender.h"

//外部ファイル読み込み
#include"_DataLoad\nkCSVData.h"
#include"_DataLoad\Json\picojson.h"
#include"_DataLoad/Json/nkJsonData.h"

//サウンド
#include"_Sound\nkSoundSource.h"