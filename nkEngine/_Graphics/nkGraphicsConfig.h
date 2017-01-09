/**
 * @file	_Graphics\nkGraphicsConfig.h
 *
 * �e�V�[���Őݒ肷��R���t�B�O�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �V���h�E�}�b�v�N���X�̃R���t�B�O.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct ShadowConfigS
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		ShadowConfigS()
		{
			isEnable_ = isSoftShadowMap_ = false;
			ShadowMapW_ = ShadowMapH_ = 512;
			Fur_ = 1000.0f;
			Near_ = 1.0f;
		}

	public:

		/** �V���h�E�}�b�v�̗L���t���O. */
		bool isEnable_;
		/** �V���h�E�}�b�v�̉���. */
		int ShadowMapW_;
		/** �V���h�E�}�b�v�̏c��. */
		int ShadowMapH_;
		/** �\�t�g�V���h�E�}�b�v�̗L���t���O. */
		bool isSoftShadowMap_;
		/** �t�@�[. */
		float Fur_;
		/** �j�A. */
		float Near_;
	};

	/**
	 * �e�V�[���Őݒ肷��O���t�B�b�N�̃R���t�B�O.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct SGraphicsConfig
	{
	public:

		/** The shadow configuration. */
		ShadowConfigS ShadowConfig_;

	};

}// namespace nkEngine