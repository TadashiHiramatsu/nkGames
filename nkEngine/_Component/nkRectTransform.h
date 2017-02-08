/**
 * @file _Component\nkRectTransform.h
 *
 * レクトトランスフォームクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * 衝突判定に使用する情報.
	 * 画面左上を0,0とする位置情報.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct BoxCollisionS
	{
	public:

		/** 上. */
		int Top_;
		/** 下. */
		int Bottom_;
		/** 左. */
		int Left_;
		/** 右. */
		int Right_;

	};

	/**
	 * UI専用トランスフォーム.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class RectTransform
	{
	public:

		/**   
		 * アンカープリセット.
		 * アンカーの位置からの位置になる. 
		 */
		enum AnchorPresetE
		{
			TopLeft,		//!< 左上
			TopCenter,		//!< 上中央
			TopRight,		//!< 右上
			MiddleLeft,		//!< 左中央
			MiddleCenter,	//!< 中心
			MiddleRight,	//!< 右中央
			BottomLeft,		//!< 左下
			BottomCenter,	//!< 下中央
			BottomRight,	//!< 右下
			AnchorPresetNum,//!< 数
		};

	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		RectTransform();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~RectTransform();

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * Z軸回転.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param value Degree値.
		 */
		void RotationZ(float value)
		{
			float z = D3DXToRadian(value);
			D3DXQuaternionRotationAxis(&Rotation_, &D3DXVECTOR3(0, 0, 1), z);
		}

	public:

		/** アンカー初期値は中心. */
		AnchorPresetE Anchor_;
		/** ポジション. */
		D3DXVECTOR3 Position_;
		/** 横幅. */
		float Width_;
		/** 縦幅. */
		float Height_;
		/** 中心. */
		D3DXVECTOR2 Pivot_;
		/** 回転. */
		D3DXQUATERNION Rotation_;
		/** サイズ. */
		D3DXVECTOR2 Scale_;

		/** 衝突レクト. */
		BoxCollisionS BoxCol_;

	public:

		/** 親子関係を持つ親のRectTransformのポインタ. */
		RectTransform* Parent_;

		/** ワールド行列. */
		D3DXMATRIX WorldMatrix_;
		/** ワールド行列(サイズなし) */
		D3DXMATRIX WorldSizeOffMatrix_;

		/** プロジェクション行列. */
		D3DXMATRIX ProjectionMatrix_;
		/** ワールドプロジェクション行列. */
		D3DXMATRIX WorldProjMatrix_;

	};

}// namespace nkEngine