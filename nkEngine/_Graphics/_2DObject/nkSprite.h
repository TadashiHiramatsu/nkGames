/**
 * @file	_Graphics\_2DObject\nkSprite.h
 *
 * Declares the nk sprite class.
 */
#pragma once

namespace nkEngine
{
	/**
	 * A sprite.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	class Sprite
	{
	public:

		/**
		 * Default constructor.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		Sprite();

		/**
		 * Destructor.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		~Sprite();

		/**
		 * Loads the given file path.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param	_FilePath	The file path to load.
		 */
		void Load(const char* _FilePath);

		/**
		 * Starts this object.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Start();

		/**
		 * Updates this object.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Update();

		/**
		 * Renders this object.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 */
		void Render();

		/**
		 * Sets a camera.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param [in,out]	_Camera	If non-null, the camera.
		 */
		void SetCamera(CCamera* _Camera)
		{
			camera = _Camera;
		}

		/**
		 * Sets a transform.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/06
		 *
		 * @param [in,out]	_Transform	If non-null, the transform.
		 */
		void SetTransform(Transform* _Transform)
		{
			transform = _Transform;
		}

	private:
		/** The primitive. */
		CPrimitive Primitive;
		/** The effect. */
		ID3DXEffect* Effect;
		/** The camera. */
		CCamera* camera;
		/** The transform. */
		Transform* transform;
		/** The texture. */
		CTexture Texture;
		/** True if this object is billboard. */
		bool isBillboard = false;
	};
}