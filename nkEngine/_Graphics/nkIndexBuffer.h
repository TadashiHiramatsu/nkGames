#pragma once

namespace nkEngine
{
	enum EIndexFormat
	{
		eIndexFormat16 = D3DFMT_INDEX16, //16bitインデックス
		eIndexFormat32 = D3DFMT_INDEX32, //32bitインデックス
	};
	class CIndexBuffer
	{
	public:
		//コンストラクタ
		CIndexBuffer();
		
		//デストラクタ
		~CIndexBuffer();

		//インデックスバッファの作成
		// param[in] インデックスの数
		// param[in] インデックスバッファのフォーマット
		// param[in] ソースインデックスバッファ
		void Create(int _IndexNum, EIndexFormat _Format, const void* _pSrcIndexBuffer);

		//インデックスバッファの解放
		void Release();

		//インデックスバッファの取得
		IDirect3DIndexBuffer9* GetBody()
		{
			return pIndexBuffer;
		}

	private:
		//インデックスバッファ
		IDirect3DIndexBuffer9* pIndexBuffer;
	};
}