/**
 * @file _Graphics\_PostEffect\nkAntiAliasing.cpp
 *
 * �A���`�G�C���A�V���O�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkAntiAliasing.h"

namespace nkEngine
{

	/**
	 * �쐬.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param config The configuration.
	 */
	void AntiAliasing::Create(const AntiAliasingConfigS& config)
	{

		//�L���t���O���R�s�[
		isEnable_ = config.isEnable_;
		
		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("AntiAliasing.fx");

	}

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param [in,out] postEffect If non-null, the post effect.
	 */
	void AntiAliasing::Render(PostEffect* postEffect)
	{
		if (isEnable_)
		{
			//�L��.

			float texSize[2] =
			{
				Engine().GetFrameW(),
				Engine().GetFrameH(),
			};

			Effect_->SetTechnique("FXAA");

			Effect_->Begin(0, D3DXFX_DONOTSAVESTATE);
			Effect_->BeginPass(0);

			Effect_->SetTexture("g_Texture", ScreenRender().GetMainRenderTarget().GetTexture());
			Effect_->SetValue("g_TexSize", texSize, sizeof(texSize));

			Effect_->CommitChanges();

			//�����_�����O�^�[�Q�b�g�̕ύX
			ScreenRender().ToggleMainRenderTarget();

			//�����_�����O�^�[�Q�b�g��ݒ�
			Engine().GetDevice()->SetRenderTarget(0, ScreenRender().GetMainRenderTarget().GetSurface());
			Engine().GetDevice()->SetDepthStencilSurface(ScreenRender().GetMainRenderTarget().GetDepthSurface());

			postEffect->RenderFullScreen();

			Effect_->EndPass();
			Effect_->End();

		}
	}

}// namespace nkEngine