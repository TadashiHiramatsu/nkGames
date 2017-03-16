/**
 * @file	_Math\nkHash.h
 *
 * ハッシュ値計算クラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ハッシュ値を計算するクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/08
	 */
	class Hash : Noncopyable
	{
	public:

		/**
		 * ハッシュ作成.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 *
		 * @param	string	文字列.
		 *
		 * @return	ハッシュ値.
		 */
		static int MakeHash(const char* string)
		{
			int hash = 0;
			int len = (int)strlen(string);
			for (int i = 0; i < len; i++)
			{
				hash = hash * 37 + string[i];
			}
			return hash;
		}

	};

}// namespace nkEngine