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
		//�L����
		bool m_Active;
		//�����t���O
		bool m_Death;
	};

}