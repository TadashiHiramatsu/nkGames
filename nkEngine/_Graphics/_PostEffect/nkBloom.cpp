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
			LuminanceRT_.Create(w, h, 1, D3DFMT_A16B16G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

			for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++)
			{
				//シフト量の計算
				int shift = i + 1;

				//ダウンサンプリング用RTの添え字を計算
				int baseIndex = i * 2;
				
				//横ブラー用RTの作成
				DownSamplingRT_[baseIndex].Create(w >> shift, h >> (shift - 1), 1, D3DFMT_A16B16G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	
				//縦ブラー用RTの作成
				DownSamplingRT_[baseIndex + 1].Create(w >> shift, h >> shift, 1, D3DFMT_A16B16G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	
			}

			//ぼかし合成用RTの作成
			CombineRT_.Create(w >> 2, h >> 2, 1, D3DFMT_A16B16G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);			

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

			//重み計算
			UpdateWeight(25.0f);

			//輝度抽出
			{

				//輝度抽出用のレンダリングターゲットに変更
				Device->SetRenderTarget(0, LuminanceRT_.GetSurface());
				Device->SetDepthStencilSurface(LuminanceRT_.GetDepthSurface());

				//テクスチャのクリア
				Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);

				Effect_->SetTechnique("SamplingLuminance");

				Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
				Effect_->BeginPass(0);

				//テクスチャの設定
				Effect_->SetTexture("g_Scene", ScreenRender().GetMainRenderTarget().GetTexture());

				Effect_->CommitChanges();

				postEffect->RenderFullScreen();

				Effect_->EndPass();
				Effect_->End();

			}//輝度抽出

			//輝度をぼかす
			{
				//ループ用RTクラスのポインタ
				RenderTarget* prevRT = &LuminanceRT_;
				//ダウンサンプリング用RTの添え字
				int rtIndex = 0;

				for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++)
				{
					//XBlur
					{
						//ダウンサンプリング用RTのXBlur用をレンダリングターゲットに設定
						Device->SetRenderTarget(0, DownSamplingRT_[rtIndex].GetSurface());
						Device->SetDepthStencilSurface(DownSamplingRT_[rtIndex].GetDepthSurface());

						//画像をクリア
						Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);

						//テクニックを設定
						Effect_->SetTechnique("XBlur");

						Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
						Effect_->BeginPass(0);
						
						//画像サイズを計算
						float size[2] = 
						{
							s_cast<float>(prevRT->GetSizeW()),
							s_cast<float>(prevRT->GetSizeH())
						};
						//オフセットを計算
						float offset[] = 
						{
							16.0f / s_cast<float>(prevRT->GetSizeW()),
							0.0f
						};

						//画面サイズを設定
						Effect_->SetValue("g_LuminanceTexSize", size, sizeof(size));
						//オフセットを設定
						Effect_->SetValue("g_Offset", offset, sizeof(size));
						//重みを設定
						Effect_->SetValue("g_Weight", Weights_, sizeof(Weights_));

						//テクスチャを設定
						Effect_->SetTexture( "g_Blur", prevRT->GetTexture());

						Effect_->CommitChanges();

						postEffect->RenderFullScreen();

						Effect_->EndPass();
						Effect_->End();
					}//XBlur

					//YBlur用を設定
					prevRT = &DownSamplingRT_[rtIndex];
					rtIndex++;

					//YBlur
					{
						//ダウンサンプリング用RTのYBlur用をレンダリングターゲットに設定
						Device->SetRenderTarget(0, DownSamplingRT_[rtIndex].GetSurface());
						Device->SetDepthStencilSurface(DownSamplingRT_[rtIndex].GetDepthSurface());

						//画像をクリア
						Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);

						Effect_->SetTechnique("YBlur");

						Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
						Effect_->BeginPass(0);
						
						//サイズを計算
						float size[2] = 
						{
							s_cast<float>(prevRT->GetSizeW()),	//横幅
							s_cast<float>(prevRT->GetSizeH())	//高さ
						};
						//オフセットを計算
						float offset[] = 
						{
							0.0f,										//横幅
							16.0f / s_cast<float>(prevRT->GetSizeH()),	//高さ
						};

						//画面サイズを設定
						Effect_->SetValue("g_LuminanceTexSize", size, sizeof(size));
						//オフセットを設定
						Effect_->SetValue("g_Offset", offset, sizeof(size));
						//重みを設定
						Effect_->SetValue("g_Weight", Weights_, sizeof(Weights_));

						//テクスチャの設定
						Effect_->SetTexture( "g_Blur", prevRT->GetTexture());
						
						Effect_->CommitChanges();

						postEffect->RenderFullScreen();

						Effect_->EndPass();
						Effect_->End();
					}

					//XBlur用を設定
					prevRT = &DownSamplingRT_[rtIndex];
					rtIndex++;

				}//YBlur

			}//輝度をぼかす

			//ボケフィルターの合成
			{
				
				//アルファブレンドをなしに設定
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

				Device->SetRenderTarget(0, CombineRT_.GetSurface());
				Device->SetDepthStencilSurface(CombineRT_.GetDepthSurface());

				//画像をクリア
				Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);
				
				float offset[] = 
				{
					0.5f / s_cast<float>(CombineRT_.GetSizeW()),
					0.5f / s_cast<float>(CombineRT_.GetSizeH()),
				};
				
				Effect_->SetTechnique("Combine");

				Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
				Effect_->BeginPass(0);

				//テクスチャの設定
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

			}//ボケフィルターの合成

			//ブルーム
			{

				float offset[] =
				{
					0.5f / s_cast<float>(CombineRT_.GetSizeW()),
					0.5f / s_cast<float>(CombineRT_.GetSizeH())
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

				Effect_->SetTexture("g_Blur", CombineRT_.GetTexture());
				Effect_->SetValue("g_Offset", offset, sizeof(offset));

				Effect_->CommitChanges();

				postEffect->RenderFullScreen();
				
				Effect_->EndPass();
				Effect_->End();

				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			}//ブルーム

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

			total += 2.0f * Weights_[i];
		}

		//規格化
		for (int i = 0; i < NUM_WEIGHTS; i++)
		{
			Weights_[i] /= total;
		}
	}

}// namespace nkEngine