/**
 * @file _Graphics\_PreRender\nkShadow.h
 *
 * �V���h�E�}�b�v�N���X.
 */
#pragma once

#include"..\nkCamera.h"
#include"..\nkBlur.h"

namespace nkEngine
{

	class CModelRender;

	/**
	 * �V���h�E�}�b�v�N���X.
	 * �V���O���g���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CShadowMap
	{
	public:

		/** �V���h�E�}�b�v�̐�. */
		static const int MAX_SHADOW_MAP = 3;

		/**
		* �V���h�E���V�[�o�[�p�̃p�����[�^.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/09
		*/
		struct ShadowReceiverParamS
		{
		public:

			/** ���C�g�r���[�v���W�F�N�V�����s��. */
			D3DXMATRIX LightViewProjMatrix_[MAX_SHADOW_MAP];
			/** �o���A���X�V���h�E�}�b�v���s�����̃t���O. */
			bool isVSM_;
			/** �V���h�E�}�b�v�̖���. */
			int numShadowMap_;

		};

		/** ���C�g�r���[�̌v�Z�̎d��. */
		enum CalcLightViewFuncE {
			CalcLightViewFunc_PositionDirection,	//!< ���C�g�̈ʒu�ƕ����Ōv�Z����B
			CalcLightViewFunc_PositionTarget,		//!< ���C�g�̈ʒu�ƒ����_�Ōv�Z����B
		};

	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CShadowMap();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CShadowMap();

	public:

		/**
		* �C���X�^���X�̎擾.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/09
		*
		* @return The instance.
		*/
		inline static CShadowMap& GetInstance()
		{
			static CShadowMap instance;
			return instance;
		}

		/**
		 * �쐬.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param config �R���t�B�O.
		 */
		void Create(const ShadowConfigS& config);

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * �J��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * ���f�����G���g���[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] skinModel ���f��.
		 */
		void Entry(CModelRender* skinModel);

		/**
		 * �e�N�X�`�����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param texNumber �e�N�X�`���i���o.
		 *
		 * @return Null if it fails, else the texture.
		 */
		const Texture* GetTexture(int texNumber) const
		{
			return Blur_[texNumber].GetTexture();
			//return m_shadowMapRT[texNumber].GetTexture();
		}

		/**
		 * ���C�g�̕�����ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param dir The dir.
		 */
		void SetLightDirection(const D3DXVECTOR3& dir)
		{
			LightDirection_ = dir;
		}

		/**
		 * ���C�g�̎��_��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param pos The position.
		 */
		void SetLightPosition(const D3DXVECTOR3& pos)
		{
			LightPosition_ = pos;
		}

		/**
		 * ���C�g�̒����_��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param target The target.
		 */
		void SetLightTarget(const D3DXVECTOR3& target)
		{
			LightTarget_ = target;
		}

		/**
		 * �ߕ��ʂ��擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The near.
		 */
		float GetNear() const
		{
			return Near_;
		}

		/**
		 * �ߕ��ʂ�ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param idx The near.
		 */
		void SetNear(float idx)
		{
			Near_ = idx;
		}

		/**
		 * �����ʂ��擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The far.
		 */
		float GetFar() const
		{
			return Far_;
		}

		/**
		 * �����ʂ�ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param idx The far.
		 */
		void SetFar(float idx)
		{
			Far_ = idx;
		}

		/**
		 * �L���t���O�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return True if enable, false if not.
		 */
		bool isEnable()const
		{
			return isEnable_;
		}

		/**
		 * ���C�g�r���[�̐ݒ�̎d����ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param func The function.
		 */
		void SetCalcLightViewFunc(CalcLightViewFuncE func)
		{
			CalcLightViewFunc_ = func;
		}

		/**
		 * �V���h�E���V�[�o�[�p�̃p�����[�^���擾 return �V���h�E���V�[�o�[�p�̃p�����[�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The shadow receiver parameter.
		 */
		const ShadowReceiverParamS& GetShadowReceiverParam()
		{
			return ShadowReceiverParam_;
		}

		/**
		 * ���C�g�r���[�v���W�F�N�V�����s��̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The light view projection matrix.
		 */
		const D3DXMATRIX& GetLightViewProjectionMatrix() const
		{
			return LightViewProjMatrix_;
		}

	private:

		/** �L���t���O. */
		bool isEnable_;
		/** �V���h�E�}�b�v�p�����_�[�^�[�Q�b�g. */
		RenderTarget ShadowMapRT_[MAX_SHADOW_MAP];
		/** �e���������ރ��f��. */
		vector<CModelRender*> ShadowModels_;

		/** ���C�g�̎��_. */
		D3DXVECTOR3 LightPosition_;
		/** ���C�g�̕���. */
		D3DXVECTOR3 LightDirection_;
		/** ���C�g�̒����_. */
		D3DXVECTOR3 LightTarget_;

		/** ���C�g�r���[�s��. */
		D3DXMATRIX LightViewMatrix_;
		/** �v���W�F�N�V�����s��. */
		D3DXMATRIX ProjMatrix_;
		/** ���C�g�r���[�v���W�F�N�V�����s��. */
		D3DXMATRIX LightViewProjMatrix_;

		/** ���C�g�r���[�̌v�Z���@. */
		CalcLightViewFuncE	CalcLightViewFunc_;

		/** �ߕ���. */
		float Near_;
		/** ������. */
		float Far_;
		/** �A�X�y�N�g��. */
		float Aspect_;
		/** �e�𗎂Ƃ��͈͂̕�. */
		float ShadowAreaW_[MAX_SHADOW_MAP];
		/** �e�𗎂Ƃ��͈͂̍���. */
		float ShadowAreaH_[MAX_SHADOW_MAP];

		/** �u���[�����N���X. */
		Blur Blur_[MAX_SHADOW_MAP];
		/** �V���h�E���V�[�o�[�p�̃p�����[�^. */
		ShadowReceiverParamS ShadowReceiverParam_;

	};

	/**
	 * �V���h�E�}�b�v�N���X�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CShadowMap.
	 */
	inline static CShadowMap& Shadow()
	{
		return CShadowMap::GetInstance();
	}

}// namespace nkEngine