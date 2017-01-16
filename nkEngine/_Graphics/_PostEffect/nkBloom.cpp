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
			LuminanceRT_.Create(w, h, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);

			//�u���[�̏�����
			Blur_[0].Init(w, h, *LuminanceRT_.GetTexture());
			Blur_[1].Init(w, h, *Blur_[0].GetTexture());

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

			UpdateWeight(25.0f);

			//�P�x�E�o
			{

				//�P�x�ɕύX
				Device->SetRenderTarget(0, LuminanceRT_.GetSurface());
				Device->SetDepthStencilSurface(LuminanceRT_.GetDepthSurface());

				Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

				Effect_->SetTechnique("SamplingLuminance");

				Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
				Effect_->BeginPass(0);

				Effect_->SetTexture("g_Scene", ScreenRender().GetMainRenderTarget().GetTextureDX());

				Effect_->CommitChanges();

				postEffect->RenderFullScreen();

				Effect_->EndPass();
				Effect_->End();

			}

			//�u���[
			for (int i = 0; i < 2; i++)
			{
				Blur_[i].Render();
			}

			//�u���[��
			{

				float offset[] =
				{
					0.5f / Blur_[1].GetSizeW(),
					0.5f / Blur_[1].GetSizeH()
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

				Effect_->SetTexture("g_blur", Blur_[1].GetTexture()->GetTexture());
				Effect_->SetValue("g_offset", offset, sizeof(offset));

				Effect_->CommitChanges();

				postEffect->RenderFullScreen();
				
				Effect_->EndPass();
				Effect_->End();

				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			}

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

			if (0 == i)
			{
				total += Weights_[i];
			}
			else
			{
				total += 2.0f * Weights_[i];

			}
		}

		for (int i = 0; i < NUM_WEIGHTS; i++)
		{
			Weights_[i] /= total;
		}

	}

}// namespace nkEngine