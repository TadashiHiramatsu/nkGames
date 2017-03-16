/**
 * @file _Graphics\_PostEffect\nkPostEffect.h
 *
 * �|�X�g�G�t�F�N�g�N���X�̒�`.
 */
#pragma once

#include"nkAntiAliasing.h"
#include"nkBloom.h"

namespace nkEngine
{

	/**
	 * �|�X�g�G�t�F�N�g�N���X.
	 * �쐬�����|�X�g�G�t�F�N�g�͂����Ŏg�p����
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	class PostEffect : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		PostEffect()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		~PostEffect()
		{
		}

		/**
		 * �쐬.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param config The configuration.
		 */
		void Create(const GraphicsConfigS& config);

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void Render();

		/**
		 * �t���X�N���[���`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void RenderFullScreen();

	private:

		/** �t���X�N���[���`��p�v���~�e�B�u. */
		Primitive Primitive_;

		/** �u���[��. */
		Bloom Bloom_;
		/** �A���`�G�C���A�X. */
		AntiAliasing AntiAliasing_;

	};
}