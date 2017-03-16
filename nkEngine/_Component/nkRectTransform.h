/**
 * @file _Component\nkRectTransform.h
 *
 * レクトトランスフォームクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	* アンカープリセット.
	* アンカーの位置からの位置になる.
	*/
	enum class AnchorPresetE
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

	/**
	 * UI専用トランスフォーム.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class RectTransform : Noncopyable
	{
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
		~RectTransform()
		{
		}

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
		 * @param angle 回転量(度).
		 */
		void RotationZ(float angle)
		{
			Rotation_.RotationAxis(Vector3::AxisZ, angle);
		}

	public:

		/** アンカー.初期値は中心. */
		AnchorPresetE Anchor_ = AnchorPresetE::MiddleCenter;
		/** ポジション. */
		Vector3 Position_ = Vector3::Zero;
		/** 横幅. */
		float Width_ = 100;
		/** 縦幅. */
		float Height_ = 100;
		/** 中心. */
		Vector2 Pivot_ = Vector2(0.5f, 0.5f);
		/** 回転. */
		Quaternion Rotation_ = Quaternion::Identity;
		/** サイズ. */
		Vector2 Scale_ = Vector2::One;

	public:

		/** 親子関係を持つ親のRectTransformのポインタ. */
		RectTransform* Parent_ = nullptr;

		/** ワールド行列. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** ワールド行列(サイズなし) */
		Matrix WorldSizeOffMatrix_ = Matrix::Identity;

		/** プロジェクション行列. */
		Matrix ProjectionMatrix_ = Matrix::Identity;
		/** ワールドプロジェクション行列. */
		Matrix WorldProjMatrix_ = Matrix::Identity;

	};

}// namespace nkEngine