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
		MeshCollider()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~MeshCollider()
		{
		}

		/**
		 * ModelRenderからMeshコライダーを生成.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	model			スキンモデル.
		 * @param 		  	offsetMatrix	オフセット行列.
		 */
		void Create(ModelRender* model, const Matrix* offsetMatrix);

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

		/**
		* 解放.
		*/
		void Release()override
		{
			//頂点バッファ配列の削除
			for (auto& vb : VertexBufferArray_)
			{
				delete vb;
			}

			//インデックスバッファの削除
			for (auto& ib : IndexBufferArray_)
			{
				delete ib;
			}
			delete StridingMeshInterface_;
		}

	private:

		/** 頂点バッファ. */
		typedef std::vector<Vector3> VertexBufferT;
		/** インデックスバッファ. */
		typedef std::vector<unsigned int> IndexBufferT;
		/** 頂点バッファの配列. */
		std::vector<VertexBufferT*> VertexBufferArray_;
		/** インデックスバッファの配列. */
		std::vector<IndexBufferT*> IndexBufferArray_;
		/** メッシュ形状. */
		btBvhTriangleMeshShape* MeshShape_ = nullptr;
		/** トライアングルインデックスバッファ. */
		btTriangleIndexVertexArray* StridingMeshInterface_ = nullptr;

	};

}// namespace nkEngine