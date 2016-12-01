#pragma once

#include"_Physics\CPhysics.h"

namespace nkEngine
{


	struct SInitParam
	{
		SInitParam()
		{
			memset(this, 0, sizeof(SInitParam));
			isCenter = true;
		}
		HINSTANCE hInstance;
		int screenW;
		int screenH;
		int frameBufferW;
		int frameBufferH;
		const char* GameName;
		bool isCenter;
	};

	//�V���O���g���̃G���W���N���X
	class CEngine
	{
	private:
		CEngine():
			m_hWnd(nullptr)
		{}
		~CEngine()
		{}
	public:
		//������
		bool Init(const SInitParam& initparam);
		//�I������
		void Final();
		//�Q�[�����[�v
		void RunGameLoop();
		//�C���X�^���X�擾
		inline static CEngine& instance()
		{
			static CEngine instance;
			return instance;
		}
		//�f�o�C�X�̎擾
		IDirect3DDevice9* GetDevice()
		{
			return m_pD3DDevice;
		}

		HWND GetHWND()
		{
			return m_hWnd;
		}

		//�������[���h�̎擾
		CPhysics& GetPhysics()
		{
			return m_Physics;
		}

		//�t���[���̕��Fx
		int GetFrameW() { return m_frameBufferW; }
		//�t���[���̍����Fy
		int GetFrameH() { return m_frameBufferH; }
		
		//�X�N���[���̕��Fx
		int GetScreenW() { return m_screenBufferW; }
		//�X�N���[���̍����Fy
		int GetScreenH() { return m_screenBufferH; }
	private:
		//�E�B���h�E�̏�����
		bool InitWindow(const SInitParam& initParam);
		//DirectX�̏�����
		bool InitDirectX(const SInitParam& initParam);
		//�E�B���h�E�v���V�[�W��
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		//�E�B���h�E�n���h��
		HWND m_hWnd;
		//�N���C�A���g�T�C�Y
		RECT m_cRect;
		//�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
		int m_frameBufferW;
		//�t���[���o�b�t�@�̍����B���ꂪ�����𑜓x�B
		int m_frameBufferH;
		//�X�N���[���o�b�t�@�̕��B
		int m_screenBufferW;
		//�X�N���[���o�b�t�@�̍����B
		int m_screenBufferH;
		//DirectX�I�u�W�F�N�g
		IDirect3D9* m_pD3D;
		//DirectX�f�o�C�X
		IDirect3DDevice9* m_pD3DDevice;
		//�������[���h
		CPhysics m_Physics;
	};
	inline static CEngine& Engine()
	{
		return CEngine::instance();
	}
	inline static CPhysics& Physics()
	{
		return CEngine::instance().GetPhysics();
	}
}

