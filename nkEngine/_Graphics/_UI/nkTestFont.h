/**
 * @file _Graphics\_UI\nkTestFont.h
 *
 * �e�X�g�t�H���g�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �e�X�g�t�H���g�N���X.
	 * �N���X���œ����𑜓x�̃T�C�Y�ɍ��킹�Ă���̂�
	 * �g�p���̓X�N���[���T�C�Y�Ōv�Z������OK.
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
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		TestFont();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~TestFont();

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
		 * @param num  ���l.
		 * @param pos  (Optional) The position.
		 */
		void Render(const char* text, int num, D3DXVECTOR2 pos = D3DXVECTOR2(0, 0));

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param text ����.
		 * @param pos  (Optional) The position.
		 */
		void Render(const char* text, D3DXVECTOR2 pos = D3DXVECTOR2(0, 0));

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param text ���l.
		 * @param pos  (Optional) The position.
		 */
		void Render(int text, D3DXVECTOR2 pos = D3DXVECTOR2(0, 0));

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

	private:

		/** �t�H���g. */
		ID3DXFont* D3DFont_;
		/** �X�N���[���Ɠ����𑜓x�̔{��. */
		float Magnification = 1.0f;

	};

}// namespace nkEngine