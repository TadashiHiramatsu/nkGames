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
	class Text : Noncopyable
	{
	public:

		/** �����̑����̌`��. */
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

		/** �\���`��. */
		enum class FormatE
		{
			Left,	//!< ���l��
			Center, //!< ����
		};

	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Text()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Text()
		{
			//���.
			Release();
		}

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

		/**
		* ���N�g�g�����X�t�H�[����ݒ�.
		*
		* @param rt	���N�g�g�����X�t�H�[���̃|�C���^.
		*/
		void SetTransform(RectTransform* rt)
		{
			Transform_ = rt;
		}

		/**
		* �F�̐ݒ�.
		*
		* @param color	�l�����x�N�g��( x:r, y:g, z:b, w:a).
		*/
		void SetColor(const Vector4& color)
		{
			Color_ = color;
		}

		/**
		* �\���`����ݒ�.
		*
		* @param format	�`��.
		*/
		void SetFormat(FormatE format)
		{
			Format_ = format;
		}

	private:

		/** �t�H���g. */
		ID3DXFont* D3DFont_ = nullptr;
		/** �X�N���[���Ɠ����𑜓x�̔{��. */
		float Magnification = 1.0f;

		/** ����. */
		int Height_ = 0;
		/** ��. */
		int Width_ = 0;

		/** �g�����X�t�H�[��. */
		RectTransform* Transform_ = nullptr;

		/** �F. */
		Vector4 Color_ = Vector4(0, 0, 0, 255);

		/** �\���`��. */
		FormatE Format_;
	
};

}// namespace nkEngine