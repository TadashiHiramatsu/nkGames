/**
 * @file	_Physics\nkCollider.h
 *
 * �R���C�_�[�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �R���C�_�[�N���X.
	 * �R���C�_�[�̊��N���X.
	 * ���̂̎g�p����R���C�_�[�͂��̃N���X���p�����쐬����.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class ICollider : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		ICollider()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~ICollider()
		{
			Release();
		}

		/**
		 * �{�f�B�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		virtual btCollisionShape* GetBody() = 0;

		/**
		* ���.
		*/
		virtual void Release()
		{
		}

	};

}// namespace nkEngine