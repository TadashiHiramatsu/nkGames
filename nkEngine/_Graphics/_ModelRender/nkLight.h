/**
 * @file _Graphics\_ModelRender\nkLight.h
 *
 * ���C�g�N���X�̒�`
 */
#pragma once

namespace nkEngine
{

	/**
	 * ���C�g�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class Light : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		Light();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~Light()
		{
		}

		/**
		 * �f�B�t���[�Y���C�g�̌�����ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param no	   ���C�g�̔ԍ�.
		 * @param lightDir ���C�g�̕����A���K���ς݃x�N�g��.
		 */
		void SetDiffuseLightDirection(int no, const Vector3& lightDir)
		{
			NK_ASSERT(no < LIGHT_NUM, "���C�g�̐��吙������");
			DiffuseLightDirection_[no] = lightDir;
		}

		/**
		 * �f�B�t���[�Y���C�g�̌������擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param no ���C�g�̔ԍ�.
		 *
		 * @return The diffuse light direction.
		 */
		const Vector3& GetDiffuseLightDirection(int no) const
		{
			return DiffuseLightDirection_[no];
		}

		/**
		 * �f�B�t���[�Y���C�g�̐F��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param no	   ���C�g�̔ԍ�.
		 * @param lightColor ���C�g�̐F�A0.0f�`1.0f�̒l.
		 */
		void SetDiffuseLightColor(int no, const Vector4& lightColor)
		{
			NK_ASSERT(no < LIGHT_NUM, "���C�g�̐F�吙������");
			DiffuseLightColor_[no] = lightColor;
		}

		/**
		 * �f�B�t���[�Y���C�g�̐F���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param no The ���C�g�̔ԍ�.
		 *
		 * @return The diffuse light color.
		 */
		const Vector4& GetDiffuseLightColor(int no) const
		{
			return DiffuseLightColor_[no];
		}

		/**
		 * �A���r�G���g���C�g�̋�����ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param amb �A���r�G���g�̐F.
		 */
		void SetAmbientLight(const Vector3& amb)
		{
			AmbientLight_ = amb;
		}

		/**
		 * �A���r�G���g���C�g���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The ambient light.
		 */
		const Vector3& GetAmbientLight() const
		{
			return AmbientLight_;
		}

		/**
		 * ���Ȕ����F�̐ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param color The color.
		 */
		void SetEmissionLightColor(const Vector3& color)
		{
			EmissionLightColor_ = color;
		}

	public:

		/** ���C�g�̐�. */
		const static int LIGHT_NUM = 6;

	private:

		/** ���s�����̕���. */
		Vector3 DiffuseLightDirection_[LIGHT_NUM];
		/** ���s�����̐F. */
		Vector4	DiffuseLightColor_[LIGHT_NUM];
		/** ����. */
		Vector3	AmbientLight_;
		/** ���Ȕ����F. */
		Vector3 EmissionLightColor_;

	};

}// namespace nkEngine