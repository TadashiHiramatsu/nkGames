#pragma once

namespace nkEngine
{
	class CGameObject
	{
	public:
		CGameObject();
		virtual ~CGameObject();
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;

		bool Active()
		{
			return m_Active;
		}
		bool Death()
		{
			return m_Death;
		}
	
	private:
		//—LŒø‚©
		bool m_Active;
		//¶‘¶ƒtƒ‰ƒO
		bool m_Death;
	};

}