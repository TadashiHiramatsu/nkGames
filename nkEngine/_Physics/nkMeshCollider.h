/**
 * @file	_Physics\nkMeshCollider.h
 *
 * メッシュコライダークラスの定義.
 */
#pragma once

#include"nkCollider.h"
#include"../_Graphics/_ModelRender/nkModelRender.h"

namespace nkEngine
{

	/**
	 * メッシュコライダークラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class MeshCollider : public ICollider
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		MeshCollider();

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~MeshCollider();

		/**
		 * ModelRenderからMeshコライダーを生成.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	model			スキンモデル.
		 * @param 		  	offsetMatrix	オフセット行列.
		 */
		void Create(ModelRender* model, const D3DXMATRIX* offsetMatrix);

		/**
		 * ボディを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		btCollisionShape* GetBody() override
		{
			return MeshShape_;
		}

	private:

		/** 頂点バッファ. */
		typedef std::vector<D3DXVECTOR3> VertexBufferT;
		/** インデックスバッファ. */
		typedef std::vector<unsigned int> IndexBufferT;
		/** 頂点バッファの配列. */
		std::vector<VertexBufferT*> VertexBufferArray_;
		/** インデックスバッファの配列. */
		std::vector<IndexBufferT*> IndexBufferArray_;
		/** メッシュ形状. */
		btBvhTriangleMeshShape* MeshShape_;
		/** トライアングルインデックスバッファ. */
		btTriangleIndexVertexArray* StridingMeshInterface_;

	};

}// namespace nkEngine