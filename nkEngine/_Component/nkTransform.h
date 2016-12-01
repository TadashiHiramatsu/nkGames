#pragma once

namespace nkEngine
{
	class Transform
	{
	public:

		//�R���X�g���N�^
		Transform();

		//�f�X�g���N�^
		~Transform();

		//���[���h�s��Ȃǂ̍X�V
		void Update();
	
	public:
		//�����o�ϐ�(�O�����猩����)
		Transform* Parent; //�e
		D3DXMATRIX* ParentMatrix;

		D3DXVECTOR3 Position;
		D3DXVECTOR3 Scale;
		D3DXQUATERNION Rotation;

		D3DXMATRIX LocalMatrix; //���[�J���̃��[���h�s��
		D3DXMATRIX WorldMatrix; //���[���h�s��
		D3DXMATRIX WorldMatrixInv; //���[���h�s��̋t�s��
		D3DXMATRIX RotationMatrix; //��]�s��
	};
}