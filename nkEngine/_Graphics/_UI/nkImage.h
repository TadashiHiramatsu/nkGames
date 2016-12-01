#pragma once

#include"nkUITransform.h"

namespace nkEngine
{
	class Image
	{
	public:

		//コンストラクタ
		Image();
		
		//デストラクタ
		~Image();

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
		void SetTexture(shared_ptr<CTexture>& tex)
		{
			Texture = tex;
		}

		void SetTransform(UITransform* _tf)
		{
			Transform = _tf;
		}

	private:
		ID3DXEffect* m_pEffect = nullptr;
		CPrimitive Primitive;
		shared_ptr<CTexture> Texture;

		UITransform* Transform;
	};
}