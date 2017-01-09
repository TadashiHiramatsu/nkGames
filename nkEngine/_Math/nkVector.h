/**
 * @file	_Math\nkVector.h
 *
 * ベクタークラスの定義.
 */
#pragma once

namespace nkEngine
{
	/**
	 * ベクトル2クラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	class Vector2
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 */
		Vector2()
		{
		}

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 */
		Vector2(float x, float y)
		{
			x_ = x;
			y_ = y;
		}

	public:

		/**
		 * X値とY値.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 */
		struct { float x_, y_; };
	
	};

	/**
	 * ベクトル3クラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	class Vector3
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 */
		Vector3()
		{
		}

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 * @param	z	The z coordinate.
		 */
		Vector3(float x, float y, float z)
		{
			x_ = x;
			y_ = y;
			z_ = z;
		}

		/**
		 * 線形補間.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @details	this = v0 + (v1-v0) * t;
		 *
		 * @param	t 	float.
		 * @param	v0	const Vector3&.
		 * @param	v1	const Vector3&.
		 */
		void Lerp(float t, const Vector3& v0, const Vector3& v1)
		{
			x_ = v0.x_ + (v1.x_ - v0.x_) * t;
			y_ = v0.y_ + (v1.y_ - v0.y_) * t;
			z_ = v0.z_ + (v1.z_ - v0.z_) * t;
		}

		/**
		 * 引数に自身の値をコピーする.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @details	_dst = this;
		 *
		 * @tparam	TVector	vectorタイプ.
		 * @param [in,out]	dst	Destination for the.
		 */
		template<class TVector>
		void CopyTo(TVector& dst)const
		{
			dst.x = x_;
			dst.y = y_;
			dst.z = z_;
		}

		/**
		 * 要素を設定.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @details	this =.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 * @param	z	The z coordinate.
		 */
		void Set(float x, float y, float z)
		{
			x_ = x;
			y_ = y;
			z_ = z;
		}

		/**
		 * ベクトルの各要素を設定.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @tparam	TVector	Type of the vector.
		 * @param [in,out]	v	The v.
		 */
		template<class TVector>
		void Set(TVector& v)
		{
			x_ = v.x;
			y_ = v.y;
			z_ = v.z;
		}

		/**
		 * ベクトルの各要素を設定.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @param [in,out]	v	The v to set.
		 */
		void Set(btVector3& v)
		{
			x_ = v.x();
			y_ = v.y();
			z_ = v.z();
		}

	public:

		/**
		 * X値とY値とZ値.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 */
		struct { float x_, y_, z_; };

		/** The zero. */
		static const Vector3 Zero;
		/** The right. */
		static const Vector3 Right;
		/** The left. */
		static const Vector3 Left;
		/** The up. */
		static const Vector3 Up;
		/** The down. */
		static const Vector3 Down;
		/** The front. */
		static const Vector3 Front;
		/** The back. */
		static const Vector3 Back;
		/** The axis x coordinate. */
		static const Vector3 AxisX;
		/** The axis y coordinate. */
		static const Vector3 AxisY;
		/** The axis z coordinate. */
		static const Vector3 AxisZ;
		/** The one. */
		static const Vector3 One;

	};

}// namespace nkEngine