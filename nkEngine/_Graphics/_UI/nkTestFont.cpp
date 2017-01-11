/**
 * @file _Graphics\_UI\nkTestFont.cpp
 *
 * テストフォントクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkTestFont.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	TestFont::TestFont() :
		D3DFont_(nullptr)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	TestFont::~TestFont()
	{
	}

	/**
	 * 作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param _Height  The height.
	 * @param _Width   The width.
	 * @param _Weights The weights.
	 */
	void TestFont::Create(int height,int width, FontWeightE weights)
	{

		//倍率を計算
		Magnification = Engine().GetFrameH() / Engine().GetScreenH();

		//フォントの作成
		D3DXCreateFont(
			Engine().GetDevice(),			// デバイス
			height * Magnification,			// 高さ
			width * Magnification,			// 幅
			weights,						// フォントの太さ 普通
			NULL,							// 下線
			FALSE,							// 斜体
			SHIFTJIS_CHARSET,				// 文字セット
			OUT_DEFAULT_PRECIS,				// 出力制度は普通
			PROOF_QUALITY,					// 文字品質を重視
			FIXED_PITCH | FF_SCRIPT,		// ピッチとファミリ
			TEXT("ＭＳ　Ｐゴシック"),		// フォント名
			&D3DFont_);						// ID3DXFontポインタ
	
	}

	/**
	* 描画.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param text 文字.
	* @param num  数値.
	* @param pos  (Optional) The position.
	*/
	void TestFont::Render(const char * text, int num, D3DXVECTOR2 pos)
	{
		RECT rc =
		{
			pos.x * Magnification,		// 左上のx座標
			pos.y * Magnification,		// 左上のy座標
			Engine().GetFrameW(),		// 右下のx座標
			Engine().GetFrameH()		// 右下のy座標
		};

		char numText[10];
		sprintf_s(numText, "%d", num);

		//フォントの作成
		char str[30] = {0};
		strcat_s(str, text);
		strcat_s(str, " : ");
		strcat_s(str, numText);

		//描画
		D3DFont_->DrawText(
			NULL,					// NULL
			str,					// 描画テキスト
			-1,						// 全て表示
			&rc,						// 表示範囲
			DT_LEFT,					// 左寄せ
			D3DCOLOR_XRGB(0, 0, 0)
		);

	}

	/**
	* 描画.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param text 文字.
	* @param pos  (Optional) The position.
	*/
	void TestFont::Render(const char* text, D3DXVECTOR2 pos)
	{

		RECT rc =
		{
			pos.x * Magnification,		// 左上のx座標
			pos.y * Magnification,		// 左上のy座標
			Engine().GetFrameW(),		// 右下のx座標
			Engine().GetFrameH()		// 右下のy座標
		};

		// 描画
		D3DFont_->DrawText(
			NULL,					// NULL
			text,					// 描画テキスト
			-1,						// 全て表示
			&rc,						// 表示範囲
			DT_LEFT,					// 左寄せ
			D3DCOLOR_XRGB(0, 0, 0)
		);

	}

	/**
	* 描画.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param text 数値.
	* @param pos  (Optional) The position.
	*/
	void TestFont::Render(int text, D3DXVECTOR2 pos)
	{
		RECT rc =
		{
			pos.x * Magnification,		// 左上のx座標
			pos.y * Magnification,		// 左上のy座標
			Engine().GetFrameW(),		// 右下のx座標
			Engine().GetFrameH()		// 右下のy座標
		};

		char numText[10];
		sprintf_s(numText, "%d", text);

		// 描画
		D3DFont_->DrawText(
			NULL,					// NULL
			numText,					// 描画テキスト
			-1,						// 全て表示
			&rc,						// 表示範囲
			DT_LEFT,					// 左寄せ
			D3DCOLOR_XRGB(0, 0, 0)
		);

	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void TestFont::Release()
	{
		// フォント開放
		SAFE_RELEASE(D3DFont_);

	}

}// namespace nkEngine