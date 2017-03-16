/**
 * @file _Graphics\_PostEffect\nkAntiAliasing.cpp
 *
 * アンチエイリアシングクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkAntiAliasing.h"

namespace nkEngine
{

	/**
	 * 作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param config The configuration.
	 */
	void AntiAliasing::Create(const AntiAliasingConfigS& config)
	{

		//有効フラグをコピー
		isEnable_ = config.isEnable_;
		
		//エフェクトのロード
		Effect_ = EffectManager().LoadEffect("AntiAliasing.fx");

	}

	/**
	 * 描画.
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
			//有効.

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

			//レンダリングターゲットの変更
			ScreenRender().ToggleMainRenderTarget();

			//レンダリングターゲットを設定
			Engine().GetDevice()->SetRenderTarget(0, ScreenRender().GetMainRenderTarget().GetSurface());
			Engine().GetDevice()->SetDepthStencilSurface(ScreenRender().GetMainRenderTarget().GetDepthSurface());

			postEffect->RenderFullScreen();

			Effect_->EndPass();
			Effect_->End();

		}
	}

}// namespace nkEngine