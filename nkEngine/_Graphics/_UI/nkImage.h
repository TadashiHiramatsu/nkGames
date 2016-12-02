#pragma once

namespace nkEngine
{

	//イメージクラス
	//2Dの画像をスクリーンに描画します
	class Image
	{
	public:

		//コンストラクタ
		Image();
		//デストラクタ
		~Image();

		//ファイルのロードを行う
		void Load(const char* _filepass);
		void Load(shared_ptr<CTexture>& _tex);
		void Load();

		//初期化のみを行う
		void Init();
		
		//描画
		void Render();
		
		//テクスチャを設定する
		void SetTexture(shared_ptr<CTexture>& _tex)
		{
			Texture = _tex;
		}

		//トランスフォームを設定する
		void SetTransform(RectTransform* _rt)
		{
			rectTransform = _rt;
		}

	private:
		ID3DXEffect* pEffect; //消さなくていい
		CPrimitive Primitive;
		shared_ptr<CTexture> Texture;

		RectTransform* rectTransform;
	};
}