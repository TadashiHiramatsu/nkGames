#include"nkEngine/nkstdafx.h"
#include"nkTestFont.h"

namespace nkEngine
{
	TestFont::TestFont():
		pFont(nullptr)
	{
	}

	TestFont::~TestFont()
	{
	}

	void TestFont::Create(int _Height,int _Width, FontWeights _Weights)
	{
		D3DXCreateFont(
			Engine().GetDevice(),			// デバイス
			_Height,						// 高さ
			_Width,							// 幅
			_Weights,						// フォントの太さ 普通
			NULL,							// 下線
			FALSE,							// 斜体
			SHIFTJIS_CHARSET,				// 文字セット
			OUT_DEFAULT_PRECIS,				// 出力制度は普通
			PROOF_QUALITY,					// 文字品質を重視
			FIXED_PITCH | FF_SCRIPT,		// ピッチとファミリ
			TEXT("ＭＳ　Ｐゴシック"),		// フォント名
			&pFont);						// ID3DXFontポインタ
	}

	void TestFont::Render(const char * _Text, int _Num, D3DXVECTOR2 _Pos)
	{
		RECT rc = {
			_Pos.x,		// 左上のx座標
			_Pos.y,		// 左上のy座標
			Engine().GetFrameW(),	// 右下のx座標
			Engine().GetFrameH()		// 右下のy座標
		};

		char num[10];
		sprintf_s(num, "%d", _Num);

		char str[30] = {0};
		strcat_s(str, _Text);
		strcat_s(str, " : ");
		strcat_s(str, num);

		// 描画
		pFont->DrawText(
			NULL,					// NULL
			str,					// 描画テキスト
			-1,						// 全て表示
			&rc,						// 表示範囲
			DT_LEFT,					// 左寄せ
			D3DCOLOR_XRGB(0, 0, 0)
		);
	}

	void TestFont::Render(const char* _Text, D3DXVECTOR2 _Pos)
	{
		RECT rc = {
			_Pos.x,		// 左上のx座標
			_Pos.y,		// 左上のy座標
			Engine().GetFrameW(),	// 右下のx座標
			Engine().GetFrameH()		// 右下のy座標
		};

		// 描画
		pFont->DrawText(
			NULL,					// NULL
			_Text,					// 描画テキスト
			-1,						// 全て表示
			&rc,						// 表示範囲
			DT_LEFT,					// 左寄せ
			D3DCOLOR_XRGB(0, 0, 0)
		);
	}

	void TestFont::Render(int _Text, D3DXVECTOR2 _Pos)
	{
		RECT rc = {
			_Pos.x,		// 左上のx座標
			_Pos.y,		// 左上のy座標
			Engine().GetFrameW(),	// 右下のx座標
			Engine().GetFrameH()		// 右下のy座標
		};

		char text[10];
		sprintf_s(text, "%d", _Text);

		// 描画
		pFont->DrawText(
			NULL,					// NULL
			text,					// 描画テキスト
			-1,						// 全て表示
			&rc,						// 表示範囲
			DT_LEFT,					// 左寄せ
			D3DCOLOR_XRGB(0, 0, 0)
		);
	}

	void TestFont::Release()
	{
		// フォント開放
		pFont->Release();
		pFont = NULL;
	}
}