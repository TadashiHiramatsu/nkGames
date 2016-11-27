#pragma once

namespace nkEngine
{
	//書きやすく短縮
	typedef shared_ptr<CSkinModelData> CSkinModelDataPtr;

	//スキンモデルのリソース管理
	class CSkinModelDataResources
	{
	private:
		//コンストラクタ
		CSkinModelDataResources();
		//デストラクタ
		~CSkinModelDataResources();
	
	public:

		static CSkinModelDataResources& GetInstance()
		{
			static CSkinModelDataResources instance;
			return instance;
		}

		//読み取り
		//param[out] スキンモデルデータハンドル
		//param[in]  ファイルパス
		//param[in]  アニメーション
		//param[in]  インスタンシングフラグ
		//param[in]  インスタンス数
		void Load(CSkinModelDataHandle& _SkinModelDataHandle, const char* _FilePath, CAnimation* _Anim, bool _isInstancing = false, int _NumInstancing = 0);

		//更新
		void Update();

	private:
		typedef map<int, CSkinModelDataPtr> CSkinModelDataMap;
		//インスタンシングしないが複数回使うモデルを保存
		CSkinModelDataMap SkinModelDataMap;
		//インスタンシングモデルを保存
		list<CSkinModelDataPtr> InstancingList;
	};

	static CSkinModelDataResources& SMDResources()
	{
		return CSkinModelDataResources::GetInstance();
	}
}