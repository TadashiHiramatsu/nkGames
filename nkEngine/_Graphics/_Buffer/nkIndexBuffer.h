/**
 * @file _Graphics\_Buffer\nkIndexBuffer.h
 *
 * �C���f�b�N�X�o�b�t�@�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/** �C���f�b�N�X�t�H�[�}�b�g�̗񋓌^. */
	enum class IndexFormatE
	{
		IndexFormat16 = D3DFMT_INDEX16, //!< 16bit�C���f�b�N�X
		IndexFormat32 = D3DFMT_INDEX32, //!< 32bit�C���f�b�N�X
	};

	/**
	 * �C���f�b�N�X�o�b�t�@�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class IndexBuffer : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		IndexBuffer();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~IndexBuffer();

		/**
		 * �C���f�b�N�X�o�b�t�@�̍쐬.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param indexNum		 �C���f�b�N�X�̐�.
		 * @param format		 �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g.
		 * @param srcIndexBuffer �\�[�X�C���f�b�N�X�o�b�t�@.
		 */
		void Create(int indexNum, IndexFormatE format, const void* srcIndexBuffer);

		/**
		 * �C���f�b�N�X�o�b�t�@�̉��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * �C���f�b�N�X�o�b�t�@�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the body.
		 */
		IDirect3DIndexBuffer9* GetBody()
		{
			return D3DIndexBuffer_;
		}

	private:

		/** �C���f�b�N�X�o�b�t�@. */
		IDirect3DIndexBuffer9* D3DIndexBuffer_;

	};

}// namespace nkEngine