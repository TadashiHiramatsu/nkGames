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

		int Priority()
		{
			return m_Priority;
		}
		bool Active()
		{
			return m_Active;
		}
		bool Death()
		{
			return m_Death;
		}
		friend bool operator<(const CGameObject& go1, const CGameObject& go2)
		{
			return go1 < go2;
		}
	private:
		//優先度
		int m_Priority;
		//有効か
		bool m_Active;
		//生存フラグ
		bool m_Death;
	};

}