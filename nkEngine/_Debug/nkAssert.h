#ifndef _NKASSERT_

namespace nkEngine
{
	static inline void Assert(bool flag,const char* format,const char*file,long line,...)
	{
		if (!flag) {
			va_list va;
			va_start(va, flag);
			vprintf(format, va);
			char fileLineInfo[256];
			sprintf(fileLineInfo, "%s, %d行目", file, line);
			char assertMessage[256];
			vsprintf(assertMessage, format, va);
			strcat(assertMessage, fileLineInfo);
			MessageBox(nullptr, assertMessage, "アサート", MB_OK);
			va_end(va);
			abort();
		}
	}
}

#ifdef _DEBUG
#define 	NK_ASSERT( flg, format, ... )	Assert( flg, format, __FILE__, __LINE__, __VA_ARGS__)
#else
#define 	NK_ASSERT( flg, format, ... )
#endif // !_DEBUG

#endif // !_NKASSERT_