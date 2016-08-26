//カメラクラス
#pragma once

namespace nkEngine
{
	class CCamera
	{
	public:
		//コンストラクタ
		CCamera();

		//デストラクタ
		~CCamera();

		//更新
		void Update();

		//横回転
		//param[in] 回転量
		void SpinHorizontally(float rot);

		//縦回転
		//param[in] 回転量
		void SpinVertically(float rot);
		
		//ビュー行列の取得
		//return ビュー行列
		const D3DXMATRIX& GetViewMatrix()
		{
			return m_mView;
		}

		//プロジェクション行列の取得
		//return プロジェクション行列
		const D3DXMATRIX& GetProjectionMatrix()
		{
			return m_mProj;
		}

		//回転行列の取得
		//return 回転行列
		const D3DXMATRIX& GetRotationMatrix()
		{
			return m_mRotation;
		}

		//回転行列の逆行列取得
		//return 回転行列の逆行列
		const D3DXMATRIX& GetRotationInvMatrix()
		{
			return m_mRotationInv;
		}

		//カメラの視点の取得
		//return カメラの視点
		const D3DXVECTOR3& GetPosition()
		{
			return m_vNormalizeTarget;
		}

		//カメラの視点の設定
		//param[in] 視点ベクトル
		void SetPosition(const D3DXVECTOR3& pos)
		{
			D3DXVec3Normalize(&m_vNormalizeTarget, &pos);
		}

		//カメラの注視点の取得
		//return カメラの注視点
		const D3DXVECTOR3& GetTarget()
		{
			return m_vTarget;
		}

		//カメラの注視点の設定
		//param[in] 注視点ベクトル
		void SetTarget(const D3DXVECTOR3& target)
		{
			m_vTarget = target;
		}

		//カメラの上方向の取得
		//return カメラの上方向
		const D3DXVECTOR3& GetUp()
		{
			return m_vUp;
		}

		//カメラの上方向の設定
		//param[in] 上方向ベクトル
		void SetUp(const D3DXVECTOR3& up)
		{
			m_vUp = up;
		}

		//カメラの視点と注視点の距離を取得
		//return カメラの距離
		const float GetDistance()
		{
			return m_Distance;
		}

		//カメラの視点と注視点の処理を設定
		//param[in] 距離
		void SetDistance(const float dis)
		{
			m_Distance = dis;
		}

		//カメラの画角を取得
		//return カメラの画角
		const float GetFovy()
		{
			return m_Fovy;
		}

		//カメラの画角を設定
		//param[in] 画角
		void SetFovy(const float fovy)
		{
			m_Fovy = fovy;
		}

		//カメラのアスペクト比を取得
		//return カメラのアスペクト比
		const float GetAspect()
		{
			return m_Aspect;
		}

		//カメラのアスペクト比を設定
		//param[in] アスペクト比
		void SetAspect(const float aspect)
		{
			m_Aspect = aspect;
		}

		//カメラのニアを取得
		//return カメラのニア
		const float GetNear()
		{
			return m_Near;
		}

		//カメラのニアを設定
		//param[in] ニア
		void SetNear(const float fnear)
		{
			m_Near = fnear;
		}

		//カメラのファーを取得
		//return カメラのファー
		const float GetFar()
		{
			return m_Far;
		}

		//カメラのファーを設定
		//param[in] ファー
		void SetFar(const float ffar)
		{
			m_Far = ffar;
		}

	private:
		D3DXMATRIX m_mView; //ビュー行列
		D3DXMATRIX m_mProj; //プロジェクション行列
		D3DXMATRIX m_mRotation; //回転行列
		D3DXMATRIX m_mRotationInv; //回転行列の逆行列

		D3DXVECTOR3 m_vPosition; //カメラの視点
		D3DXVECTOR3 m_vTarget; //カメラの注視点
		D3DXVECTOR3 m_vNormalizeTarget; //カメラの注視点
		D3DXVECTOR3 m_vUp; //カメラの上方向
		float m_Distance; //カメラの視点と注視点の距離

		float m_Fovy;		//画角
		float m_Aspect;	//アスペクト比
		float m_Near;		//ニア
		float m_Far;		//ファー

	};
}