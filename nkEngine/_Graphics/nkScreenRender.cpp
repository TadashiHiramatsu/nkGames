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
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CScreenRender::CScreenRender()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CScreenRender::~CScreenRender()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param initParam The init parameter.
	 */
	void CScreenRender::Start(const InitParamS& initParam)
	{
		//メインレンダーターゲットの作成
		MainRT_.Create(initParam.FrameBufferW_, initParam.FrameBufferH_, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

		//アンチエイリアシングの初期化
		AntiAliasing_.Init();

		//ブルームの初期化
		Bloom_.Create(false);

		//バックバッファレンダーターゲットの作成
		LPDIRECT3DSURFACE9 rt, depth;
		Engine().GetDevice()->GetRenderTarget(0, &rt);
		Engine().GetDevice()->GetDepthStencilSurface(&depth);
		BackBufferRT_.SetSurface(rt);
		BackBufferRT_.SetDepthSurface(depth);

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

		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		//シーンの開始
		Device->BeginScene();

		//レンダーターゲットをメインレンダーに設定
		Device->SetRenderTarget(0, MainRT_.GetSurface());
		Device->SetDepthStencilSurface(MainRT_.GetDepthSurface());
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//プリレンダーの描画
		Shadow().Render();

		//Renderの前の描画
		GameObjectManager().PreRender();

		//描画
		GameObjectManager().Render();

		//ポストエフェクト
		//Bloom_.Render();

		//レンダーターゲットをバックバッファに戻す
		Device->SetRenderTarget(0, BackBufferRT_.GetSurface());
		Device->SetDepthStencilSurface(BackBufferRT_.GetDepthSurface());
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//アンチエイリアシングの描画
		AntiAliasing_.Render();

		//ポストエフェクトの後の描画
		GameObjectManager().PostRender();

		//シーンの終了
		Device->EndScene();
		Device->Present(NULL, NULL, NULL, NULL);

		//削除登録されたGameObjectを削除
		GameObjectManager().Delete();
	}

}// namespace nkEngine