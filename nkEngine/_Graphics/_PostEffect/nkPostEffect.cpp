/**
 * @file _Graphics\_PostEffect\nkPostEffect.cpp
 *
 * ポストエフェクトクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkPostEffect.h"

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
	void PostEffect::Create(const GraphicsConfigS& config)
	{

		//アンチエイリアシングの初期化
		AntiAliasing_.Create(config.AntiAliasingConfig_);
		//ブルームの初期化
		Bloom_.Create(config.BloomConfig_);

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
		//プリミティブの初期化
		Primitive_.Create(
			Primitive::TypeE::TriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			IndexFormatE::IndexFormat16,
			ib
		);

	}

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	void PostEffect::Render()
	{
	
		//ブルームの描画
		Bloom_.Render(this);
		//アンチエイリアスの描画
		AntiAliasing_.Render(this);

	}

	/**
	 * フルスクリーンの描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	void PostEffect::RenderFullScreen()
	{
		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());
	
	}

}// namespace nkEngine