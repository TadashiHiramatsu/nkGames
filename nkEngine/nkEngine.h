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
		int GetFrameW() { return m_frameBufferW; }
		int GetFrameH() { return m_frameBufferH; }
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
		//DirectX�I�u�W�F�N�g
		IDirect3D9* m_pD3D;
		//DirectX�f�o�C�X
		IDirect3DDevice9* m_pD3DDevice;
	};
	inline static CEngine& Engine()
	{
		return CEngine::instance();
	}
}

#endif // !_NKENGINE_