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
		 * 更新.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Update();

		/**
		 * 描画.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Render();

		/**
		 * カメラ設定.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param [in,out]	camera	If non-null, the camera.
		 */
		void SetCamera(Camera* camera)
		{
			Camera_ = camera;
		}

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

	private:

		/** プリミティブ. */
		Primitive Primitive_;
		/** エフェクト. */
		ID3DXEffect* Effect_;
		/** カメラ. */
		Camera* Camera_;
		/** トランスフォーム. */
		Transform* Transform_;
		/** テクスチャ. */
		Texture Texture_;
		/** ビルボードフラグ. */
		bool isBillboard_ = false;

	};

}// namespace nkEngine