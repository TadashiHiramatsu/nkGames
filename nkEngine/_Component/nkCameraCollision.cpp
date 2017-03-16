/**
* カメラのコリジョンクラスの実装.
*/
#include"nkEngine/nkstdafx.h"
#include"nkCameraCollision.h"

namespace nkEngine
{

	/**
	* 衝突したときに呼ばれる関数オブジェクト.
	*/
	struct ConvexSweepCallbackS : public btCollisionWorld::ClosestConvexResultCallback
	{
	public:
		
		/**
		* コンストラクタ.
		*/
		ConvexSweepCallbackS() :
			btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f))
		{
		}

		/**
		* 何かのコールバック関数.
		*/
		virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{

			if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionAttr_Character)
			{
				//キャラクターは無視.
				return 1.0f;
			}

			//衝突.
			return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
		}

	};

	/**
	* 初期化.
	*
	* @param radius	カメラの半径.
	* @param posdir	カメラの視点方向ポインタ.
	* @param tar	カメラの注視点座標ポインタ.
	* @param dis	カメラの注視点から視点の距離
	*/
	void CameraCollision::Start(float radius, const Vector3* posdir, const Vector3* tar)
	{

		//カメラの視点を設定
		CameraPosDirection_ = posdir;
		//カメラの注視点を設定
		CameraTarget_ = tar;

		//半径を設定.
		Radius_ = radius;
		//コライダー作成
		Collider_.Create(Radius_);

	}

	/**
	* 更新.
	*/
	void CameraCollision::Update()
	{
		//カメラの視点を計算
		Vector3 pos = *CameraPosDirection_;
		pos.Scale(DefaultDistance_);
		pos.Add(*CameraTarget_);

		//注視点から視点へのベクトル.
		Vector3 toTarget;

		toTarget.Sub(pos, *CameraTarget_);

		if (toTarget.LengthSq() < FLT_EPSILON)
		{
			//視点と注視点がほぼ同じ座標にあるの判定をしない.
			return;
		}

		//レイを作成する.
		btTransform btStart, btEnd;
		btStart.setIdentity();
		btEnd.setIdentity();

		//注視点をスタート位置に設定
		btStart.setOrigin(btVector3(CameraTarget_->x, CameraTarget_->y, CameraTarget_->z));
		//視点をエンド位置に設定
		btEnd.setOrigin(btVector3(pos.x, pos.y, pos.z));
		
		//コールバックオブジェクト.
		ConvexSweepCallbackS callback;

		Physics().ConvexSweepTest((const btConvexShape*)Collider_.GetBody(), btStart, btEnd, callback);

		if (callback.hasHit())
		{
			//視点と注視点の間に障害物があったので距離を縮める.

			//衝突した座標.
			Vector3 hitpos;
			hitpos.Set(callback.m_hitPointWorld);
			
			//衝突した座標座標から注視点へのベクトル.
			Vector3 toHitPos;
			toHitPos.Sub(*CameraTarget_, hitpos);

			//衝突した座標座標から注視点への距離.
			float len = toHitPos.Length();

			//通常の距離よりも短ければ設定.
			Distance_ = min(DefaultDistance_,len - Radius_);
		}
		else
		{
			//距離を通常設定.
			Distance_ = DefaultDistance_;
		}
	
	}

}