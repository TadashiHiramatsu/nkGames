#pragma once

#include"nkStopwatch.h"

namespace nkEngine
{
	class GameTime
	{
	private:
		//コンストラクタ
		GameTime()
		{

		}
		//デストラクタ
		~GameTime(){}
	public:
		static GameTime& GetInstance()
		{
			static GameTime t;
			return t;
		}

		float DeltaTime() const
		{
			return min(1.0f / 10.0f, m_frameDeltaTime);
		}
		void Update()
		{
			if (m_isReady) {
				m_sw.Stop();
				m_frameDeltaTime = s_cast<float>(m_sw.GetElapsed());
			}
			m_sw.Start();
			m_isReady = true;
		}

	private:
		float		m_frameDeltaTime;		//1フレームの経過時間。
		Stopwatch	m_sw;
		bool		m_isReady;
	};

	static GameTime& Time()
	{
		return GameTime::GetInstance();
	}
}