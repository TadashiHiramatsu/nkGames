//プリコンパイル済みヘッダー
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

//DirectX9関連のインクルード
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<XInput.h>

#ifdef _DEBUG
#include<DxErr.h>
#pragma comment(lib, "dxerr.lib")
#endif

//先にインクルード
#include"btBulletDynamicsCommon.h"
#include"BulletCollision\CollisionDispatch\btGhostObject.h"
#include"_Physics\nkCollisionAttr.h"

//自作ヘッダのインクルード
#include"nkEngine.h"
#include"nkOriginalDefine.h"

#include"_Debug/nkAssert.h"
#include"_Debug/nkLog.h"

#include"_Math\nkHash.h"
#include"_Math\nkRandom.h"
#include"_Timer\nkTime.h"

//コンポーネント
#include"_Component\nkTransform.h"
#include"_Component\nkRectTransform.h"
#include"_Component\nkCharacterController.h"

//カメラ
#include"_Graphics\nkCamera.h"

#include"_Graphics\nkPrimitive.h"
#include"_Graphics\nkTexture.h"
#include"_Graphics\nkRenderTarget.h"
#include"_Graphics\nkVertexBuffer.h"
#include"_Graphics\nkEffectManager.h"

//パーティクル
#include"_Graphics/_Particle/nkParticleEmitter.h"

//シーン
#include"_Scene\nkScene.h"
#include"_Scene\nkSceneManager.h"

//プリレンダー
#include"_Graphics\_Prerender\nkShadow.h"

//ポストエフェクト
#include"_Graphics\nkBlur.h"

//UI
#include"_Graphics\_UI\nkImage.h"
#include"_Graphics\_UI\nkTestFont.h"

//スキンモデルレンダー
#include"_Graphics\_ModelRender\nkModelRender.h"
#include"_Graphics\_ModelRender\nkAnimation.h"
#include"_Resources\nkSkinModelDataHandle.h"
#include"_Resources\nkSkinModelDataResources.h"

//ゲームオブジェクト
#include"_GameObject\nkGameObject.h"
#include"_GameObject\nkGameObjectManager.h"

//インプット
#include"_Input\nkInput.h"
#include"_Input\nkXinput.h"

//グラフィックス初期設定
#include"_Graphics\nkGraphicsConfig.h"

//シーンレンダー
#include"_Graphics\nkScreenRender.h"