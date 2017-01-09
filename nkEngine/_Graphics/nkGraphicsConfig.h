/**
 * @file	_Graphics\nkGraphicsConfig.h
 *
 * 各シーンで設定するコンフィグの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * シャドウマップクラスのコンフィグ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct ShadowConfigS
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		ShadowConfigS()
		{
			isEnable_ = isSoftShadowMap_ = false;
			ShadowMapW_ = ShadowMapH_ = 512;
			Fur_ = 1000.0f;
			Near_ = 1.0f;
		}

	public:

		/** シャドウマップの有効フラグ. */
		bool isEnable_;
		/** シャドウマップの横幅. */
		int ShadowMapW_;
		/** シャドウマップの縦幅. */
		int ShadowMapH_;
		/** ソフトシャドウマップの有効フラグ. */
		bool isSoftShadowMap_;
		/** ファー. */
		float Fur_;
		/** ニア. */
		float Near_;
	};

	/**
	 * 各シーンで設定するグラフィックのコンフィグ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct SGraphicsConfig
	{
	public:

		/** The shadow configuration. */
		ShadowConfigS ShadowConfig_;

	};

}// namespace nkEngine