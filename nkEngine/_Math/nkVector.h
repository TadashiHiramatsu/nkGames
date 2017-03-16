/**
 * @file	_Math\nkVector.h
 *
 * �x�N�g���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{
	class Matrix;

	/**
	 * �񎟌��x�N�g���N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	class Vector2
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 */
		Vector2()
		{
		}

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 */
		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		/**
		* ���Z.
		*
		* @param v �x�N�g��.
		*/
		void Add(const Vector2& v)
		{
			x += v.x;
			y += v.y;
		}

		/**
		* �������Ƒ������̉��Z�l���� +.
		*
		* @param v0 �x�N�g��.
		* @param v1	�x�N�g��.
		*/
		void Add(const Vector2& v0, const Vector2& v1)
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
		}

		/**
		* �������擾.
		*/
		float Length() const
		{
			return sqrt(LengthSq());
		}
		/**
		* �����̓����擾.
		*/
		float LengthSq() const
		{
			return x * x + y * y;
		}

	public:

		/**
		 * X�l��Y�l.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 */
		struct { float x, y; };
	
	public:

		/** �[��. */
		static const Vector2 Zero;
		/** ����. */
		static const Vector2 One;

	};

	/**
	 * �O�����x�N�g���N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	class Vector3
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 */
		Vector3()
		{
		}

		/**
		 * �R���X�g���N�^.
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
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
		 * ���`���.
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
			this->x = v0.x + (v1.x - v0.x) * t;
			this->y = v0.y + (v1.y - v0.y) * t;
			this->z = v0.z + (v1.z - v0.z) * t;
		}

		/**
		 * �����Ɏ��g�̒l���R�s�[����.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @details	_dst = this;
		 *
		 * @tparam	TVector	vector�^�C�v.
		 * @param [in,out]	dst	Destination for the.
		 */
		template<class TVector>
		void CopyTo(TVector& dst) const
		{
			dst.x = this->x;
			dst.y = this->y;
			dst.z = this->z;
		}

		/**
		 * �v�f��ݒ� =.
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
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
		 * �x�N�g���̊e�v�f��ݒ� =.
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
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		/**
		 * �x�N�g���̊e�v�f��ݒ� =.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @param [in,out]	v	The v to set.
		 */
		void Set(btVector3& v)
		{
			this->x = v.x();
			this->y = v.y();
			this->z = v.z();
		}

		/**
		* �x�N�g�������Z +=.
		*
		* @param v	�x�N�g��.
		*/
		void Add(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}
		/**
		* �������Ƒ������̉��Z�l���� +.
		*
		* @param v0 �x�N�g��.
		* @param v1	�x�N�g��.
		*/
		void Add(const Vector3& v0, const Vector3& v1)
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
			z = v0.z + v1.z;
		}

		/**
		* �x�N�g���̌��Z -=.
		*
		* @param v	�x�N�g��.
		*/
		void Sub(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}
		/**
		* �������Ƒ������̌��Z�l���� -. 
		*
		* @param v0 �x�N�g��.
		* @param v1	�x�N�g��.
		*/
		void Sub(const Vector3& v0, const Vector3& v1)
		{
			x = v0.x - v1.x;
			y = v0.y - v1.y;
			z = v0.z - v1.z;
		}

		/**
		* ����.
		*
		* @param v	�x�N�g��.
		*/
		float Dot(const Vector3& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		/**
		* �O��.
		*
		* @param v	�x�N�g��.
		*/
		void Cross(const Vector3& v)
		{
			float _x = (y * v.z) - (v.y * z);
			float _y = (z * v.x) - (v.z * x);
			float _z = (x * v.y) - (v.x * y);
			x = _x;
			y = _y;
			z = _z;
		}
		/**
		* �������Ƒ������̊O�ϒl����.
		*
		* @param v0 �x�N�g��.
		* @param v1	�x�N�g��.
		*/
		void Cross(const Vector3& v0, const Vector3& v1)
		{
			float _x = (v0.y * v1.z) - (v1.y * v0.z);
			float _y = (v0.z * v1.x) - (v1.z * v0.x);
			float _z = (v0.x * v1.y) - (v1.x * v0.y);
			x = _x;
			y = _y;
			z = _z;
		}

		/**
		* �������擾.
		*/
		float Length() const
		{
			return sqrt(LengthSq());
		}
		/**
		* �����̓����擾.
		*/
		float LengthSq() const
		{
			return x * x + y * y + z * z;
		}

		/**
		* �g�� *=.
		*
		* @param s	�g��l.
		*/
		void Scale(float s)
		{
			x *= s;
			y *= s;
			z *= s;
		}

		/**
		* ���K��.
		*/
		void Normalize()
		{
			float len = Length();
			if (len > 0.0f)
			{
				x /= len;
				y /= len;
				z /= len;
			}
			else
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			}
		}

		/**
		* ���Z /=.
		*
		* @param d ���Z�l.
		*/
		void Div(float d)
		{
			x /= d;
			y /= d;
			z /= d;
		}

		/**
		* �����̍s��ɂ��x�N�g�����g�����X�t�H�[������.
		*
		* @param m �s��.
		*/
		void TransformCoord(const Matrix& m)
		{
			D3DXVec3TransformCoord(r_cast<D3DXVECTOR3*>(this), r_cast<const D3DXVECTOR3*>(this), r_cast<const D3DXMATRIX*>(&m));
		}

	public:

		/**
		 * X�l��Y�l��Z�l.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 */
		struct { float x, y, z; };

	public:

		/** �[��. */
		static const Vector3 Zero;
		/** �E. */
		static const Vector3 Right;
		/** ��. */
		static const Vector3 Left;
		/** ��. */
		static const Vector3 Up;
		/** ��. */
		static const Vector3 Down;
		/** �O. */
		static const Vector3 Front;
		/** ��. */
		static const Vector3 Back;
		/** The axis x coordinate. */
		static const Vector3 AxisX;
		/** The axis y coordinate. */
		static const Vector3 AxisY;
		/** The axis z coordinate. */
		static const Vector3 AxisZ;
		/** �C�`. */
		static const Vector3 One;

	};

	/**
	* �l�����x�N�g���N���X.
	*/
	class Vector4
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		Vector4()
		{
		}

		/**
		* �R���X�g���N�^.
		*/
		Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		/**
		* �x�N�g���̊e�v�f����.
		*
		* @param	x	The x coordinate.
		* @param	y	The y coordinate.
		* @param	z	The z coordinate.
		* @param	w	The w coordinate.
		*/
		void Set(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		/**
		* �����̎O�����x�N�g���ő��.
		* w�ɂ�1.0���ݒ肳��܂�.
		*/
		void Set(const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = 1.0f;
		}

		/**
		* ���Z.
		*
		* @param v	�x�N�g��.
		*/
		void Add(const Vector4& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}
		/**
		* �������Ƒ������̉��Z�l����.
		*
		* @param v0 �x�N�g��.
		* @param v1	�x�N�g��.
		*/
		void Add(const Vector4& v0, const Vector4& v1)
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
			z = v0.z + v1.z;
			w = v0.w + v1.w;
		}

		/**
		* ���Z.
		*
		* @param v	�x�N�g��.
		*/
		void Sub(const Vector4& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}
		/**
		* �������Ƒ������̌��Z�l����.
		*
		* @param v0 �x�N�g��.
		* @param v1	�x�N�g��.
		*/
		void Sub(const Vector4& v0, const Vector4& v1)
		{
			x = v0.x - v1.x;
			y = v0.y - v1.y;
			z = v0.z - v1.z;
			w = v0.w - v1.w;
		}

		/**
		* ����.
		*/
		float Dot(const Vector4& v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		/**
		* �������擾.
		*/
		float Length() const
		{
			return sqrt(LengthSq());
		}
		/**
		* �����̓����擾.
		*/
		float LengthSq() const
		{
			return x * x + y * y + z * z + w * w;
		}

		/**
		* �g��.
		*
		* @param s	�g��l.
		*/
		void Scale(float s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
		}

	public:

		/**
		* X�l��Y�l��Z�l��W�l.
		*/
		struct { float x, y, z, w; };

	public:

		static const Vector4 Zero;
	};

	/**
	* �N�H�[�^�j�I���N���X.
	* �l����.
	*/
	class Quaternion : public Vector4
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		Quaternion()
		{
		}

		/**
		* �R���X�g���N�^.
		*/
		Quaternion(float x, float y, float z, float w) :
			Vector4(x, y, z, w)
		{
		}

		/**
		* �C�ӂ̎����̉�].
		*
		* @param axis	�C�ӂ̎��x�N�g��.
		* @param angle	��]�l(�x).
		*/
		void RotationAxis(const Vector3& axis, float angle)
		{
			float s;
			float halfAngle = D3DXToRadian(angle) * 0.5f;
			s = sin(halfAngle);
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
			w = cos(halfAngle);
		}

		/**
		* �N�H�[�^�j�I�����m�̐�.
		*
		* @param rot	�N�H�[�^�j�I��.
		*/
		void Multiply(const Quaternion& rot)
		{
			float pw, px, py, pz;
			float qw, qx, qy, qz;

			pw = w; px = x; py = y; pz = z;
			qw = rot.w; qx = rot.x; qy = rot.y; qz = rot.z;

			w = pw * qw - px * qx - py * qy - pz * qz;
			x = pw * qx + px * qw + py * qz - pz * qy;
			y = pw * qy - px * qz + py * qw + pz * qx;
			z = pw * qz + px * qy - py * qx + pz * qw;
		}
		/**
		* �������Ƒ������̃N�H�[�^�j�I���̐ς���.
		* @param rot0	�N�H�[�^�j�I��.
		* @param rot1	�N�H�[�^�j�I��.
		*/
		void Multiply(const Quaternion& rot0, const Quaternion& rot1)
		{
			float pw, px, py, pz;
			float qw, qx, qy, qz;

			pw = rot0.w; px = rot0.x; py = rot0.y; pz = rot0.z;
			qw = rot1.w; qx = rot1.x; qy = rot1.y; qz = rot1.z;

			w = pw * qw - px * qx - py * qy - pz * qz;
			x = pw * qx + px * qw + py * qz - pz * qy;
			y = pw * qy - px * qz + py * qw + pz * qx;
			z = pw * qz + px * qy - py * qx + pz * qw;
		}

	public:

		/** �f��. */
		static const Quaternion Identity;

	};

}// namespace nkEngine