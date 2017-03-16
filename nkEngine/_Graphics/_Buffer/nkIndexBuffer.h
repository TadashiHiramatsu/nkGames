/**
 * @file _Graphics\_Buffer\nkIndexBuffer.h
 *
 * インデックスバッファクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/** インデックスフォーマットの列挙型. */
	enum class IndexFormatE
	{
		IndexFormat16 = D3DFMT_INDEX16, //!< 16bitインデックス
		IndexFormat32 = D3DFMT_INDEX32, //!< 32bitインデックス
	};

	/**
	 * インデックスバッファクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class IndexBuffer : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		IndexBuffer();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~IndexBuffer();

		/**
		 * インデックスバッファの作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param indexNum		 インデックスの数.
		 * @param format		 インデックスバッファのフォーマット.
		 * @param srcIndexBuffer ソースインデックスバッファ.
		 */
		void Create(int indexNum, IndexFormatE format, const void* srcIndexBuffer);

		/**
		 * インデックスバッファの解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * インデックスバッファの取得.
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

		/** インデックスバッファ. */
		IDirect3DIndexBuffer9* D3DIndexBuffer_;

	};

}// namespace nkEngine