/**
 * @file _Graphics\nkEffectManager.h
 *
 * エフェクトマネージャクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * エフェクトマネージャクラス.
	 * シングルトンクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CEffectManager
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CEffectManager();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CEffectManager();
	
	public:

		/**
		 * エフェクトのロード.
		 * "Asset/Shader/"フォルダからロードします.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param filePath ファイルパス。"Asset/Shader/"を省いたファイルパス.
		 *
		 * @return ロードしたエフェクト.
		 */
		ID3DXEffect* LoadEffect(const char* filePath);

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * インスタンス取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return A reference to a CEffectManager.
		 */
		inline static CEffectManager& instance()
		{
			static CEffectManager instance;
			return instance;
		}

	private:
		/** エフェクトのディクショナリ、ファイルパスのハッシュ値をキーにもつ. */
		map<int, ID3DXEffect*> EffectDictinary_;
	};

	/**
	 * エフェクトマネージャクラスの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CEffectManager.
	 */
	inline static CEffectManager& EffectManager()
	{
		return CEffectManager::instance();
	}

}// namespace nkEngine