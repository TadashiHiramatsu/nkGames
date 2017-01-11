/**
 * @file _Graphics\_UI\nkTestFont.h
 *
 * テストフォントクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * テストフォントクラス.
	 * クラス内で内部解像度のサイズに合わせているので
	 * 使用時はスクリーンサイズで計算したらOK.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class TestFont
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
		TestFont();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~TestFont();

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
		 * @param num  数値.
		 * @param pos  (Optional) The position.
		 */
		void Render(const char* text, int num, D3DXVECTOR2 pos = D3DXVECTOR2(0, 0));

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param text 文字.
		 * @param pos  (Optional) The position.
		 */
		void Render(const char* text, D3DXVECTOR2 pos = D3DXVECTOR2(0, 0));

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param text 数値.
		 * @param pos  (Optional) The position.
		 */
		void Render(int text, D3DXVECTOR2 pos = D3DXVECTOR2(0, 0));

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

	private:

		/** フォント. */
		ID3DXFont* D3DFont_;
		/** スクリーンと内部解像度の倍率. */
		float Magnification = 1.0f;

	};

}// namespace nkEngine