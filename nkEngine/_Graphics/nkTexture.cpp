#include"nkEngine/nkstdafx.h"
#include"nkTexture.h"

namespace nkEngine
{

	void CTexture::Load(const char * fileName)
	{
		IDirect3DDevice9* Device = Engine().GetDevice();
		char* baseDir = "Texture/";
		char filePath[64];
		strcpy(filePath, baseDir);
		strcat(filePath, fileName);

		if(FAILED(D3DXCreateTextureFromFile(
		Device,
			filePath,
			&m_tex)))
		{
			NK_ASSERT(false, "failed lloadtexture");
		}
	}

}