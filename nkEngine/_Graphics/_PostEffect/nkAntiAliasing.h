/**
 * @file _Graphics\_PostEffect\nkAntiAliasing.h
 *
 * アンチエイリアシングクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * アンチエイリアシングクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class AntiAliasing
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		AntiAliasing();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~AntiAliasing();

		/**
		 * 初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Init();

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

	private:

		/** 有効フラグ. */
		bool isEnable_;
		/** エフェクト. */
		ID3DXEffect* Effect_;
		/** The primitive. */
		Primitive Primitive_;

	};
}