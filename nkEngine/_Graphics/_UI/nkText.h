/**
 * @file _Graphics\_UI\nkText.h
 *
 * テストフォントクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * テキストクラス.
	 * クラス内で内部解像度のサイズに合わせているので
	 * 使用時はスクリーンサイズで計算したらOK.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Text
	{
	public:

		/** Values that represent font weights. */
		enum FontWeightE
		{
			DONTCARE	= FW_DONTCARE,
			THIN		= FW_THIN,
			EXTRALIGHT	= FW_EXTRALIGHT,
			LIGHT		= FW_LIGHT,
			NORMAL		= FW_NORMAL,
			MEDIUM		= FW_MEDIUM,
			SEMIBOLD	= FW_SEMIBOLD,
			BOLD		= FW_BOLD,
			EXTRABOLD	= FW_EXTRABOLD,
			HEAVY		= FW_HEAVY
		};

	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Text();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Text();

		/**
		 * 作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param height  The height.
		 * @param width   The width.
		 * @param weights (Optional) The weights.
		 */
		void Create(int height, int width, FontWeightE weights = FontWeightE::NORMAL);

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param text 文字.
		 * @param pos  (Optional) The position.
		 */
		void Render(const char* text);

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		void SetTransform(RectTransform* rt)
		{
			Transform_ = rt;
		}

		void SetColor(const D3DXVECTOR4& color)
		{
			Color_ = color;
		}

	private:

		/** フォント. */
		ID3DXFont* D3DFont_;
		/** スクリーンと内部解像度の倍率. */
		float Magnification = 1.0f;

		int Height_;
		int Width_;

		RectTransform* Transform_;

		D3DXVECTOR4 Color_ = D3DXVECTOR4(0, 0, 0, 255);
	};

}// namespace nkEngine