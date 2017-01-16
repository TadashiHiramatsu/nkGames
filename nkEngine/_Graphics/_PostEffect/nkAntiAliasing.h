/**
 * @file _Graphics\_PostEffect\nkAntiAliasing.h
 *
 * �A���`�G�C���A�V���O�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{
	class PostEffect;

	/**
	 * �A���`�G�C���A�V���O�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class AntiAliasing
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

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

	private:

		/** �L���t���O. */
		bool isEnable_ = false;
		/** �G�t�F�N�g. */
		ID3DXEffect* Effect_ = nullptr;

	};

}// namespace nkEngine