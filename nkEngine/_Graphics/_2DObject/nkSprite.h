/**
 * @file	_Graphics\_2DObject\nkSprite.h
 *
 * スプライトクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * スプライトクラス.
	 * 3D空間に板ポリを表示
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	class Sprite
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		Sprite();

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		~Sprite();

		/**
		 * 読み込み.
		 * 
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param	filePath	The file path to load.
		 */
		void Load(const char* filePath);

		/**
		 * 初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Start();

		/**
		 * 描画.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Render();

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/11
		 */
		void Release();

		/**
		 * トランスフォームの設定.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param [in,out]	transform	If non-null, the transform.
		 */
		void SetTransform(Transform* transform)
		{
			Transform_ = transform;
		}

		/**
		 * カメラのポインタを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/12
		 *
		 * @param [in,out] camera If non-null, the camera.
		 */
		void SetCamera(Camera* camera)
		{
			Camera_ = camera;
		}

	private:

		/** プリミティブ. */
		Primitive Primitive_;
		/** エフェクト. */
		ID3DXEffect* Effect_;
		/** トランスフォーム. */
		Transform* Transform_ = nullptr;
		/** テクスチャ. */
		Texture Texture_;
		/** カメラのポインタ. */
		Camera* Camera_;

	public:

		/** UV座標 x:左, y:上, z:右, w:下. */
		D3DXVECTOR4 RectUV_;
		/** 色. */
		D3DXVECTOR4 Color_;

	};

}// namespace nkEngine