/**
 * @file _Graphics\_UI\nkText.h
 *
 * �e�X�g�t�H���g�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �e�L�X�g�N���X.
	 * �N���X���œ����𑜓x�̃T�C�Y�ɍ��킹�Ă���̂�
	 * �g�p���̓X�N���[���T�C�Y�Ōv�Z������OK.
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
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Text();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Text();

		/**
		 * �쐬.
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
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param text ����.
		 * @param pos  (Optional) The position.
		 */
		void Render(const char* text);

		/**
		 * ���.
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

		/** �t�H���g. */
		ID3DXFont* D3DFont_;
		/** �X�N���[���Ɠ����𑜓x�̔{��. */
		float Magnification = 1.0f;

		int Height_;
		int Width_;

		RectTransform* Transform_;

		D3DXVECTOR4 Color_ = D3DXVECTOR4(0, 0, 0, 255);
	};

}// namespace nkEngine