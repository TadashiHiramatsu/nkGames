#ifndef _NKENGINE_
#define _NKENGINE_

namespace nkEngine
{
	struct SInitParam
	{
		SInitParam()
		{
			memset(this, 0, sizeof(SInitParam));
		}
		HINSTANCE hInstance;
		int screenW;
		int screenH;
		int frameBufferW;
		int frameBufferH;
		const char* GameName;
	};

	//シングルトンのエンジンクラス
	class CEngine
	{
	private:
		CEngine():
			m_hWnd(nullptr)
		{}
		~CEngine()
		{}
	public:
		//初期化
		bool Init(const SInitParam& initparam);
		//終了処理
		void Final();
		//ゲームループ
		void RunGameLoop();
		//インスタンス取得
		inline static CEngine& instance()
		{
			static CEngine instance;
			return instance;
		}
		//デバイスの取得
		IDirect3DDevice9* GetDevice()
		{
			return m_pD3DDevice;
		}
		int GetFrameW() { return m_frameBufferW; }
		int GetFrameH() { return m_frameBufferH; }
	private:
		//ウィンドウの初期化
		bool InitWindow(const SInitParam& initParam);
		//DirectXの初期化
		bool InitDirectX(const SInitParam& initParam);
		//ウィンドウプロシージャ
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		//ウィンドウハンドル
		HWND m_hWnd;
		//クライアントサイズ
		RECT m_cRect;
		//フレームバッファの幅。これが内部解像度。
		int m_frameBufferW;
		//フレームバッファの高さ。これが内部解像度。
		int m_frameBufferH;
		//DirectXオブジェクト
		IDirect3D9* m_pD3D;
		//DirectXデバイス
		IDirect3DDevice9* m_pD3DDevice;
	};
	inline static CEngine& Engine()
	{
		return CEngine::instance();
	}
}

#endif // !_NKENGINE_