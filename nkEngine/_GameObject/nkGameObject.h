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
		//�D��x
		int m_Priority;
		//�L����
		bool m_Active;
		//�����t���O
		bool m_Death;
	};

}