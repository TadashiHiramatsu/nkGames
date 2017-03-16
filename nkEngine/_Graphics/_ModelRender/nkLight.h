/**
 * @file _Graphics\_ModelRender\nkLight.h
 *
 * ライトクラスの定義
 */
#pragma once

namespace nkEngine
{

	/**
	 * ライトクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class Light : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		Light();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~Light()
		{
		}

		/**
		 * ディフューズライトの向きを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param no	   ライトの番号.
		 * @param lightDir ライトの方向、正規化済みベクトル.
		 */
		void SetDiffuseLightDirection(int no, const Vector3& lightDir)
		{
			NK_ASSERT(no < LIGHT_NUM, "ライトの数大杉ぃぃぃ");
			DiffuseLightDirection_[no] = lightDir;
		}

		/**
		 * ディフューズライトの向きを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param no ライトの番号.
		 *
		 * @return The diffuse light direction.
		 */
		const Vector3& GetDiffuseLightDirection(int no) const
		{
			return DiffuseLightDirection_[no];
		}

		/**
		 * ディフューズライトの色を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param no	   ライトの番号.
		 * @param lightColor ライトの色、0.0f～1.0fの値.
		 */
		void SetDiffuseLightColor(int no, const Vector4& lightColor)
		{
			NK_ASSERT(no < LIGHT_NUM, "ライトの色大杉ぃぃぃ");
			DiffuseLightColor_[no] = lightColor;
		}

		/**
		 * ディフューズライトの色を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param no The ライトの番号.
		 *
		 * @return The diffuse light color.
		 */
		const Vector4& GetDiffuseLightColor(int no) const
		{
			return DiffuseLightColor_[no];
		}

		/**
		 * アンビエントライトの強さを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param amb アンビエントの色.
		 */
		void SetAmbientLight(const Vector3& amb)
		{
			AmbientLight_ = amb;
		}

		/**
		 * アンビエントライトを取得.
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
		 * 自己発光色の設定.
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

		/** ライトの数. */
		const static int LIGHT_NUM = 6;

	private:

		/** 平行光源の方向. */
		Vector3 DiffuseLightDirection_[LIGHT_NUM];
		/** 平行光源の色. */
		Vector4	DiffuseLightColor_[LIGHT_NUM];
		/** 環境光. */
		Vector3	AmbientLight_;
		/** 自己発光色. */
		Vector3 EmissionLightColor_;

	};

}// namespace nkEngine