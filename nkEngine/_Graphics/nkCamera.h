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
	class Camera
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Camera();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Camera();

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
		 * @param rot 回転量。ラジアン.
		 */
		void SpinHorizontally(float rot);

		/**
		 * 縦回転.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param rot 回転量。ラジアン.
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
		const D3DXMATRIX& GetViewMatrix()
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
		const D3DXMATRIX& GetViewInvMatrix()
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
		const D3DXMATRIX& GetProjectionMatrix()
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
		const D3DXMATRIX& GetRotationMatrix()
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
		const D3DXMATRIX& GetRotationInvMatrix()
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
		const D3DXVECTOR3& GetPosition()
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
		void SetPosition(const D3DXVECTOR3& pos)
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
		const D3DXVECTOR3& GetPosDirection()
		{
			return PosDirection_;
		}

		/**
		 * カメラの視点方向ベクトルの設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param _dir 視点ベクトル.
		 */
		void SetPosDirection(const D3DXVECTOR3& _dir)
		{
			PosDirection_ = _dir;
		}

		/**
		 * カメラの注視点の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The target.
		 */
		const D3DXVECTOR3& GetTarget()
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
		void SetTarget(const D3DXVECTOR3& target)
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
		const D3DXVECTOR3& GetUp()
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
		void SetUp(const D3DXVECTOR3& up)
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
		const float GetDistance()
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
		void SetDistance(const float distance)
		{
			Distance_ = distance;
		}

		/**
		 * カメラの画角を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The fovy.
		 */
		const float GetFovy()
		{
			return Fovy_;
		}

		/**
		 * カメラの画角を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param fovy 画角.
		 */
		void SetFovy(const float fovy)
		{
			Fovy_ = fovy;
		}

		/**
		 * カメラのアスペクト比を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The aspect.
		 */
		const float GetAspect()
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
		void SetAspect(const float aspect)
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
		const float GetNear()
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
		void SetNear(const float fnear)
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
		const float GetFar()
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
		void SetFar(const float ffar)
		{
			Far_ = ffar;
		}

	private:

		/** ビュー行列. */
		D3DXMATRIX ViewMatrix_;
		/** ビュー行列の逆行列. */
		D3DXMATRIX ViewInvMatrix_;
		/** プロジェクション行列. */
		D3DXMATRIX ProjMatrix_;
		/** 回転行列. */
		D3DXMATRIX RotationMatrix_;
		/** 回転行列の逆行列. */
		D3DXMATRIX RotationInvMatrix_;

		/** カメラの視点. */
		D3DXVECTOR3 Position_;
		/** カメラの注視点. */
		D3DXVECTOR3 Target_;
		/** カメラの上方向. */
		D3DXVECTOR3 Up_;

		/** ポジションの方向ベクトル. */
		D3DXVECTOR3 PosDirection_;
		/** 距離. */
		float Distance_;

		/** 画角. */
		float Fovy_;
		/** アスペクト比. */
		float Aspect_;
		/** ニア. */
		float Near_;
		/** ファー. */
		float Far_;

		/** 下限. */
		float LowerLimit_;
		/** 上限. */
		float UpperLimit_;

	};

}// namespace nkEngine