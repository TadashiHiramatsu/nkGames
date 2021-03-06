/**
 * @file	nkEngine.h
 *
 * エンジンクラスの定義.
 */
#pragma once

#include"_Physics\nkPhysics.h"
#include"_Sound\nkSoundEngine.h"

namespace nkEngine
{

	/**
	 * 初期化パラメータの構造体.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct InitParamS
	{
	public:

		/**
		 * コンストラクタ.
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

		/** インスタンスハンドル. */
		HINSTANCE hInstance_;
		/** スクリーンの横幅. */
		int ScreenBufferW_;
		/** スクリーンの高さ. */
		int ScreenBufferH_;
		/** 内部解像度の横幅. */
		int FrameBufferW_;
		/** 内部解像度の高さ. */
		int FrameBufferH_;
		/** ゲームの表示名. */
		const char* GameName_;
		/** デスクトップの中心に表示するか. */
		bool isCenter_;

	};

	/**
	 * エンジンクラス.
	 * シングルトンクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CEngine : Noncopyable
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CEngine():
			Hwnd_(nullptr)
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CEngine()
		{
		}

	public:

		/**
		 * 初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	initparam	初期化パラメータ.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool Init(const InitParamS& initparam);

		/**
		 * 終了処理.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Final();

		/**
		 * ゲームループ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void RunGameLoop();

		/**
		 * インスタンスの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	A reference to a CEngine.
		 */
		inline static CEngine& GetInstance()
		{
			static CEngine instance;
			return instance;
		}

		/**
		 * デバイスの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the device.
		 */
		IDirect3DDevice9* GetDevice() const
		{
			return D3DDevice_;
		}


		/**
		 * ハンドルの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The hwnd.
		 */
		HWND GetHWND() const
		{
			return Hwnd_;
		}

		/**
		 * フレームの横幅を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The frame w.
		 */
		int GetFrameW() const
		{
			return FrameBufferW_;
		}

		/**
		 * フレームの高さを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The frame h.
		 */
		int GetFrameH() const
		{
			return FrameBufferH_; 
		}

		/**
		 * スクリーンの横幅を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The screen w.
		 */
		int GetScreenW() const
		{
			return ScreenBufferW_; 
		}

		/**
		 * スクリーンの高さを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The screen h.
		 */
		int GetScreenH() const
		{
			return ScreenBufferH_; 
		}

		/**
		* ゲームの終了.
		*/
		void GameExit()
		{
			isExit_ = true;
		}

	public:

		/**
		* 物理ワールドの取得.
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
		* サウンドエンジンの取得.
		*/
		CSoundEngine& GetSoundEngine()
		{
			return SoundEngine_;
		}

	private:

		/**
		 * ウィンドウの初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	initparam	初期化パラメータ.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool InitWindow(const InitParamS& initparam);

		/**
		 * DirectXの初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param	initparam	初期化パラメータ.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool InitDirectX(const InitParamS& initparam);

		/**
		 * ウィンドウプロシージャ.
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

		/** ウィンドウハンドル. */
		HWND Hwnd_;
		/** クライアントサイズ. */
		RECT ClientRect_;
		/** フレームバッファの幅。内部解像度. */
		int FrameBufferW_;
		/** フレームバッファの高さ。内部解像度. */
		int FrameBufferH_;
		/** スクリーンバッファの幅. */
		int ScreenBufferW_;
		/** スクリーンバッファの高さ. */
		int ScreenBufferH_;
		/** DirectXオブジェクト. */
		IDirect3D9* D3DObject_;
		/** DirectXデバイス. */
		IDirect3DDevice9* D3DDevice_;

		/** 物理ワールド. */
		CPhysics Physics_;

		/** サウンドエンジン. */
		CSoundEngine SoundEngine_;

		/** 終了フラグ. */
		bool isExit_ = false;

	};

	/**
	 * エンジンの取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to a CEngine.
	 */
	inline static CEngine& Engine()
	{
		return CEngine::GetInstance();
	}

	/**
	 * 物理ワールドの取得.
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
	* サウンドエンジンの取得.
	*/
	inline static CSoundEngine& SoundEngine()
	{
		return Engine().GetSoundEngine();
	}

}// namesoace nkEngine