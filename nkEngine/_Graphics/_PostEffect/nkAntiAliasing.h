/**
 * @file _Graphics\_PostEffect\nkAntiAliasing.h
 *
 * �A���`�G�C���A�V���O�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/** �|�X�g�G�t�F�N�g�N���X. */
	class PostEffect;

	/**
	 * �A���`�G�C���A�V���O�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class AntiAliasing : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		AntiAliasing()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~AntiAliasing()
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
		void Create(const AntiAliasingConfigS& config);

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param [in,out] postEffect The post effect.
		 */
		void Render(PostEffect* postEffect);

	private:

		/** �L���t���O. */
		bool isEnable_ = false;
		/** �G�t�F�N�g. */
		Effect* Effect_ = nullptr;

	};

}// namespace nkEngine