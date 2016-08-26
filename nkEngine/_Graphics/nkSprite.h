#pragma once

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

namespace nkEngine
{

	struct SVertex
	{
		FLOAT x, y, z, w;
		DWORD color;
		FLOAT u, v;
	};

	class CSprite
	{
	public:
		CSprite();
		~CSprite();
		//�t�@�C���̃��[�h���s��
		void Load(const char* filepass);
		void Load();
		//�������݂̂��s��
		void Init();
		//�X�V
		void Update(D3DXVECTOR3, D3DXVECTOR3, float angle = 0);
		//�`��
		void Render();
		//�폜
		void Release();
		
		//�t���X�N���[���Ńv���~�e�B�u�݂̂�`�悷��
		void DrawPrimitiveOnly();

		//�e�N�X�`����ݒ肷��
		void SetTexture(IDirect3DTexture9* tex)
		{
			m_pTex = tex;
		}
	private:
		IDirect3DTexture9* m_pTex;
		ID3DXEffect* m_pEffect;
		IDirect3DVertexBuffer9* m_pVB;

		D3DXMATRIX  m_mWorld, m_mTrans, m_mScale, m_mRot;

		bool isLuminance;
		float Luminance;
	};
}