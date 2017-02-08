/**
 * @file _Graphics\_UI\nkImage.cpp
 *
 * �C���[�W�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkImage.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Image::Image() :
		RectUV_(D3DXVECTOR4(0, 0, 1, 1)),
		Color_(D3DXVECTOR4(1, 1, 1, 1)),
		RectTransform_(nullptr),
		Effect_(nullptr)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Image::~Image()
	{
	}

	/**
	* �t�@�C���̃��[�h���s��.
	* �G�t�F�N�g�ƃe�N�X�`��.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param _filepass "Asset/Texture/"���Ȃ����t�@�C���p�X.
	*/
	void Image::Load(const char * filepass)
	{
		Effect_ = EffectManager().LoadEffect("Image.fx");

		Texture_.reset(new Texture);
		Texture_->Load(filepass,true);

		Init();
	}

	/**
	* �t�@�C���̃��[�h���s��.
	* �G�t�F�N�g�̂�.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*
	* @param [in,out] _tex The tex to load.
	*/
	void Image::Load(shared_ptr<Texture>& tex)
	{
		Effect_ = EffectManager().LoadEffect("Image.fx");

		Texture_ = tex;

		Init();
	}

	/**
	* �t�@�C���̃��[�h���s���@
	* �G�t�F�N�g�̂�.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*/
	void Image::Load()
	{
		Effect_ = EffectManager().LoadEffect("Image.fx");

		Init();
	}

	/**
	* ������.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/09
	*/
	void Image::Init()
	{

		static SShapeVertex_PT vertex[] =
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
		static unsigned short index[] =
		{
			0,1,2,3
		};

		//�v���~�e�B�u�̍쐬
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

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Image::Render()
	{

		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		//�A���t�@�u�����f�B���O���s��
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		//���ߏ������s��
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		Effect_->SetTechnique("Tech");

		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);

		Effect_->SetMatrix("matWorld", &RectTransform_->WorldProjMatrix_);
		Effect_->SetTexture("g_diffuseTexture", Texture_.get());
		Effect_->SetValue("uvRect", &RectUV_, sizeof(RectUV_));
		Effect_->SetValue("color", &Color_, sizeof(Color_));

		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	}

}// namespace nkEngine