/**
 * @file _Graphics\nkEffectManager.h
 *
 * エフェクトマネージャクラスの定義.
 */
#pragma once

#include"nkEffect.h"

namespace nkEngine
{

	/**
	 * エフェクトマネージャクラス.
	 * シングルトンクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CEffectManager : Noncopyable
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CEffectManager()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CEffectManager()
		{
			Release();
		}
	
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
		Effect* LoadEffect(const char* filePath);

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
		map<int, Effect*> EffectDictinary_;

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