#pragma once

#define		r_cast		reinterpret_cast
#define		s_cast		static_cast
#define		c_cast		const_cast

#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=nullptr; } }
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=nullptr; } }

#define WIN32_LEAN_AND_MEAN // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B

static const float GAME_DELTA_TIME = 1.0f / 60.0f; //1�t���[���̌o�ߎ���(�P��:�b)�B�Œ�FPS
