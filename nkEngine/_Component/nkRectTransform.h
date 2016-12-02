#pragma once

namespace nkEngine
{
	//UI��p�g�����X�t�H�[��
	class RectTransform
	{
	public:

		//�A���J�[�v���Z�b�g
		//�A���J�[�̈ʒu����̈ʒu�ɂȂ�
		enum AnchorPreset
		{
			TopLeft,		//����
			TopCenter,		//�㒆��
			TopRight,		//�E��
			MiddleLeft,		//������
			MiddleCenter,	//���S
			MiddleRight,	//�E����
			BottomLeft,		//����
			BottomCenter,	//������
			BottomRight,	//�E��
			AnchorPresetNum, //��
		};



	public:

		//�R���X�g���N�^
		RectTransform();
		//�f�X�g���N�^
		~RectTransform();

		//�X�V
		void Update();

		void RotationZ(float _value)
		{
			float z = D3DXToRadian(_value);
			D3DXQuaternionRotationAxis(&Rotation, &D3DXVECTOR3(0, 0, 1), z);
		}

	public:
		AnchorPreset Anchor; //�A���J�[�����l�͒��S
		D3DXVECTOR2 Position; //�|�W�V����
		float Width; //����
		float Height; //����
		D3DXVECTOR2 Pivot; //���S
		D3DXQUATERNION Rotation; //��]		
		D3DXVECTOR2 Scale; //�T�C�Y

	public:
		RectTransform* Parent; //�e

		D3DXMATRIX WorldMatrix; //���[���h�s��
		D3DXMATRIX WorldSizeOffMatrix; //���[���h�s��(�T�C�Y�Ȃ�)
		D3DXMATRIX TransMatrix; //���s�ړ��s��
		D3DXMATRIX ScaleMatrix; //�g��s��
		D3DXMATRIX RotationMatrix; //��]�s��

		D3DXMATRIX ProjectionMatrix; //�v���W�F�N�V�����s��
		D3DXMATRIX WorldProjMatrix; //���[���h�v���W�F�N�V�����s��
	};
}