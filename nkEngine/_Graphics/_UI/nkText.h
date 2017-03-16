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
	class Text : Noncopyable
	{
	public:

		/** 文字の太さの形式. */
		enum class FontWeightE
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

		/** 表示形式. */
		enum class FormatE
		{
			Left,	//!< 左詰め
			Center, //!< 中央
		};

	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Text()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Text()
		{
			//解放.
			Release();
		}

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

		/**
		* レクトトランスフォームを設定.
		*
		* @param rt	レクトトランスフォームのポインタ.
		*/
		void SetTransform(RectTransform* rt)
		{
			Transform_ = rt;
		}

		/**
		* 色の設定.
		*
		* @param color	四次元ベクトル( x:r, y:g, z:b, w:a).
		*/
		void SetColor(const Vector4& color)
		{
			Color_ = color;
		}

		/**
		* 表示形式を設定.
		*
		* @param format	形式.
		*/
		void SetFormat(FormatE format)
		{
			Format_ = format;
		}

	private:

		/** フォント. */
		ID3DXFont* D3DFont_ = nullptr;
		/** スクリーンと内部解像度の倍率. */
		float Magnification = 1.0f;

		/** 高さ. */
		int Height_ = 0;
		/** 幅. */
		int Width_ = 0;

		/** トランスフォーム. */
		RectTransform* Transform_ = nullptr;

		/** 色. */
		Vector4 Color_ = Vector4(0, 0, 0, 255);

		/** 表示形式. */
		FormatE Format_;
	
};

}// namespace nkEngine