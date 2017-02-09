/**
 * @file _Graphics\_UI\nkText.cpp
 *
 * テストフォントクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkText.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Text::Text() :
		D3DFont_(nullptr)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Text::~Text()
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
	void Text::Create(int height,int width, FontWeightE weights)
	{

		//倍率を計算
		Magnification = Engine().GetFrameH() / Engine().GetScreenH();

		Format_ = FormatE::Center;

		Height_ = height;
		Width_ = width;

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
			TEXT("ＭＳ　Ｐ明朝"),			// フォント名
			&D3DFont_
		);						// ID3DXFontポインタ
	
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
	void Text::Render(const char* text)
	{

		D3DXVECTOR2 pos;
		pos.x = Transform_->WorldMatrix_._41;
		pos.y = Transform_->WorldMatrix_._42;

		pos.x += Engine().GetScreenW() / 2;
		pos.y = (Engine().GetScreenH() / 2) - pos.y;

		pos.y += Transform_->Position_.y * 2;

		int num = strlen(text);

		int idx = 0;

		switch (Format_)
		{
		case nkEngine::Text::Left:
			idx = 0;
			break;
		case nkEngine::Text::Center:
			idx = num / 2 * Width_;
			break;
		default:
			idx = 0;
			break;
		}

		
		RECT rc =
		{
			(pos.x - idx) * Magnification,		// 左上のx座標
			(pos.y) * Magnification,		// 左上のy座標
			(pos.x + (Width_ * num) - idx) * Magnification,		// 右下のx座標
			(pos.y  + Height_) * Magnification		// 右下のy座標
		};

		// 描画
		D3DFont_->DrawText(
			NULL,					// NULL
			text,					// 描画テキスト
			-1,						// 全て表示
			&rc,						// 表示範囲
			DT_LEFT,					// 左寄せ
			D3DCOLOR_RGBA((int)Color_.x, (int)Color_.y, (int)Color_.z, (int)Color_.w)
		);
	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Text::Release()
	{
		// フォント開放
		SAFE_RELEASE(D3DFont_);
	}

}// namespace nkEngine