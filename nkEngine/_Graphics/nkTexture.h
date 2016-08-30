#pragma once

namespace nkEngine
{
	class CTexture
	{
	public:
		CTexture():
			m_tex(nullptr)
		{}
		~CTexture()
		{
			SAFE_RELEASE(m_tex);
		}
		void SetTextureDX(IDirect3DTexture9* tex)
		{
			m_tex = tex;
		}
		IDirect3DTexture9* GetTextureDX() const
		{
			return m_tex;
		}
		void Load(const char* fileName);
	private:
		IDirect3DTexture9* m_tex;
	};
}