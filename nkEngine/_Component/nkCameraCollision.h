/**
* �J�����̃R���W�����N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �J�����R���W�����N���X.
	* ��ʓI�ȎO�l�̎��_�̃Q�[���J�����̃R���W����.
	*/
	class CameraCollision : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		CameraCollision()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~CameraCollision()
		{
		}

		/**
		* ������.
		*
		* @param radius	�J�����̔��a.
		* @param posdir	�J�����̎��_�����|�C���^.
		* @param tar	�J�����̒����_���W�|�C���^.
		*/
		void Start(float radius,const Vector3* posdir, const Vector3* tar);

		/**
		* �X�V.
		*/
		void Update();

		/**
		* �����_���王�_�̋������擾.
		*/
		float GetDistance() const
		{
			return Distance_;
		}

		/**
		* �ʏ�̋�����ݒ�.
		*/
		void SetDefaultDistance(float value)
		{
			DefaultDistance_ = value;
		}

	private:

		const Vector3* CameraPosDirection_ = nullptr;
		/** Camera�̒����_�|�C���^. */
		const Vector3* CameraTarget_ = nullptr;

		/** ���̃R���C�_�[. */
		SphereCollider Collider_;
		/** ���a. */
		float Radius_;

		/** �����_���王�_�ւ̋���. */
		float Distance_ = 10;
		/** �ʏ�̋���. */
		float DefaultDistance_ = 10;

	};
}