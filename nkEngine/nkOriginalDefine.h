#pragma once

#define		r_cast		reinterpret_cast
#define		s_cast		static_cast
#define		c_cast		const_cast

#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=nullptr; } }
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=nullptr; } }

#define WIN32_LEAN_AND_MEAN // Windows ヘッダーから使用されていない部分を除外します。

static const float GAME_DELTA_TIME = 1.0f / 60.0f; //1フレームの経過時間(単位:秒)。固定FPS
