/**
 * @file	_Graphics\_2DObject\nkSprite.cpp
 *
 * スプライトクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSprite.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Sprite::Sprite() :
		RectUV_(D3DXVECTOR4(0, 0, 1, 1)),
		Color_(D3DXVECTOR4(1, 1, 1, 1))
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	Sprite::~Sprite()
	{
	}

	/**
	 * 読み込み.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 *
	 * @param	filePath	The file path to load.
	 */
	void Sprite::Load(const char * filePath)
	{
		//テクスチャのロード
		Texture_.Load(filePath);

		//エフェクトのロード
		Effect_ = EffectManager().LoadEffect("Sprite.fx");
	}

	/**
	 * 初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	void Sprite::Start()
	{
		//パーティクルの初期化
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
		short ib[] =
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
	}

	/**
	 * 描画.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	void Sprite::Render()
	{
		//ビュープロジェクション行列の計算
		D3DXMATRIX viewProj;
		D3DXMatrixMultiply(&viewProj, &Camera_->GetViewMatrix(), &Camera_->GetProjectionMatrix());

		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		Effect_->SetTechnique("Sprite");

		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);

		Effect_->SetValue("g_mWorld", &Transform_->WorldMatrix_, sizeof(D3DXMATRIX));
		Effect_->SetValue("g_mViewProj", &viewProj, sizeof(D3DXMATRIX));

		Effect_->SetTexture("g_Texture", Texture_.GetTexture());

		Effect_->SetValue("g_RectUV", &RectUV_, sizeof(RectUV_));
		Effect_->SetValue("g_Color", &Color_, sizeof(Color_));
		
		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();
	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Sprite::Release()
	{
		Texture_.Release();
	}

}// namespace nkEngine