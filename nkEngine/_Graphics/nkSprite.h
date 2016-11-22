#pragma once

namespace nkEngine
{
	struct SpriteTransform
	{
		D3DXVECTOR2 Position = D3DXVECTOR2(0, 0); //ポジション
		D3DXVECTOR2 Size = D3DXVECTOR2(100, 100);	//サイズ
		D3DXVECTOR2 Pivot = D3DXVECTOR2(0.5f, 0.5f);	//中心
		D3DXQUATERNION Rotation = D3DXQUATERNION(0, 0, 0, 1);	//回転
	};

	class CSprite
	{
	public:

		//コンストラクタ
		CSprite();
		
		//デストラクタ
		~CSprite();

		//ファイルのロードを行う
		void Load(const char* filepass);
		void Load();

		//初期化のみを行う
		void Init();
		
		//更新
		void Update();
		
		//描画
		void Render();
		
		//解放
		void Release();
		
		//テクスチャを設定する
		void SetTexture(CTexture* tex)
		{
			Texture = tex;
		}

		//トランスフォーム設定
		void SetSTransform(SpriteTransform* _ST)
		{
			STransform = _ST;
		}

	private:
		ID3DXEffect* m_pEffect = nullptr;
		CPrimitive Primitive;
		CTexture* Texture = nullptr;

		D3DXMATRIX  m_mWorld;

		SpriteTransform* STransform;
	};
}