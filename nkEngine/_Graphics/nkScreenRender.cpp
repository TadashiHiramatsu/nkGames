/**
 * @file _Graphics\nkScreenRender.cpp
 *
 * シーンレンダークラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkScreenRender.h"

namespace nkEngine
{

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CScreenRender::Start()
	{
		//デバイスの取得
		Device_ = Engine().GetDevice();

		//メインレンダーターゲットの作成
		MainRT_[0].Create(Engine().GetFrameW(), Engine().GetFrameH(), 1, D3DFMT_A16B16G16R16F, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0);
		MainRT_[1].Create(Engine().GetFrameW(), Engine().GetFrameH(), 1, D3DFMT_A16B16G16R16F, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0);

		//バックバッファレンダーターゲットの作成
		LPDIRECT3DSURFACE9 rt, depth;
		Device_->GetRenderTarget(0, &rt);
		Device_->GetDepthStencilSurface(&depth);
		BackBufferRT_.SetSurface(rt);
		BackBufferRT_.SetDepthSurface(depth);

		//頂点バッファの作成
		static SShapeVertex_PT vb[] = 
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
		//インデックスバッファの作成
		static unsigned short ib[] = 
		{
			0,1,2,3
		};
		//プリミティブの作成
		Primitive_.Create(
			Primitive::TriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			IndexFormat16,
			ib
		);

		//エフェクトのロード
		Effect_ = EffectManager().LoadEffect("TransformedPrim.fx");

	}

	/**
	 * グラフィック関連の初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param config The configuration.
	 */
	void CScreenRender::StartGraphic(const GraphicsConfigS& config)
	{
		//シャドウクラスの初期化
		Shadow().Create(config.ShadowConfig_);

		//ポストエフェクトの初期化
		PostEffect_.Create(config);
	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CScreenRender::Loop()
	{
		//タイムの更新
		Time().Update();

		//DirectInputの更新
		Input().Update();
		//XInputの更新
		XInput().Update();

		//初期化されていないオブジェクトを初期化
		GameObjectManager().Start();

		//プリレンダリング前の更新
		GameObjectManager().PreUpdate();

		//プリレンダリング
		Shadow().Update(); 

		//更新
		GameObjectManager().Update();

		//Updateの後の更新
		GameObjectManager().PostUpdate();

		//削除登録されたGameObjectを削除
		GameObjectManager().Delete();

		//シーンの開始
		Device_->BeginScene();

		//プリレンダーの描画
		Shadow().Render();

		//レンダーターゲットをメインレンダーに設定
		Device_->SetRenderTarget(0, GetMainRenderTarget().GetSurface());
		Device_->SetDepthStencilSurface(GetMainRenderTarget().GetDepthSurface());
		Device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);

		//Renderの前の描画
		GameObjectManager().PreRender();

		//描画
		GameObjectManager().Render();

		//ポストエフェクトの描画
		PostEffect_.Render();

		//ポストエフェクトの後の描画
		GameObjectManager().PostRender();

		//バックバッファに書き込み
		BackBufferRender();

		//シーンの終了
		Device_->EndScene();
		Device_->Present(NULL, NULL, NULL, NULL);

	}

	/**
	 * バックバッファにレンダリング.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	void CScreenRender::BackBufferRender()
	{
		//レンダーターゲットをバックバッファに戻す
		Device_->SetRenderTarget(0, BackBufferRT_.GetSurface());
		Device_->SetDepthStencilSurface(BackBufferRT_.GetDepthSurface());
		Device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		//書き込まれているレンダリングターゲットを取得
		RenderTarget& rt = GetMainRenderTarget();

		Effect_->SetTechnique("TransformedPrim");

		//始まり
		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);
		
		//オフセット作成
		float offset[] = 
		{
			0.5f / Engine().GetFrameW(),
			0.5f / Engine().GetFrameH()
		};

		//テクスチャの設定
		Effect_->SetTexture("g_Texture", rt.GetTexture());
		//オフセットの設定
		Effect_->SetValue("g_Offset", offset, sizeof(offset));

		Effect_->CommitChanges();

		Device_->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device_->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device_->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device_->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		//終り
		Effect_->EndPass();
		Effect_->End();
	}

}// namespace nkEngine