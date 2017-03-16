/**
* 行列クラスの定義.
*/
#pragma once

#include"nkVector.h"

namespace nkEngine
{
	
	/**
	* 行列クラス.
	*/
	class Matrix
	{
	public:

		/**
		* 行列の各要素を設定.
		*/
		template<class TMatrix>
		void Set(TMatrix& matrix)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0;j < 4; j++)
				{
					m[i][j] = matrix.m[i][j];
				}
			}
		}

		/**
		* ベクトルと3x3行列の積.
		*
		* @param[out] v ベクトル.
		*/
		void Mul3x3(Vector3& v) const
		{
			Vector3 vTmp = v;
			v.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0];
			v.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1];
			v.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2];
		}

		/**
		* 三次元ベクトルと行列の積.
		*
		* @param[out]	v	ベクトル.
		*/
		void Mul(Vector3& v) const
		{
			Vector3 vTmp = v;
			v.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0] + m[3][0];
			v.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1] + m[3][1];
			v.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2] + m[3][2];
		}

		/**
		* 四次元ベクトルと行列の積.
		*
		* @param[out]	v	ベクトル.
		*/
		void Mul(Vector4& v) const
		{
			Vector4 vTmp = v;
			v.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0] + vTmp.w * m[3][0];
			v.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1] + vTmp.w * m[3][1];
			v.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2] + vTmp.w * m[3][2];
			v.w = vTmp.x * m[0][3] + vTmp.y * m[1][3] + vTmp.z * m[2][3] + vTmp.w * m[3][3];
		}

		/**
		* 平行移動行列を作成.
		*
		* @param trans	ベクトル.
		*/
		void MakeTranslation(const Vector3& trans)
		{
			*this = Identity;
			m[3][0] = trans.x;
			m[3][1] = trans.y;
			m[3][2] = trans.z;
		}

		/**
		* X軸回りの回転行列を作成.
		*
		* @param angle	回転角度(度).
		*/
		void MakeRotationX(float angle)
		{
			D3DXMatrixRotationX(r_cast<D3DXMATRIX*>(this), D3DXToRadian(angle));
		}

		/**
		* Y軸回りの回転行列を作成.
		*
		* @param angle	回転角度(度).
		*/
		void MakeRotationY(float angle)
		{
			D3DXMatrixRotationY(r_cast<D3DXMATRIX*>(this), D3DXToRadian(angle));
		}

		/**
		* Z軸回りの回転行列を作成.
		*
		* @param angle	回転角度(度).
		*/
		void MakeRotationZ(float angle)
		{
			D3DXMatrixRotationZ(r_cast<D3DXMATRIX*>(this), D3DXToRadian(angle));
		}

		/**
		* クォータニオンから回転行列を作成.
		*
		* @param q	クォータニオン.
		*/
		void MakeRotationQuaternion(const Quaternion& q)
		{
			D3DXMatrixRotationQuaternion(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXQUATERNION*>(&q));
		}

		/**
		* 任意の軸回りの回転行列を作成.
		*
		* @param axis	任意の軸.
		* @param angle	回転量(度).
		*/
		void MakeRotationAxis(const Vector3& axis, float angle)
		{
			D3DXMatrixRotationAxis(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXVECTOR3*>(&axis), D3DXToRadian(angle));
		}

		/**
		* 拡大行列を作成.
		*
		* @param scale	拡大ベクトル.
		*/
		void MakeScaling(const Vector3& scale)
		{
			D3DXMatrixScaling(r_cast<D3DXMATRIX*>(this),scale.x, scale.y, scale.z);
		}

		/**
		* プロジェクション行列を作成.
		*
		* @param angle	画角(ラジアン).
		* @param aspect	アスペクト比.
		* @param fNear	近平面.
		* @param fFar	遠平面.
		*/
		void MakeProjection(float angle, float aspect, float fNear, float fFar)
		{
			D3DXMatrixPerspectiveFovLH(r_cast<D3DXMATRIX*>(this), angle, aspect, fNear, fFar);
		}

		/**
		* 平行投影行列を作成.
		*
		* @param w		ビューボリュームの幅.
		* @param h		ビューボリュームの高さ.
		* @param fNear	近平面.
		* @param fFar	遠平面.
		*/
		void MakeOrthoProjection(float w, float h, float fNear, float fFar)
		{
			D3DXMatrixOrthoLH(r_cast<D3DXMATRIX*>(this), w, h, fNear, fFar);
		}

		/**
		* ビュー行列を作成.
		*
		* @param pos	カメラの視点.
		* @param target	カメラの注視点.
		* @param up		カメラの上方向.
		*/
		void MakeLookAt(const Vector3& pos, const Vector3& target, const Vector3& up)
		{
			D3DXMatrixLookAtLH(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXVECTOR3*>(&pos), r_cast<const D3DXVECTOR3*>(&target), r_cast<const D3DXVECTOR3*>(&up));
		}

		/**
		* 行列同士の乗算を代入.
		*
		* @param m0	行列.
		* @param m1	行列.
		*/
		void Mul(const Matrix& m0, const Matrix& m1)
		{
			D3DXMatrixMultiply(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXMATRIX*>(&m0), r_cast<const D3DXMATRIX*>(&m1));
		}
		/**
		* 行列同士の乗算を代入.
		*
		* @param m0	行列.
		* @param m1	行列.
		*/
		void Mul(const D3DXMATRIX& m0, const D3DXMATRIX& m1)
		{
			D3DXMatrixMultiply(r_cast<D3DXMATRIX*>(this),&m0,&m1);
		}

		/**
		* 逆行列を計算.
		*
		* @param m	元となる行列.
		*/
		void Inverse(const Matrix& m)
		{
			D3DXMatrixInverse(r_cast<D3DXMATRIX*>(this), nullptr, r_cast<const D3DXMATRIX*>(&m));
		}

		/**
		* 回転行列の逆行列を計算.
		*
		* @param m	元となる行列.
		*/
		void Transpose(const Matrix& m)
		{
			D3DXMatrixTranspose(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXMATRIX*>(&m));
		}

	public:

		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};

	public:

		/** 単位行列. */
		static const Matrix Identity;

	};
}