#ifndef _NKLOG_
#define _NKLOG_

namespace nkEngine
{
	//ÉçÉOèoóÕ
	static inline void Log(const char* format, ...)
	{
		char log[256];
		va_list va;
		va_start(va, format);
		vsprintf(log, format, va);
		OutputDebugString(log);
		va_end(va);
	}
}

#if _DEBUG
#define NK_LOG(format,...) nkEngine::Log(format,__VA_ARGS__)
#else
#define NK_LOG(format,...)
#endif // !_DEBUG

#endif // !_NKLOG_