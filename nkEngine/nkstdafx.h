//プリコンパイル済みヘッダー
#pragma once

#include <SDKDDKVer.h>
#include<Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include<stdarg.h>
#include<map>
#include<vector>
#include<list>

using namespace std;

#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<XInput.h>

#ifdef _DEBUG
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")
#endif

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。

#define		r_cast		reinterpret_cast
#define		s_cast		static_cast
#define		c_cast		const_cast

//自作ヘッダのインクルード
#include"nkEngine/nkEngine.h"
#include"nkEngine/nkOriginalDefine.h"

#include"nkEngine/_Debug/nkAssert.h"
#include"nkEngine/_Debug/nkLog.h"

#include"_Math\nkHash.h"

#include"_Graphics\nkTexture.h"
#include"_Graphics\nkRenderTarget.h"
#include"_Graphics\nkScreenRender.h"

#include"_Scene\nkScene.h"
#include"_Scene\nkSceneManager.h"

#include"_Graphics\Shadow\nkShadow.h"
#include"_Graphics\nkCamera.h"

#include"_Graphics\nkSprite.h"
#include"_Graphics\modelRender\nkSkinModel.h"
#include"_Graphics\nkVertexBuffer.h"
#include"_Graphics\nkEffectManager.h"
#include"_Graphics\modelRender\nkAnimation.h"
#include"_Graphics\nkBlur.h"

#include"_Component\nkTransform.h"
#include"_GameObject\nkGameObject.h"

#include"_Input\nkInput.h"
#include"_Input\nkXinput.h"

#include"_Graphics\nkGraphicsConfig.h"
