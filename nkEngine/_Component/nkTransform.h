#pragma once

namespace nkEngine
{
	class CTransform
	{
	public:
		CTransform();
		~CTransform();
		D3DXVECTOR3 GetPosition()
		{
			return m_position;
		}
		D3DXVECTOR3 GetScale()
		{
			return m_scale;
		}
		D3DXQUATERNION GetRotation()
		{
			return m_rotation;
		}
		void SetPosition(D3DXVECTOR3& pos)
		{
			m_position = pos;
		}
		void SetScale(D3DXVECTOR3& sca)
		{
			m_scale = sca;
		}
		void SetRotation(D3DXQUATERNION& rot)
		{
			m_rotation = rot;
		}
	private:
		D3DXVECTOR3 m_position;
		D3DXVECTOR3 m_scale;
		D3DXQUATERNION m_rotation;
	};
}