/**
 * @file _Debug\nkLog.h
 *
 * ���O�o�͊֐��̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ���O�o��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param format Describes the format to use.
	 * @param ...    Variable arguments providing additional information.
	 */
	static inline void Log(const char* format, ...)
	{
		char log[256];
		va_list va;
		va_start(va, format);
		vsprintf(log, format, va);
		OutputDebugString(log);
		va_end(va);
	}

}// namespace nkEngine

#if _DEBUG
#define NK_LOG(format,...) nkEngine::Log(format,__VA_ARGS__)
#else
#define NK_LOG(format,...)
#endif // !_DEBUG