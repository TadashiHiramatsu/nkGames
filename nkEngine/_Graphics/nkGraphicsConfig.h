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

		/** �V���h�E�}�b�v�̗L���t���O. */
		bool isEnable_ = false;
		/** �V���h�E�}�b�v�̉���. */
		int ShadowMapW_ = 512;
		/** �V���h�E�}�b�v�̏c��. */
		int ShadowMapH_ = 512;
		/** �\�t�g�V���h�E�}�b�v�̗L���t���O. */
		bool isSoftShadowMap_ = false;
		/** �t�@�[. */
		float Far_ = 100.0f;
		/** �j�A. */
		float Near_ = 1.0f;

	};

	/**
	 * �u���[���N���X�̃R���t�B�O.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	struct BloomConfigS
	{
	public:

		/** �u���[���̗L���t���O. */
		bool isEnable_ = false;
	
	};

	/**
	 * �A���`�G�C���A�X�N���X�̃R���t�B�O.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	struct AntiAliasingConfigS
	{
	public:

		/** �A���`�G�C���A�X�̗L���t���O. */
		bool isEnable_ = false;
	
	};

	/**
	 * �e�V�[���Őݒ肷��O���t�B�b�N�̃R���t�B�O.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct GraphicsConfigS
	{
	public:

		/** �V���h�E�}�b�v�̃R���t�B�O. */
		ShadowConfigS ShadowConfig_;
		/** �u���[���̃R���t�B�O. */
		BloomConfigS BloomConfig_;
		/** �A���`�G�C���A�X�̃R���t�B�O. */
		AntiAliasingConfigS AntiAliasingConfig_;

	};

}// namespace nkEngine