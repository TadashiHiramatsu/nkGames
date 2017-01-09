/**
 * @file _Graphics\nkScreenRender.h
 *
 * �V�[���������_�����O����N���X���`.
 */
#pragma once

#include"_PostEffect\nkAntiAliasing.h"
#include"_PostEffect\nkBloom.h"

namespace nkEngine
{

	/**
	 * �V�[�������_�[�N���X.
	 * �V���O���g���N���X
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CScreenRender
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CScreenRender();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CScreenRender();

	public:

		/**
		 * �C���X�^���X�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The instance.
		 */
		inline static CScreenRender& GetInstance()
		{
			static CScreenRender instance;
			return instance;
		}

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param initParam The init parameter.
		 */
		void Start(const InitParamS& initParam);

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Loop();

		/**
		 * ���C�������_�[�^�[�Q�b�g���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The main render target.
		 */
		CRenderTarget& GetMainRenderTarget()
		{
			return MainRT_;
		}

	private:

		/** �o�b�N�o�b�t�@�̃����_�[�^�[�Q�b�g. */
		CRenderTarget BackBufferRT_;
		/** ���C���̃����_�[�^�[�Q�b�g. */
		CRenderTarget MainRT_;
		/** �A���`�G�C���A�V���O. */
		CAntiAliasing AntiAliasing_;
		/** �u���[��. */
		CBloom Bloom_;
	};

	/**
	 * �X�N���[�������_�[�N���X�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CScreenRender.
	 */
	inline static CScreenRender& ScreenRender()
	{
		return CScreenRender::GetInstance();
	}
	 
}// namespace nkEngine