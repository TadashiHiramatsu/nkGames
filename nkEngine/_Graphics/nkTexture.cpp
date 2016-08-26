#include"nkEngine/nkstdafx.h"
#include"nkTexture.h"

namespace nkEngine
{

	void CTexture::Load(const char * fileName)
	{
		IDirect3DDevice9* Device = Engine().GetDevice();
		if(FAILED(D3DXCreateTextureFromFile(
		Device,
			fileName,
			&m_tex)))
		{
			NK_ASSERT(false, "failed lloadtexture");
		}
	}

}