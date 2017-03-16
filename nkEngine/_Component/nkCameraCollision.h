/**
* カメラのコリジョンクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* カメラコリジョンクラス.
	* 一般的な三人称視点のゲームカメラのコリジョン.
	*/
	class CameraCollision : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		CameraCollision()
		{
		}

		/**
		* デストラクタ.
		*/
		~CameraCollision()
		{
		}

		/**
		* 初期化.
		*
		* @param radius	カメラの半径.
		* @param posdir	カメラの視点方向ポインタ.
		* @param tar	カメラの注視点座標ポインタ.
		*/
		void Start(float radius,const Vector3* posdir, const Vector3* tar);

		/**
		* 更新.
		*/
		void Update();

		/**
		* 注視点から視点の距離を取得.
		*/
		float GetDistance() const
		{
			return Distance_;
		}

		/**
		* 通常の距離を設定.
		*/
		void SetDefaultDistance(float value)
		{
			DefaultDistance_ = value;
		}

	private:

		const Vector3* CameraPosDirection_ = nullptr;
		/** Cameraの注視点ポインタ. */
		const Vector3* CameraTarget_ = nullptr;

		/** 球体コライダー. */
		SphereCollider Collider_;
		/** 半径. */
		float Radius_;

		/** 注視点から視点への距離. */
		float Distance_ = 10;
		/** 通常の距離. */
		float DefaultDistance_ = 10;

	};
}