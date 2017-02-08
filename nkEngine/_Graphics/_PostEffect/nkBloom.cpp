/**
 * @file _Graphics\_PostEffect\nkBloom.cpp
 *
 * �u���[���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkBloom.h"


namespace nkEngine
{

	/**
	 * �쐬.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param config The configuration.
	 */
	void Bloom::Create(const BloomConfigS & config)
	{
		//�L���t���O���R�s�[
		isEnable_ = config.isEnable_;

		if (isEnable_)
		{
			//�����𑜓x�̃T�C�Y���v�Z
			int w = Engine().GetFrameW();
			int h = Engine().GetFrameH();

			//�P�x�����_�����O�^�[�Q�b�g�̍쐬
			LuminanceRT_.Create(w, h, 1, D3DFMT_A16B16G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

			for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++)
			{
				//�V�t�g�ʂ̌v�Z
				int shift = i + 1;

				//�_�E���T���v�����O�pRT�̓Y�������v�Z
				int baseIndex = i * 2;
				
				//���u���[�pRT�̍쐬
				DownSamplingRT_[baseIndex].Create(w >> shift, h >> (shift - 1), 1, D3DFMT_A16B16G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	
				//�c�u���[�pRT�̍쐬
				DownSamplingRT_[baseIndex + 1].Create(w >> shift, h >> shift, 1, D3DFMT_A16B16G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	
			}

			//�ڂ��������pRT�̍쐬
			CombineRT_.Create(w >> 2, h >> 2, 1, D3DFMT_A16B16G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);			

			//�G�t�F�N�g�̃��[�h
			Effect_ = EffectManager().LoadEffect("Bloom.fx");
		}
	}

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param [in,out] postEffect If non-null, the post effect.
	 */
	void Bloom::Render(PostEffect* postEffect)
	{
		if (isEnable_)
		{
			//�f�o�C�X�̎擾
			IDirect3DDevice9* Device = Engine().GetDevice();

			//�d�݌v�Z
			UpdateWeight(25.0f);

			//�P�x���o
			{

				//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
				Device->SetRenderTarget(0, LuminanceRT_.GetSurface());
				Device->SetDepthStencilSurface(LuminanceRT_.GetDepthSurface());

				//�e�N�X�`���̃N���A
				Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);

				Effect_->SetTechnique("SamplingLuminance");

				Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
				Effect_->BeginPass(0);

				//�e�N�X�`���̐ݒ�
				Effect_->SetTexture("g_Scene", ScreenRender().GetMainRenderTarget().GetTexture());

				Effect_->CommitChanges();

				postEffect->RenderFullScreen();

				Effect_->EndPass();
				Effect_->End();

			}//�P�x���o

			//�P�x���ڂ���
			{
				//���[�v�pRT�N���X�̃|�C���^
				RenderTarget* prevRT = &LuminanceRT_;
				//�_�E���T���v�����O�pRT�̓Y����
				int rtIndex = 0;

				for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++)
				{
					//XBlur
					{
						//�_�E���T���v�����O�pRT��XBlur�p�������_�����O�^�[�Q�b�g�ɐݒ�
						Device->SetRenderTarget(0, DownSamplingRT_[rtIndex].GetSurface());
						Device->SetDepthStencilSurface(DownSamplingRT_[rtIndex].GetDepthSurface());

						//�摜���N���A
						Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);

						//�e�N�j�b�N��ݒ�
						Effect_->SetTechnique("XBlur");

						Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
						Effect_->BeginPass(0);
						
						//�摜�T�C�Y���v�Z
						float size[2] = 
						{
							s_cast<float>(prevRT->GetSizeW()),
							s_cast<float>(prevRT->GetSizeH())
						};
						//�I�t�Z�b�g���v�Z
						float offset[] = 
						{
							16.0f / s_cast<float>(prevRT->GetSizeW()),
							0.0f
						};

						//��ʃT�C�Y��ݒ�
						Effect_->SetValue("g_LuminanceTexSize", size, sizeof(size));
						//�I�t�Z�b�g��ݒ�
						Effect_->SetValue("g_Offset", offset, sizeof(size));
						//�d�݂�ݒ�
						Effect_->SetValue("g_Weight", Weights_, sizeof(Weights_));

						//�e�N�X�`����ݒ�
						Effect_->SetTexture( "g_Blur", prevRT->GetTexture());

						Effect_->CommitChanges();

						postEffect->RenderFullScreen();

						Effect_->EndPass();
						Effect_->End();
					}//XBlur

					//YBlur�p��ݒ�
					prevRT = &DownSamplingRT_[rtIndex];
					rtIndex++;

					//YBlur
					{
						//�_�E���T���v�����O�pRT��YBlur�p�������_�����O�^�[�Q�b�g�ɐݒ�
						Device->SetRenderTarget(0, DownSamplingRT_[rtIndex].GetSurface());
						Device->SetDepthStencilSurface(DownSamplingRT_[rtIndex].GetDepthSurface());

						//�摜���N���A
						Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);

						Effect_->SetTechnique("YBlur");

						Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
						Effect_->BeginPass(0);
						
						//�T�C�Y���v�Z
						float size[2] = 
						{
							s_cast<float>(prevRT->GetSizeW()),	//����
							s_cast<float>(prevRT->GetSizeH())	//����
						};
						//�I�t�Z�b�g���v�Z
						float offset[] = 
						{
							0.0f,										//����
							16.0f / s_cast<float>(prevRT->GetSizeH()),	//����
						};

						//��ʃT�C�Y��ݒ�
						Effect_->SetValue("g_LuminanceTexSize", size, sizeof(size));
						//�I�t�Z�b�g��ݒ�
						Effect_->SetValue("g_Offset", offset, sizeof(size));
						//�d�݂�ݒ�
						Effect_->SetValue("g_Weight", Weights_, sizeof(Weights_));

						//�e�N�X�`���̐ݒ�
						Effect_->SetTexture( "g_Blur", prevRT->GetTexture());
						
						Effect_->CommitChanges();

						postEffect->RenderFullScreen();

						Effect_->EndPass();
						Effect_->End();
					}

					//XBlur�p��ݒ�
					prevRT = &DownSamplingRT_[rtIndex];
					rtIndex++;

				}//YBlur

			}//�P�x���ڂ���

			//�{�P�t�B���^�[�̍���
			{
				
				//�A���t�@�u�����h���Ȃ��ɐݒ�
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

				Device->SetRenderTarget(0, CombineRT_.GetSurface());
				Device->SetDepthStencilSurface(CombineRT_.GetDepthSurface());

				//�摜���N���A
				Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);
				
				float offset[] = 
				{
					0.5f / s_cast<float>(CombineRT_.GetSizeW()),
					0.5f / s_cast<float>(CombineRT_.GetSizeH()),
				};
				
				Effect_->SetTechnique("Combine");

				Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
				Effect_->BeginPass(0);

				//�e�N�X�`���̐ݒ�
				Effect_->SetTexture( "g_CombineTex00", DownSamplingRT_[1].GetTexture());
				Effect_->SetTexture( "g_CombineTex01", DownSamplingRT_[3].GetTexture());
				Effect_->SetTexture( "g_CombineTex02", DownSamplingRT_[5].GetTexture());
				Effect_->SetTexture( "g_CombineTex03", DownSamplingRT_[7].GetTexture());
				Effect_->SetTexture( "g_CombineTex04", DownSamplingRT_[9].GetTexture());

				Effect_->SetValue( "g_Offset", offset, sizeof(offset));

				Effect_->CommitChanges();

				postEffect->RenderFullScreen();

				Effect_->EndPass();
				Effect_->End();

			}//�{�P�t�B���^�[�̍���

			//�u���[��
			{

				float offset[] =
				{
					0.5f / s_cast<float>(CombineRT_.GetSizeW()),
					0.5f / s_cast<float>(CombineRT_.GetSizeH())
				};

				//���C�������_�[�ɕύX
				Device->SetRenderTarget(0, ScreenRender().GetMainRenderTarget().GetSurface());
				Device->SetDepthStencilSurface(ScreenRender().GetMainRenderTarget().GetDepthSurface());

				//���Z�����B
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

				Effect_->SetTechnique("Final");

				Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
				Effect_->BeginPass(0);

				Effect_->SetTexture("g_Blur", CombineRT_.GetTexture());
				Effect_->SetValue("g_Offset", offset, sizeof(offset));

				Effect_->CommitChanges();

				postEffect->RenderFullScreen();
				
				Effect_->EndPass();
				Effect_->End();

				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			}//�u���[��

		}
	}

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	void Bloom::Release()
	{
	}

	/**
	* �d�݂��v�Z.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param dis The dis.
	*/
	void Bloom::UpdateWeight(float dis)
	{
		float total = 0;

		for (int i = 0; i < NUM_WEIGHTS; i++)
		{
			Weights_[i] = expf(-0.5f*(float)(i*i) / dis);

			total += 2.0f * Weights_[i];
		}

		//�K�i��
		for (int i = 0; i < NUM_WEIGHTS; i++)
		{
			Weights_[i] /= total;
		}
	}

}// namespace nkEngine