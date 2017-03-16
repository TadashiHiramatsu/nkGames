/**
 * @file _Graphics\nkCamera.h
 *
 * カメラクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * カメラクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Camera : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Camera()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Camera()
		{
		}

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();

		/**
		 * 横回転.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param rot 回転量(度).
		 */
		void SpinHorizontally(float rot);

		/**
		 * 縦回転.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param rot 回転量(度).
		 */
		void SpinVertically(float rot);

		/**
		 * ビュー行列の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The view matrix.
		 */
		const Matrix& GetViewMatrix() const
		{
			return ViewMatrix_;
		}

		/**
		 * ビュー行列の逆行列の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The view inverse matrix.
		 */
		const Matrix& GetViewInvMatrix() const
		{
			return ViewInvMatrix_;
		}

		/**
		 * プロジェクション行列の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The projection matrix.
		 */
		const Matrix& GetProjectionMatrix() const
		{
			return ProjMatrix_;
		}

		/**
		 * 回転行列の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The rotation matrix.
		 */
		const Matrix& GetRotationMatrix() const
		{
			return RotationMatrix_;
		}

		/**
		 * 回転行列の逆行列取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The rotation inverse matrix.
		 */
		const Matrix& GetRotationInvMatrix() const
		{
			return RotationInvMatrix_;
		}

		/**
		 * カメラの視点の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The position.
		 */
		const Vector3& GetPosition() const
		{
			return Position_;
		}

		/**
		 * カメラの視点の設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param pos 視点ベクトル.
		 */
		void SetPosition(const Vector3& pos)
		{
			Position_ = pos;
		}

		/**
		 * カメラの視点方向ベクトルの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The position direction.
		 */
		const Vector3& GetPosDirection() const
		{
			return PosDirection_;
		}

		/**
		 * カメラの視点方向ベクトルの設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param dir 視点ベクトル.
		 */
		void SetPosDirection(const Vector3& dir)
		{
			PosDirection_ = dir;
		}

		/**
		 * カメラの注視点の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The target.
		 */
		const Vector3& GetTarget() const
		{
			return Target_;
		}

		/**
		 * カメラの注視点の設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param target 注視点ベクトル.
		 */
		void SetTarget(const Vector3& target)
		{
			Target_ = target;
		}

		/**
		 * カメラの上方向の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The up.
		 */
		const Vector3& GetUp() const
		{
			return Up_;
		}

		/**
		 * カメラの上方向の設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param up 上方向ベクトル.
		 */
		void SetUp(const Vector3& up)
		{
			Up_ = up;
		}

		/**
		 * カメラの視点、注視点間の距離を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The distance.
		 */
		const float GetDistance() const
		{
			return Distance_;
		}

		/**
		 * カメラの視点、注視点間の距離を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param distance 距離.
		 */
		void SetDistance(float distance)
		{
			Distance_ = distance;
		}

		/**
		 * カメラの画角を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The Angle_.
		 */
		float GetAngle() const
		{
			return Angle_;
		}

		/**
		 * カメラの画角を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param angle 画角.
		 */
		void SetAngle(float angle)
		{
			Angle_ = angle;
		}

		/**
		 * カメラのアスペクト比を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The aspect.
		 */
		float GetAspect() const
		{
			return Aspect_;
		}

		/**
		 * カメラのアスペクト比を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param aspect アスペクト比.
		 */
		void SetAspect(float aspect)
		{
			Aspect_ = aspect;
		}

		/**
		 * カメラのニアを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The near.
		 */
		float GetNear() const
		{
			return Near_;
		}

		/**
		 * カメラのニアを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param fnear ニア.
		 */
		void SetNear(float fnear)
		{
			Near_ = fnear;
		}

		/**
		 * カメラのファーを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The far.
		 */
		float GetFar() const
		{
			return Far_;
		}

		/**
		 * カメラのファーを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param ffar ファー.
		 */
		void SetFar(float ffar)
		{
			Far_ = ffar;
		}

	private:

		/** ビュー行列. */
		Matrix ViewMatrix_ = Matrix::Identity;
		/** ビュー行列の逆行列. */
		Matrix ViewInvMatrix_ = Matrix::Identity;
		/** プロジェクション行列. */
		Matrix ProjMatrix_ = Matrix::Identity;
		/** 回転行列. */
		Matrix RotationMatrix_ = Matrix::Identity;
		/** 回転行列の逆行列. */
		Matrix RotationInvMatrix_ = Matrix::Identity;

		/** カメラの視点. */
		Vector3 Position_ = Vector3::Zero;
		/** カメラの注視点. */
		Vector3 Target_ = Vector3::Zero;
		/** カメラの上方向. */
		Vector3 Up_ = Vector3::Up;

		/** ポジションの方向ベクトル. */
		Vector3 PosDirection_ = Vector3::Zero;
		/** 距離. */
		float Distance_ = 0;

		/** 画角. */
		float Angle_ = D3DXToRadian(45);
		/** アスペクト比. */
		float Aspect_ = 0.0f;
		/** ニア. */
		float Near_ = 0.1f;
		/** ファー. */
		float Far_ = 1200.0f;

		/** 下限. */
		float LowerLimit_ = -0.7f;
		/** 上限. */
		float UpperLimit_ = 0.7f;

	};

}// namespace nkEngine