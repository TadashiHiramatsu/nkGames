/**
 * @file	_Math\nkVector.h
 *
 * Declares the nk vector class.
 */
#pragma once

namespace nkEngine
{
	/**
	 * �x�N�g��2.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	class Vector2
	{
	public:


		/**
		 * �f�t�H���g�R���X�g���N�^.
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
		 * @param	_x	The x coordinate.
		 * @param	_y	The y coordinate.
		 */
		Vector2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

	public:
		struct { float x, y; };
	};

	/**
	 * �x�N�g��3�N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	class Vector3
	{
	public:

		/**
		 * �f�t�H���g�R���X�g���N�^.
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
		 * @param	_x	The x coordinate.
		 * @param	_y	The y coordinate.
		 * @param	_z	The z coordinate.
		 */
		Vector3(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		/**
		 * ���`���.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @details	this = v0 + (v1-v0) * t;
		 *
		 * @param	_t 	float.
		 * @param	_v0	const Vector3&.
		 * @param	_v1	const Vector3&.
		 */
		void Lerp(float _t, const Vector3& _v0, const Vector3& _v1)
		{
			x = _v0.x + (_v1.x - _v0.x) * _t;
			y = _v0.y + (_v1.y - _v0.y) * _t;
			z = _v0.z + (_v1.z - _v0.z) * _t;
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
		 * @param [in,out]	_dst	Destination for the.
		 */
		template<class TVector>
		void CopyTo(TVector& _dst)const
		{
			_dst.x = x;
			_dst.y = y;
			_dst.z = z;
		}

		/**
		 * �x�N�g���̊e�v�f��ݒ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 * 			
		 * @details this = 
		 *
		 * @param	_x	The x coordinate.
		 * @param	_y	The y coordinate.
		 * @param	_z	The z coordinate.
		 */
		void Set(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		/**
		 * �x�N�g���̊e�v�f��ݒ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @tparam	TVector	Type of the vector.
		 * @param [in,out]	_v	The v.
		 */
		template<class TVector>
		void Set(TVector& _v)
		{
			x = _v.x;
			y = _v.y;
			z = _v.z;
		}

		/**
		 * �x�N�g���̊e�v�f��ݒ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2016/12/30
		 *
		 * @param [in,out]	_v	The v to set.
		 */
		void Set(btVector3& _v)
		{
			this->x = _v.x();
			this->y = _v.y();
			this->z = _v.z();
		}

	public:
		struct { float x, y, z; };

		static const Vector3 Zero;
		static const Vector3 Right;
		static const Vector3 Left;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Front;
		static const Vector3 Back;
		static const Vector3 AxisX;
		static const Vector3 AxisY;
		static const Vector3 AxisZ;
		static const Vector3 One;
	};
}