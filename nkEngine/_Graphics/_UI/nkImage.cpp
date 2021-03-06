/**
 * @file _Graphics\_UI\nkImage.cpp
 *
 * イメージクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkImage.h"

namespace nkEngine
{

	/**
	* ファイルのロードを行う.
	* エフェクトとテクスチャ.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param filepass "Asset/Texture/"を省いたファイルパス.
	*/
	void Image::Load(const char * filepass)
	{
		Effect_ = EffectManager().LoadEffect("Image.fx");

		Texture_.reset(new Texture);
		Texture_->Load(filepass, true);

		if (!isInit)
		{
			Init();
		}
	}

	/**
	* ファイルのロードを行う　
	* エフェクトのみ.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*/
	void Image::Load()
	{
		Effect_ = EffectManager().LoadEffect("Image.fx");

		if (!isInit)
		{
			Init();
		}
	}

	/**
	* 初期化.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*/
	void Image::Init()
	{
		isMonochrome_ = false;

		static SShapeVertex_PT vb[] =
		{
			{
				-0.5f, 0.5f, 0.0f, 1.0f,
				0.0f, 0.0f
			},
			{
				0.5f, 0.5f, 0.0f, 1.0f,
				1.0f, 0.0f
			},
			{
				-0.5f, -0.5f, 0.0f, 1.0f,
				0.0f, 1.0f
			},
			{
				0.5f, -0.5f, 0.0f, 1.0f,
				1.0f, 1.0f
			},
		};
		static unsigned short ib[] =
		{
			0,1,2,3
		};

		//プリミティブの作成
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

		isInit = true;
	}

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Image::Render()
	{

		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		//アルファブレンディングを行う
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		//透過処理を行う
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		Device->SetRenderState(D3DRS_ZENABLE, FALSE);

		Effect_->SetTechnique("Tech");

		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);

		Effect_->SetMatrix("matWorld", &RectTransform_->WorldProjMatrix_);
		Effect_->SetTexture("g_diffuseTexture", Texture_.get());
		Effect_->SetValue("uvRect", &RectUV_, sizeof(RectUV_));
		Effect_->SetValue("color", &Color_, sizeof(Color_));
		Effect_->SetBool("isMonochrome", isMonochrome_);

		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);


	}

}// namespace nkEngine