#pragma once

namespace nkEngine
{
	class CGameObject
	{
	public:
		CGameObject();
		virtual ~CGameObject();
		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void Release();
	
	private:

	};

}