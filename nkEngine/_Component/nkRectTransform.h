/**
 * @file _Component\nkRectTransform.h
 *
 * ���N�g�g�����X�t�H�[���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �Փ˔���Ɏg�p������.
	 * ��ʍ����0,0�Ƃ���ʒu���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct BoxCollisionS
	{
	public:

		/** ��. */
		int Top_;
		/** ��. */
		int Bottom_;
		/** ��. */
		int Left_;
		/** �E. */
		int Right_;

	};

	/**
	 * UI��p�g�����X�t�H�[��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class RectTransform
	{
	public:

		/**   
		 * �A���J�[�v���Z�b�g.
		 * �A���J�[�̈ʒu����̈ʒu�ɂȂ�. 
		 */
		enum AnchorPresetE
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
		~RectTransform();

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
		 * @param value Degree�l.
		 */
		void RotationZ(float value)
		{
			float z = D3DXToRadian(value);
			D3DXQuaternionRotationAxis(&Rotation_, &D3DXVECTOR3(0, 0, 1), z);
		}

	public:

		/** �A���J�[�����l�͒��S. */
		AnchorPresetE Anchor_;
		/** �|�W�V����. */
		D3DXVECTOR3 Position_;
		/** ����. */
		float Width_;
		/** �c��. */
		float Height_;
		/** ���S. */
		D3DXVECTOR2 Pivot_;
		/** ��]. */
		D3DXQUATERNION Rotation_;
		/** �T�C�Y. */
		D3DXVECTOR2 Scale_;

		/** �Փ˃��N�g. */
		BoxCollisionS BoxCol_;

	public:

		/** �e�q�֌W�����e��RectTransform�̃|�C���^. */
		RectTransform* Parent_;

		/** ���[���h�s��. */
		D3DXMATRIX WorldMatrix_;
		/** ���[���h�s��(�T�C�Y�Ȃ�) */
		D3DXMATRIX WorldSizeOffMatrix_;

		/** �v���W�F�N�V�����s��. */
		D3DXMATRIX ProjectionMatrix_;
		/** ���[���h�v���W�F�N�V�����s��. */
		D3DXMATRIX WorldProjMatrix_;

	};

}// namespace nkEngine