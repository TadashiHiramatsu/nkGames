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
		//ファイルのロードを行う
		void Load(const char* filepass);
		void Load();
		//初期化のみを行う
		void Init();
		//更新
		void Update(D3DXVECTOR3, D3DXVECTOR3, float angle = 0);
		//描画
		void Render();
		//削除
		void Release();
		
		//フルスクリーンでプリミティブのみを描画する
		void DrawPrimitiveOnly();

		//テクスチャを設定する
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