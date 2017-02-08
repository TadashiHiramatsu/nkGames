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

		/** シャドウマップの有効フラグ. */
		bool isEnable_ = false;
		/** シャドウマップの横幅. */
		int ShadowMapW_ = 512;
		/** シャドウマップの縦幅. */
		int ShadowMapH_ = 512;
		/** ソフトシャドウマップの有効フラグ. */
		bool isSoftShadowMap_ = false;
		/** ファー. */
		float Far_ = 100.0f;
		/** ニア. */
		float Near_ = 1.0f;

	};

	/**
	 * ブルームクラスのコンフィグ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	struct BloomConfigS
	{
	public:

		/** ブルームの有効フラグ. */
		bool isEnable_ = false;
	
	};

	/**
	 * アンチエイリアスクラスのコンフィグ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	struct AntiAliasingConfigS
	{
	public:

		/** アンチエイリアスの有効フラグ. */
		bool isEnable_ = false;
	
	};

	/**
	 * 各シーンで設定するグラフィックのコンフィグ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct GraphicsConfigS
	{
	public:

		/** シャドウマップのコンフィグ. */
		ShadowConfigS ShadowConfig_;
		/** ブルームのコンフィグ. */
		BloomConfigS BloomConfig_;
		/** アンチエイリアスのコンフィグ. */
		AntiAliasingConfigS AntiAliasingConfig_;

	};

}// namespace nkEngine