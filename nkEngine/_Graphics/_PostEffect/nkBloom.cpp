/**
 * @file _Graphics\_PostEffect\nkBloom.cpp
 *
 * ブルームクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkBloom.h"


namespace nkEngine
{

	/**
	 * 作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param config The configuration.
	 */
	void Bloom::Create(const BloomConfigS & config)
	{
		//有効フラグをコピー
		isEnable_ = config.isEnable_;

		if (isEnable_)
		{
			//内部解像度のサイズを計算
			int w = Engine().GetFrameW();
			int h = Engine().GetFrameH();

			//輝度レンダリングターゲットの作成
			LuminanceRT_.Create(w, h, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);

			//ブラーの初期化
			Blur_[0].Init(w, h, *LuminanceRT_.GetTexture());
			Blur_[1].Init(w, h, *Blur_[0].GetTexture());

			//エフェクトのロード
			Effect_ = EffectManager().LoadEffect("Bloom.fx");

		}
	}

	/**
	 * 描画.
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
			//デバイスの取得
			IDirect3DDevice9* Device = Engine().GetDevice();

			UpdateWeight(25.0f);

			//輝度摘出
			{

				//輝度に変更
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

			//ブラー
			for (int i = 0; i < 2; i++)
			{
				Blur_[i].Render();
			}

			//ブルーム
			{

				float offset[] =
				{
					0.5f / Blur_[1].GetSizeW(),
					0.5f / Blur_[1].GetSizeH()
				};

				//メインレンダーに変更
				Device->SetRenderTarget(0, ScreenRender().GetMainRenderTarget().GetSurface());
				Device->SetDepthStencilSurface(ScreenRender().GetMainRenderTarget().GetDepthSurface());

				//加算合成。
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
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	void Bloom::Release()
	{
	}

	/**
	* 重みを計算.
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