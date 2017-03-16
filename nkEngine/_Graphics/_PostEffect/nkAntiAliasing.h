/**
 * @file _Graphics\_PostEffect\nkAntiAliasing.h
 *
 * アンチエイリアシングクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/** ポストエフェクトクラス. */
	class PostEffect;

	/**
	 * アンチエイリアシングクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class AntiAliasing : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		AntiAliasing()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~AntiAliasing()
		{
		}

		/**
		 * 作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param config The configuration.
		 */
		void Create(const AntiAliasingConfigS& config);

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param [in,out] postEffect The post effect.
		 */
		void Render(PostEffect* postEffect);

	private:

		/** 有効フラグ. */
		bool isEnable_ = false;
		/** エフェクト. */
		Effect* Effect_ = nullptr;

	};

}// namespace nkEngine