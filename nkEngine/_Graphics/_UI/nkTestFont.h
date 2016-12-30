#pragma once

namespace nkEngine
{
	class TestFont
	{
	public:
		enum FontWeights
		{
			DONTCARE = FW_DONTCARE,
			THIN = FW_THIN,
			EXTRALIGHT = FW_EXTRALIGHT,
			LIGHT = FW_LIGHT,
			NORMAL = FW_NORMAL,
			MEDIUM = FW_MEDIUM,
			SEMIBOLD = FW_SEMIBOLD,
			BOLD = FW_BOLD,
			EXTRABOLD = FW_EXTRABOLD,
			HEAVY = FW_HEAVY
		};
	public:
		TestFont();
		~TestFont();
		void Create(int _Height, int _Width, FontWeights _Weights = FontWeights::NORMAL);
		void Render(const char* _Text, int _Num, D3DXVECTOR2 _Pos = D3DXVECTOR2(0, 0));
		void Render(const char* _Text, D3DXVECTOR2 _Pos = D3DXVECTOR2(0, 0));
		void Render(int _Text, D3DXVECTOR2 _Pos = D3DXVECTOR2(0, 0));
		void Release();
	private:
		LPD3DXFONT	pFont;
	};
}