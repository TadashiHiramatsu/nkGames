/**
 * @file	nkEngine.h
 *
 * �G���W���N���X�̒�`.
 */
#pragma once

#include"_Physics\nkPhysics.h"
#include"_Sound\nkSoundEngine.h"

namespace nkEngine
{

	/**
	 * �������p�����[�^�̍\����.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct InitParamS
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		InitParamS()
		{
			memset(this, 0, sizeof(InitParamS));
			isCenter_ = true;
		}

	public:

		/** �C���X�^���X�n���h��. */
		HINSTANCE hInstance_;
		/** �X�N���[���̉���. */
		int ScreenBufferW_;
		/** �X�N���[���̍���. */
		int ScreenBufferH_;
		/** �����𑜓x�̉���. */
		int FrameBufferW_;
		/** �����𑜓x�̍���. */
		int FrameBufferH_;
		/** �Q�[���̕\����. */
		const char* GameName_;
		/** �f�X�N�g�b�v�̒��S�ɕ\�����邩. */
		bool isCenter_;

	};

	/**
	 * �G���W���N���X.
	 * �V���O���g���N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CEngine
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CEngine():
			Hwnd_(nullptr)
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CEngine()
		{
		}

	public:

		/**
		 * ������.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	initparam	�������p�����[�^.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool Init(const InitParamS& initparam);

		/**
		 * �I������.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Final();

		/**
		 * �Q�[�����[�v.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void RunGameLoop();

		/**
		 * �C���X�^���X�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	A reference to a CEngine.
		 */
		inline static CEngine& instance()
		{
			static CEngine instance;
			return instance;
		}

		/**
		 * �f�o�C�X�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the device.
		 */
		IDirect3DDevice9* GetDevice()
		{
			return D3DDevice_;
		}


		/**
		 * �n���h���̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The hwnd.
		 */
		HWND GetHWND()
		{
			return Hwnd_;
		}

		/**
		 * �������[���h�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The physics.
		 */
		CPhysics& GetPhysics()
		{
			return Physics_;
		}

		/**
		 * �t���[���̉������擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The frame w.
		 */
		int GetFrameW() 
		{
			return FrameBufferW_;
		}

		/**
		 * �t���[���̍������擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The frame h.
		 */
		int GetFrameH() 
		{
			return FrameBufferH_; 
		}

		/**
		 * �X�N���[���̉������擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The screen w.
		 */
		int GetScreenW()
		{
			return ScreenBufferW_; 
		}

		/**
		 * �X�N���[���̍������擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The screen h.
		 */
		int GetScreenH()
		{
			return ScreenBufferH_; 
		}

		/**
		* �T�E���h�G���W���̎擾.
		*/
		CSoundEngine& GetSoundEngine()
		{
			return SoundEngine_;
		}

	private:

		/**
		 * �E�B���h�E�̏�����.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	initparam	�������p�����[�^.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool InitWindow(const InitParamS& initparam);

		/**
		 * DirectX�̏�����.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	initparam	�������p�����[�^.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool InitDirectX(const InitParamS& initparam);

		/**
		 * �E�B���h�E�v���V�[�W��.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	hwnd  	Handle of the window.
		 * @param	msg   	The message.
		 * @param	wParam	The wParam field of the message.
		 * @param	lParam	The lParam field of the message.
		 *
		 * @return	A LRESULT.
		 */
		static LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:

		/** �E�B���h�E�n���h��. */
		HWND Hwnd_;
		/** �N���C�A���g�T�C�Y. */
		RECT ClientRect_;
		/** �t���[���o�b�t�@�̕��B�����𑜓x. */
		int FrameBufferW_;
		/** �t���[���o�b�t�@�̍����B�����𑜓x. */
		int FrameBufferH_;
		/** �X�N���[���o�b�t�@�̕�. */
		int ScreenBufferW_;
		/** �X�N���[���o�b�t�@�̍���. */
		int ScreenBufferH_;
		/** DirectX�I�u�W�F�N�g. */
		IDirect3D9* D3DObject_;
		/** DirectX�f�o�C�X. */
		IDirect3DDevice9* D3DDevice_;

		/** �������[���h. */
		CPhysics Physics_;

		/** �T�E���h�G���W��. */
		CSoundEngine SoundEngine_;

	};

	/**
	 * �G���W���̎擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to a CEngine.
	 */
	inline static CEngine& Engine()
	{
		return CEngine::instance();
	}

	/**
	 * �������[���h�̎擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to the CPhysics.
	 */
	inline static CPhysics& Physics()
	{
		return Engine().GetPhysics();
	}

	/**
	* �T�E���h�G���W���̎擾.
	*/
	inline static CSoundEngine& SoundEngine()
	{
		return Engine().GetSoundEngine();
	}

}// namesoace nkEngine