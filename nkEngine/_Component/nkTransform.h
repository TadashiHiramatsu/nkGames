/**
 * @file _Component\nkTransform.h
 *
 * トランスフォームクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * トランスフォームクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class Transform : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		Transform()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~Transform()
		{
		}

		/**
		 * ワールド行列などの更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * ビルボードする更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void BillboardUpdate(const Matrix& rot);
	
	public:

		/** 親子関係を持つ親のTransformクラスのポインタ. */
		Transform* Parent_ = nullptr;
		/** 親にする行列. */
		Matrix* ParentMatrix_ = nullptr;

		/** 位置ベクトル. */
		Vector3 Position_ = Vector3::Zero;
		/** 拡大ベクトル. */
		Vector3 Scale_ = Vector3::One;
		/** 回転ベクトル. */
		Quaternion Rotation_ = Quaternion::Identity;

		/** ローカルのワールド行列. */
		Matrix LocalMatrix_ = Matrix::Identity;
		/** ワールド行列. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** ワールド行列の逆行列. */
		Matrix WorldInvMatrix_ = Matrix::Identity;
		/** 回転行列. */
		Matrix RotationMatrix_ = Matrix::Identity;

	};

}// namespace nkEngine