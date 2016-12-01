#pragma once

namespace nkEngine
{
	class UITransform
	{
	public:
		UITransform();
		
		//�X�V
		void Update();
	public:

		D3DXVECTOR2 Position = D3DXVECTOR2(0, 0); //�|�W�V����
		D3DXVECTOR2 Size = D3DXVECTOR2(100, 100);	//�T�C�Y
		D3DXVECTOR2 Pivot = D3DXVECTOR2(0.5f, 0.5f);	//���S
		D3DXQUATERNION Rotation = D3DXQUATERNION(0, 0, 0, 1);	//��]		

		D3DXMATRIX mWorld;
		D3DXMATRIX mLocal;
		D3DXMATRIX* mParent;
	};
}