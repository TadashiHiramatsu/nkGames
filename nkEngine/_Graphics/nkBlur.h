//ブラー
#pragma once

namespace nkEngine
{

	class CBlur
	{
	public:
		//コンストラクタ
		CBlur();
		
		//デストラクタ
		~CBlur();
		
		//初期化
		//param[in] 横幅
		//param[in] 縦幅
		//param[in] 元となるテクスチャ
		void Init(int w,int h,const CTexture& srcTexture);
		//描画
		void Render();

		//テクスチャを取得
		const CTexture* GetTexture()const
		{
			return m_rt[1].GetTexture();
		}

		int GetSizeW()
		{
			return m_srcTexWH[0];
		}

		int GetSizeH()
		{
			return m_srcTexWH[1];
		}

	private:
		CRenderTarget m_rt[2]; //ガウシアンブラーの結果を描きこむレンダリングターゲット
		const CTexture*	m_srcTexture; //ソースとなるテクスチャ
		ID3DXEffect* m_Effect; //エフェクト
		int m_srcTexWH[2]; //テクスチャの幅
		CSprite m_fullscreen;
	};
}