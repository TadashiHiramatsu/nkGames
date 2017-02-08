/**
 * @file _Graphics\_Effect\nkEffect.h
 *
 * �V�F�[�_�G�t�F�N�g�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �V�F�[�_�G�t�F�N�g�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/18
	 */
	class Effect
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		Effect()
		{
		}

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param [in,out] effect If non-null, the effect.
		 */
		Effect(ID3DXEffect* effect) :
			D3DEffect_(effect)
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		~Effect()
		{
		}

		/**
		 * �e�N�j�b�N��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param technique �e�N�j�b�N��.
		 */
		void SetTechnique(const char* technique)
		{
			D3DEffect_->SetTechnique(technique);
		}

		/**
		 * �e�N�j�b�N�̓K���J�n.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		void Begin()
		{
			D3DEffect_->Begin(nullptr, D3DXFX_DONOTSAVESHADERSTATE);
		}
		/**
		 * �e�N�j�b�N�̓K���J�n.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param [in,out] pass �p�X.
		 * @param 		   flag �t���O.
		 */
		void Begin(UINT* pass,DWORD flag)
		{
			D3DEffect_->Begin(pass, flag);
		}

		/**
		 * �g�p����e�N�j�b�N�̃p�X��ݒ肵�ĕ`��J�n.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param pass �p�X.
		 */
		void BeginPass(int pass)
		{
			D3DEffect_->BeginPass(pass);
		}

		/**
		 * �ݒ肵���l��GPU�ɑ���.
		 * �������͂�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		void CommitChanges()
		{
			D3DEffect_->CommitChanges();
		}

		/**
		 * �e�N�j�b�N�̓K�����I��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		void EndPass()
		{
			D3DEffect_->EndPass();
		}

		/**
		 * �`��̏I��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		void End()
		{
			D3DEffect_->End();
		}


		/**
		 * �l��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param name �p�����[�^�̖��O.
		 * @param data �ݒ肷��l.
		 * @param size �T�C�Y�i�P��:�o�C�g�j.
		 */
		void SetValue(const char* name, const void* data, int size)
		{
			D3DEffect_->SetValue(name, data, size);
		}

		/**
		 * �s���ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 *
		 * @param name   �p�����[�^�̖��O.
		 * @param matrix �s��̃|�C���^.
		 */
		void SetMatrix(const char* name, const D3DXMATRIX* matrix)
		{
			D3DEffect_->SetMatrix(name, matrix);
		}

		/**
		 * �s��̔z���ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param name		  �p�����[�^�̖��O.
		 * @param matrixarrey �z��̐擪�A�h���X.
		 * @param size		  �T�C�Y.
		 */
		void SetMatrixArray(const char* name, const D3DXMATRIX* matrixarrey,UINT size)
		{
			D3DEffect_->SetMatrixArray(name, matrixarrey, size);
		}

		/**
		 * �e�N�X�`����ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param name    �p�����[�^�̖��O.
		 * @param texture �e�N�X�`���N���X�̃|�C���^.
		 */
		void SetTexture(const char* name, const Texture* texture)
		{
			D3DEffect_->SetTexture(name, texture->GetTexture());
		}

		/**
		 * �����̐ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param name �p�����[�^�̖��O.
		 * @param idx  �����l.
		 */
		void SetInt(const char* name, const int idx)
		{
			D3DEffect_->SetInt(name, idx);
		}

		/**
		 * �u�[���^�̐ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param name �p�����[�^�̖��O.
		 * @param flag true or false.
		 */
		void SetBool(const char* name, const bool flag)
		{
			D3DEffect_->SetBool(name, flag);
		}

		/**
		 * �x�N�g����ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 * 
		 * @param name �p�����[�^�̖��O.
		 * @param vec  �x�N�g���̃|�C���^.
		 */
		void SetVector(const char* name, const D3DXVECTOR4* vec)
		{
			D3DEffect_->SetVector(name, vec);
		}

	private:

		/** D3D�V�F�[�_�G�t�F�N�g. */
		ID3DXEffect* D3DEffect_;

	};

}// namespace nkEngine