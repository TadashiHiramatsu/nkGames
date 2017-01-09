/**
 * @file _Graphics\_PostEffect\nkAntiAliasing.h
 *
 * �A���`�G�C���A�V���O�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

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
		AntiAliasing();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~AntiAliasing();

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Init();

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

	private:

		/** �L���t���O. */
		bool isEnable_;
		/** �G�t�F�N�g. */
		ID3DXEffect* Effect_;
		/** The primitive. */
		Primitive Primitive_;

	};
}