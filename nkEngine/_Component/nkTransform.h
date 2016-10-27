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
			return Position;
		}
		D3DXVECTOR3 GetScale()
		{
			return Scale;
		}
		D3DXQUATERNION GetRotation()
		{
			return Rotation;
		}
		void SetPosition(D3DXVECTOR3& pos)
		{
			Position = pos;
		}
		void SetScale(D3DXVECTOR3& sca)
		{
			Scale = sca;
		}
		void SetRotation(D3DXQUATERNION& rot)
		{
			Rotation = rot;
		}
		void AddPosition(D3DXVECTOR3& pos)
		{
			Position += pos;
		}
	public:
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Scale;
		D3DXQUATERNION Rotation;
	};
}