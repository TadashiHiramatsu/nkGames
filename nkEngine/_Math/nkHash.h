#pragma once

namespace nkEngine
{
	class CHash
	{
	public:
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

}