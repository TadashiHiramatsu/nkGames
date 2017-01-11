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
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Bloom::Bloom()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Bloom::~Bloom()
	{
	}

	/**
	* 作成.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param isEnable True if this object is enable.
	*/
	void Bloom::Create(bool isEnable)
	{

		if (isEnable)
		{
			//内部解像度のサイズを計算
			int w = Engine().GetFrameW();
			int h = Engine().GetFrameH();

			//輝度レンダリングターゲットの作成
			LuminanceRT_.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

			//ブラーの初期化
			Blur_[0].Init(w, h, *LuminanceRT_.GetTexture());
			Blur_[1].Init(w, h, *Blur_[0].GetTexture());

			//エフェクトのロード
			Effect_ = EffectManager().LoadEffect("bloom.fx");
			
			isEnable_ = isEnable;

			static SShapeVertex_PT vertex[] = 
			{
				{
					-1.0f, 1.0f, 0.0f, 1.0f,
					0.0f, 0.0f
				},
				{
					1.0f, 1.0f, 0.0f, 1.0f,
					1.0f, 0.0f
				},
				{
					-1.0f, -1.0f, 0.0f, 1.0f,
					0.0f, 1.0f
				},
				{
					1.0f, -1.0f, 0.0f, 1.0f,
					1.0f, 1.0f
				},
			};
			static unsigned short index[] =
			{
				0,1,2,3
			};
			
			Primitive_.Create(
				Primitive::TriangleStrip,
				4,
				sizeof(SShapeVertex_PT),
				scShapeVertex_PT_Element,
				vertex,
				4,
				IndexFormat16,
				index
			);
		}
	}

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Bloom::Render()
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

				Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
				Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
				Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
				Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

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

				Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
				Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
				Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
				Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

				Effect_->EndPass();
				Effect_->End();

				Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			}

		}

	}

	/**
	* Updates the weight described by dis.
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