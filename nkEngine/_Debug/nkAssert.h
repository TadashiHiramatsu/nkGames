/**
 * @file _Debug\nkAssert.h
 *
 * �A�T�[�g�o�͊֐��̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �A�T�[�g.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param flag   True to flag.
	 * @param format Describes the format to use.
	 * @param file   The file.
	 * @param line   The line.
	 * @param ...    Variable arguments providing additional information.
	 */
	static inline void Assert(bool flag,const char* format,const char*file,long line,...)
	{
		if (!flag) {
			va_list va;
			va_start(va, flag);
			vprintf(format, va);
			char fileLineInfo[256];
			sprintf(fileLineInfo, "%s, %d�s��", file, line);
			char assertMessage[256];
			vsprintf(assertMessage, format, va);
			strcat(assertMessage, fileLineInfo);
			MessageBox(nullptr, assertMessage, "�A�T�[�g", MB_OK);
			va_end(va);
			abort();
		}
	}

}// namespace nkEngine

#ifdef _DEBUG
#define 	NK_ASSERT( flg, format, ... )	Assert( flg, format, __FILE__, __LINE__, __VA_ARGS__)
#else
#define 	NK_ASSERT( flg, format, ... )
#endif // !_DEBUG