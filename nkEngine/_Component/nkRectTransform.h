/**
 * @file _Component\nkRectTransform.h
 *
 * ���N�g�g�����X�t�H�[���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	* �A���J�[�v���Z�b�g.
	* �A���J�[�̈ʒu����̈ʒu�ɂȂ�.
	*/
	enum class AnchorPresetE
	{
		TopLeft,		//!< ����
		TopCenter,		//!< �㒆��
		TopRight,		//!< �E��
		MiddleLeft,		//!< ������
		MiddleCenter,	//!< ���S
		MiddleRight,	//!< �E����
		BottomLeft,		//!< ����
		BottomCenter,	//!< ������
		BottomRight,	//!< �E��
		AnchorPresetNum,//!< ��
	};

	/**
	 * UI��p�g�����X�t�H�[��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class RectTransform : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		RectTransform();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~RectTransform()
		{
		}

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * Z����].
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param angle ��]��(�x).
		 */
		void RotationZ(float angle)
		{
			Rotation_.RotationAxis(Vector3::AxisZ, angle);
		}

	public:

		/** �A���J�[.�����l�͒��S. */
		AnchorPresetE Anchor_ = AnchorPresetE::MiddleCenter;
		/** �|�W�V����. */
		Vector3 Position_ = Vector3::Zero;
		/** ����. */
		float Width_ = 100;
		/** �c��. */
		float Height_ = 100;
		/** ���S. */
		Vector2 Pivot_ = Vector2(0.5f, 0.5f);
		/** ��]. */
		Quaternion Rotation_ = Quaternion::Identity;
		/** �T�C�Y. */
		Vector2 Scale_ = Vector2::One;

	public:

		/** �e�q�֌W�����e��RectTransform�̃|�C���^. */
		RectTransform* Parent_ = nullptr;

		/** ���[���h�s��. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** ���[���h�s��(�T�C�Y�Ȃ�) */
		Matrix WorldSizeOffMatrix_ = Matrix::Identity;

		/** �v���W�F�N�V�����s��. */
		Matrix ProjectionMatrix_ = Matrix::Identity;
		/** ���[���h�v���W�F�N�V�����s��. */
		Matrix WorldProjMatrix_ = Matrix::Identity;

	};

}// namespace nkEngine