#pragma once

namespace nkEngine
{
	class CEffectManager
	{
	public:
	
		//エフェクトのロード
		//param[in] ファイルパス
		//return ロードしたエフェクト
		ID3DXEffect* LoadEffect(const char* filePath);

		//リリース
		void Release();

		//インスタンス取得
		inline static CEffectManager& instance()
		{
			static CEffectManager instance;
			return instance;
		}
	private:
		//コンストラクタ
		CEffectManager();

		//デストラクタ
		~CEffectManager();
	private:
		map<int, ID3DXEffect*> m_effectDictinary; //エフェクトのディクショナリ、ファイルパスのハッシュ値をキーにもつ
	};
	inline static CEffectManager& EffectManager()
	{
		return CEffectManager::instance();
	}
}