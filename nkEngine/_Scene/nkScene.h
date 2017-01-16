/**
 * @file	_Scene\nkScene.h
 *
 * �V�[���N���X�̒�`.
 */
#pragma once 

#include"..\_Graphics\nkGraphicsConfig.h"

namespace nkEngine
{
	/**
	 * �V�[���̊��N���X.
	 * ���̃N���X���p������V�[���N���X���쐬����
	 * �V�[���}�l�[�W���ɓo�^����K�v������
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class IScene
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		IScene();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		virtual ~IScene();

	public:

		/**
		 * ������.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		virtual void Start() = 0;

		/**
		 * �O���t�B�b�N�R���t�B�O�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The graphics configuration.
		 */
		const GraphicsConfigS& GetGraphicsConfig() const
		{
			return GraphicsConfig_;
		}

	protected:

		/** �O���t�B�b�N�̐ݒ�. */
		GraphicsConfigS GraphicsConfig_;
	
	};
}
