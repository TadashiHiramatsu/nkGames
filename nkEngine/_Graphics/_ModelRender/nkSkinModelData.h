/**
 * @file _Graphics\_ModelRender\nkSkinModelData.h
 *
 * スキンモデルデータクラスの定義.
 */
#pragma once

#include"..\_Buffer\nkVertexBuffer.h"
#include"../nkTexture.h"

namespace nkEngine
{

	/**
	 * A 3D xframe derived.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct D3DXFRAME_DERIVED : public D3DXFRAME 
	{
	public:

		/** 合成済み行列. */
		D3DXMATRIXA16 CombinedTransformationMatrix_;

	};

	/**
	 * A 3D xmeshcontainer derived.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
	{
	public:

		/** D3Dテクスチャ. */
		LPDIRECT3DTEXTURE9* D3DTexture_;
		/** テクスチャ. */
		Texture* Texture_;
		/** オリジナルメッシュ. */
		LPD3DXMESH OrigMesh_;
		/** 属性テーブル. */
		LPD3DXATTRIBUTERANGE AttributeTable_;
		/** 属性テーブルグループ. */
		DWORD NumAttributeGroup_;
		/** インフレーション？. */
		DWORD NumInfl_;
		/** 前回のボーンコンビネーション. */
		LPD3DXBUFFER BoneCombinationBuf_;
		/** ボーン行列ポインタ. */
		D3DXMATRIX** BoneMatrixPtrs_;
		/** ボーンオフセット行列. */
		D3DXMATRIX* BoneOffsetMatrix_;
		/** Number of palette entries. */
		DWORD NumPaletteEntries;
		/** True to use software vp. */
		bool UseSoftwareVP;
		/** Zero-based index of the attribute software. */
		DWORD iAttributeSW;

	};

	class Animation;

	/**
	 * スキンモデルデータ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class SkinModelData : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		SkinModelData();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~SkinModelData();

		/**
		 * モデルデータをロード.
		 * アニメーション付きモデルの場合アニメーションクラスも構築.
		 * アニメーションなしの場合nullでOK.
		 * "Asset/Model/" ファイル内のXファイルモデルをロード
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param 		   filepath ファイルパス、"Asset/Model/"を省いたファイルパス.
		 * @param [in,out] anim	    アニメーションクラスポインタ、null.
		 */
		void LoadModelData(const char* filepath, Animation* anim);

		/**
		 * インスタンシング描画を行うためのデータを作成する.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param 		   numInstance   インスタンスの数.
		 * @param [in,out] vertexElement インスタンシング描画用の頂点ストリーム１に流し込む頂点バッファの頂点レイアウト.
		 */
		void CreateInstancingRenderData(int numInstance, D3DVERTEXELEMENT9* vertexElement);

		/**
		 * モデルデータのクローンを作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param 		   modelData モデルデータ.
		 * @param [in,out] anim		 アニメーション付きモデルデータの場合、アニメーションクラスも構築されます.
		 */
		void CloneModelData(const SkinModelData& modelData, Animation* anim);

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Release();

		/**
		 * スケルトン削除.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param frame The frame.
		 */
		void DeleteSkeleton(LPD3DXFRAME frame);

		/**
		 * フレームレートの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the frame root.
		 */
		D3DXFRAME* GetFrameRoot()
		{
			return FrameRoot_;
		}

		/**
		 * オリジナルメッシュを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param frame The frame.
		 *
		 * @return The organisation mesh.
		 */
		LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame) const;

		/**
		 * 先頭のメッシュを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The organisation mesh first.
		 */
		LPD3DXMESH GetOrgMeshFirst() const;

		/**
		 * テスト 意味不.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] frame  フレーム.
		 * @param [in,out] aniCon アニメーションコントローラ.
		 */
		void SetupOutputAnimationRegist(D3DXFRAME* frame, ID3DXAnimationController* aniCon);

		/**
		 * ボーン行列を更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param matWorld ワールド行列.
		 */
		void UpdateBoneMatrix(const Matrix& matWorld);

		/**
		 * 各フレームの行列を更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param frameBase    The frame base.
		 * @param parentMatrix The parent matrix.
		 */
		void UpdateFrameMatrices(LPD3DXFRAME frameBase, const D3DXMATRIX* parentMatrix);

		/**
		 * インスタンシング描画用のデータを更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param data 頂点バッファにコピーするデータ.
		 */
		void UpdateInstancingRenderData(const void* data)
		{
			InstanceVertexBuffer_.Update(data);
		}

		/**
		 * インスタンシング描画用のときに使用する頂点定義を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the vertex declaration for instancing render.
		 */
		IDirect3DVertexDeclaration9* GetVertexDeclForInstancingRender() const
		{
			return VertexDeclForInstancingRender_;
		}

		/**
		 * インスタンシング描画用の頂点バッファを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return ストリーム１に流す頂点バッファ.
		 */
		const VertexBuffer& GetInstancingVertexBuffer() const
		{
			return(const_cast<SkinModelData&>(*this)).GetInstancingVertexBuffer();
		}

		/**
		 * インスタンシング描画用の頂点バッファを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return 頂点バッファ.
		 */
		VertexBuffer& GetInstancingVertexBuffer()
		{
			return InstanceVertexBuffer_;
		}

		/**
		 * インスタンスの数を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The number instance.
		 */
		int GetNumInstance() const
		{
			return numInstance_;
		}

		/**
		 * 頂点バッファのストライドを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The vertex buffer stride.
		 */
		int GetVertexBufferStride() const
		{
			return VertexBufferStride_;
		}

		/**
		* 先頭のボーン行列を取得.
		*
		* @return 先頭のボーン行列.
		*/
		Matrix* GetRootBoneWorldMatrix()
		{
			D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)FrameRoot_;
			return (Matrix*)&frameDer->CombinedTransformationMatrix_;
		}

	private:

		/**
		 * スケルトンのクローンを作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] dstFrame クローン先のスケルトンの格納先.
		 * @param [in,out] srcFrame クローン元のスケルトン.
		 */
		void CloneSkeleton(LPD3DXFRAME& dstFrame, D3DXFRAME* srcFrame);

		/**
		 * スケルトンのクローンを削除.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] frame 削除するスケルトン.
		 */
		void DeleteCloneSkeleton(D3DXFRAME* frame);

		/**
		 * インスタンシング描画用のデータを作成.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] frame		 フレーム.
		 * @param 		   numInstance   インスタンスの数.
		 * @param [in,out] vertexElement インスタンシング描画用の頂点ストリーム1に流し込む頂点バッファの頂点レイアウト.
		 *
		 * @return trueが帰ってきたら再帰処理終了.
		 */
		bool CreateInstancingRenderData(D3DXFRAME* frame, int numInstance, D3DVERTEXELEMENT9* vertexElement);

		/**
		 * 謎.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] frame	  If non-null, the frame.
		 * @param [in,out] rootFrame If non-null, the root frame.
		 *
		 * @return A hResult.
		 */
		HRESULT SetupBoneMatrixPointers(D3DXFRAME* frame, D3DXFRAME* rootFrame);

	private:

		/** フレームルート. */
		D3DXFRAME* FrameRoot_;
		/** アニメーションコントローラ. */
		ID3DXAnimationController* D3DAnimController_;
		/** クローンフラグ. */
		bool isClone_;
		/** インスタンシング描画用の頂点バッファのリスト. */
		VertexBuffer InstanceVertexBuffer_;
		/** インスタンシング描画用の頂点定義. */
		IDirect3DVertexDeclaration9* VertexDeclForInstancingRender_;
		/** インスタンスの数. */
		int numInstance_;
		/** 頂点ストライド. */
		int VertexBufferStride_;

	};
}