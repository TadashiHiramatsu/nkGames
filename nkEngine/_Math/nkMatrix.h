/**
* �s��N���X�̒�`.
*/
#pragma once

#include"nkVector.h"

namespace nkEngine
{
	
	/**
	* �s��N���X.
	*/
	class Matrix
	{
	public:

		/**
		* �s��̊e�v�f��ݒ�.
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
		* �x�N�g����3x3�s��̐�.
		*
		* @param[out] v �x�N�g��.
		*/
		void Mul3x3(Vector3& v) const
		{
			Vector3 vTmp = v;
			v.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0];
			v.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1];
			v.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2];
		}

		/**
		* �O�����x�N�g���ƍs��̐�.
		*
		* @param[out]	v	�x�N�g��.
		*/
		void Mul(Vector3& v) const
		{
			Vector3 vTmp = v;
			v.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0] + m[3][0];
			v.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1] + m[3][1];
			v.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2] + m[3][2];
		}

		/**
		* �l�����x�N�g���ƍs��̐�.
		*
		* @param[out]	v	�x�N�g��.
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
		* ���s�ړ��s����쐬.
		*
		* @param trans	�x�N�g��.
		*/
		void MakeTranslation(const Vector3& trans)
		{
			*this = Identity;
			m[3][0] = trans.x;
			m[3][1] = trans.y;
			m[3][2] = trans.z;
		}

		/**
		* X�����̉�]�s����쐬.
		*
		* @param angle	��]�p�x(�x).
		*/
		void MakeRotationX(float angle)
		{
			D3DXMatrixRotationX(r_cast<D3DXMATRIX*>(this), D3DXToRadian(angle));
		}

		/**
		* Y�����̉�]�s����쐬.
		*
		* @param angle	��]�p�x(�x).
		*/
		void MakeRotationY(float angle)
		{
			D3DXMatrixRotationY(r_cast<D3DXMATRIX*>(this), D3DXToRadian(angle));
		}

		/**
		* Z�����̉�]�s����쐬.
		*
		* @param angle	��]�p�x(�x).
		*/
		void MakeRotationZ(float angle)
		{
			D3DXMatrixRotationZ(r_cast<D3DXMATRIX*>(this), D3DXToRadian(angle));
		}

		/**
		* �N�H�[�^�j�I�������]�s����쐬.
		*
		* @param q	�N�H�[�^�j�I��.
		*/
		void MakeRotationQuaternion(const Quaternion& q)
		{
			D3DXMatrixRotationQuaternion(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXQUATERNION*>(&q));
		}

		/**
		* �C�ӂ̎����̉�]�s����쐬.
		*
		* @param axis	�C�ӂ̎�.
		* @param angle	��]��(�x).
		*/
		void MakeRotationAxis(const Vector3& axis, float angle)
		{
			D3DXMatrixRotationAxis(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXVECTOR3*>(&axis), D3DXToRadian(angle));
		}

		/**
		* �g��s����쐬.
		*
		* @param scale	�g��x�N�g��.
		*/
		void MakeScaling(const Vector3& scale)
		{
			D3DXMatrixScaling(r_cast<D3DXMATRIX*>(this),scale.x, scale.y, scale.z);
		}

		/**
		* �v���W�F�N�V�����s����쐬.
		*
		* @param angle	��p(���W�A��).
		* @param aspect	�A�X�y�N�g��.
		* @param fNear	�ߕ���.
		* @param fFar	������.
		*/
		void MakeProjection(float angle, float aspect, float fNear, float fFar)
		{
			D3DXMatrixPerspectiveFovLH(r_cast<D3DXMATRIX*>(this), angle, aspect, fNear, fFar);
		}

		/**
		* ���s���e�s����쐬.
		*
		* @param w		�r���[�{�����[���̕�.
		* @param h		�r���[�{�����[���̍���.
		* @param fNear	�ߕ���.
		* @param fFar	������.
		*/
		void MakeOrthoProjection(float w, float h, float fNear, float fFar)
		{
			D3DXMatrixOrthoLH(r_cast<D3DXMATRIX*>(this), w, h, fNear, fFar);
		}

		/**
		* �r���[�s����쐬.
		*
		* @param pos	�J�����̎��_.
		* @param target	�J�����̒����_.
		* @param up		�J�����̏����.
		*/
		void MakeLookAt(const Vector3& pos, const Vector3& target, const Vector3& up)
		{
			D3DXMatrixLookAtLH(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXVECTOR3*>(&pos), r_cast<const D3DXVECTOR3*>(&target), r_cast<const D3DXVECTOR3*>(&up));
		}

		/**
		* �s�񓯎m�̏�Z����.
		*
		* @param m0	�s��.
		* @param m1	�s��.
		*/
		void Mul(const Matrix& m0, const Matrix& m1)
		{
			D3DXMatrixMultiply(r_cast<D3DXMATRIX*>(this), r_cast<const D3DXMATRIX*>(&m0), r_cast<const D3DXMATRIX*>(&m1));
		}
		/**
		* �s�񓯎m�̏�Z����.
		*
		* @param m0	�s��.
		* @param m1	�s��.
		*/
		void Mul(const D3DXMATRIX& m0, const D3DXMATRIX& m1)
		{
			D3DXMatrixMultiply(r_cast<D3DXMATRIX*>(this),&m0,&m1);
		}

		/**
		* �t�s����v�Z.
		*
		* @param m	���ƂȂ�s��.
		*/
		void Inverse(const Matrix& m)
		{
			D3DXMatrixInverse(r_cast<D3DXMATRIX*>(this), nullptr, r_cast<const D3DXMATRIX*>(&m));
		}

		/**
		* ��]�s��̋t�s����v�Z.
		*
		* @param m	���ƂȂ�s��.
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

		/** �P�ʍs��. */
		static const Matrix Identity;

	};
}