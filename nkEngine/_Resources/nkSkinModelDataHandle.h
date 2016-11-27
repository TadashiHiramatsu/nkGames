#pragma once

namespace nkEngine
{
	//スキンモデルのハンドルクラス
	class CSkinModelDataHandle
	{
	public:
		//スキンモデルデータの生ポインタを取得
		CSkinModelData* GetBody()
		{
			//クローン作成していたら
			if (SkinModelData)
			{
				return SkinModelData.get();
			}
			return OriginSkinModelData.get();
		}

		//初期化
		void Init(const shared_ptr<CSkinModelData>& _Skin, CAnimation* _Anim, bool _isClone);
	
	private:
		//オリジナルモデルデータ
		shared_ptr<CSkinModelData> OriginSkinModelData;
		//モデルデータ
		//アニメーションがある場合
		//クローン作成しないと同じ動きをしてしまう
		unique_ptr<CSkinModelData> SkinModelData;
	};
}