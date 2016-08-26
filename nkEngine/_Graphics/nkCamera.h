//�J�����N���X
#pragma once

namespace nkEngine
{
	class CCamera
	{
	public:
		//�R���X�g���N�^
		CCamera();

		//�f�X�g���N�^
		~CCamera();

		//�X�V
		void Update();

		//����]
		//param[in] ��]��
		void SpinHorizontally(float rot);

		//�c��]
		//param[in] ��]��
		void SpinVertically(float rot);
		
		//�r���[�s��̎擾
		//return �r���[�s��
		const D3DXMATRIX& GetViewMatrix()
		{
			return m_mView;
		}

		//�v���W�F�N�V�����s��̎擾
		//return �v���W�F�N�V�����s��
		const D3DXMATRIX& GetProjectionMatrix()
		{
			return m_mProj;
		}

		//��]�s��̎擾
		//return ��]�s��
		const D3DXMATRIX& GetRotationMatrix()
		{
			return m_mRotation;
		}

		//��]�s��̋t�s��擾
		//return ��]�s��̋t�s��
		const D3DXMATRIX& GetRotationInvMatrix()
		{
			return m_mRotationInv;
		}

		//�J�����̎��_�̎擾
		//return �J�����̎��_
		const D3DXVECTOR3& GetPosition()
		{
			return m_vNormalizeTarget;
		}

		//�J�����̎��_�̐ݒ�
		//param[in] ���_�x�N�g��
		void SetPosition(const D3DXVECTOR3& pos)
		{
			D3DXVec3Normalize(&m_vNormalizeTarget, &pos);
		}

		//�J�����̒����_�̎擾
		//return �J�����̒����_
		const D3DXVECTOR3& GetTarget()
		{
			return m_vTarget;
		}

		//�J�����̒����_�̐ݒ�
		//param[in] �����_�x�N�g��
		void SetTarget(const D3DXVECTOR3& target)
		{
			m_vTarget = target;
		}

		//�J�����̏�����̎擾
		//return �J�����̏����
		const D3DXVECTOR3& GetUp()
		{
			return m_vUp;
		}

		//�J�����̏�����̐ݒ�
		//param[in] ������x�N�g��
		void SetUp(const D3DXVECTOR3& up)
		{
			m_vUp = up;
		}

		//�J�����̎��_�ƒ����_�̋������擾
		//return �J�����̋���
		const float GetDistance()
		{
			return m_Distance;
		}

		//�J�����̎��_�ƒ����_�̏�����ݒ�
		//param[in] ����
		void SetDistance(const float dis)
		{
			m_Distance = dis;
		}

		//�J�����̉�p���擾
		//return �J�����̉�p
		const float GetFovy()
		{
			return m_Fovy;
		}

		//�J�����̉�p��ݒ�
		//param[in] ��p
		void SetFovy(const float fovy)
		{
			m_Fovy = fovy;
		}

		//�J�����̃A�X�y�N�g����擾
		//return �J�����̃A�X�y�N�g��
		const float GetAspect()
		{
			return m_Aspect;
		}

		//�J�����̃A�X�y�N�g���ݒ�
		//param[in] �A�X�y�N�g��
		void SetAspect(const float aspect)
		{
			m_Aspect = aspect;
		}

		//�J�����̃j�A���擾
		//return �J�����̃j�A
		const float GetNear()
		{
			return m_Near;
		}

		//�J�����̃j�A��ݒ�
		//param[in] �j�A
		void SetNear(const float fnear)
		{
			m_Near = fnear;
		}

		//�J�����̃t�@�[���擾
		//return �J�����̃t�@�[
		const float GetFar()
		{
			return m_Far;
		}

		//�J�����̃t�@�[��ݒ�
		//param[in] �t�@�[
		void SetFar(const float ffar)
		{
			m_Far = ffar;
		}

	private:
		D3DXMATRIX m_mView; //�r���[�s��
		D3DXMATRIX m_mProj; //�v���W�F�N�V�����s��
		D3DXMATRIX m_mRotation; //��]�s��
		D3DXMATRIX m_mRotationInv; //��]�s��̋t�s��

		D3DXVECTOR3 m_vPosition; //�J�����̎��_
		D3DXVECTOR3 m_vTarget; //�J�����̒����_
		D3DXVECTOR3 m_vNormalizeTarget; //�J�����̒����_
		D3DXVECTOR3 m_vUp; //�J�����̏����
		float m_Distance; //�J�����̎��_�ƒ����_�̋���

		float m_Fovy;		//��p
		float m_Aspect;	//�A�X�y�N�g��
		float m_Near;		//�j�A
		float m_Far;		//�t�@�[

	};
}