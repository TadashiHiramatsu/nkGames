//スキンモデルデータ
#pragma once

#include"..\nkVertexBuffer.h"

namespace nkEngine
{
	struct D3DXFRAME_DERIVED : public D3DXFRAME {
		D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
	};
	struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9* ppTextures;
		LPD3DXMESH pOrigMesh;
		LPD3DXATTRIBUTERANGE pAttributeTable;
		DWORD NumAttributeGroups;
		DWORD NumInfl;
		LPD3DXBUFFER pBoneCombinationBuf;
		D3DXMATRIX** ppBoneMatrixPtrs;
		D3DXMATRIX* pBoneOffsetMatrices;
		DWORD NumPaletteEntries;
		bool UseSoftwareVP;
		DWORD iAttributeSW;
	};

	//アニメーションクラス
	class CAnimation;

	//スキンモデルデータ
	class CSkinModelData
	{
	public:
		//コンストラクタ
		CSkinModelData();

		//デストラクタ
		~CSkinModelData();

		//モデルデータをロード
		//param[in] ファイルパス
		//param[out] アニメーション付きモデルデータの場合、アニメーションクラスも構築されます。
		void LoadModelData(const char* filepath, CAnimation* anim);

		//インスタンシング描画を行うためのデータを作成する
		//param[in] インスタンスの数
		//param[in] インスタンシング描画用の頂点ストリーム１に流し込む頂点バッファの頂点レイアウト
		void CreateInstancingDrawData(int numInstance, D3DVERTEXELEMENT9* vertexElement);

		//モデルデータのクローンを作成
		//param[in] モデルデータ
		//param[in] アニメーション付きモデルデータの場合、アニメーションクラスも構築されます。
		void CloneModelData(const CSkinModelData& ModelData, CAnimation* anim);

		//リリース
		void Release();

		//スケルトン削除
		void DeleteSkeleton(LPD3DXFRAME frame);

		//フレームレートの取得
		//return フレームレート
		D3DXFRAME* GetFrameRoot()
		{
			return m_FrameRoot;
		}

		//テスト 意味不
		//param[in] フレーム
		//param[in] アニメーションコントローラ
		void SetupOutputAnimationRegist(D3DXFRAME* frame, ID3DXAnimationController* aniCon);

		//ボーン行列を更新
		//param[in] ワールド行列
		void UpdateBoneMatrix(const D3DXMATRIX& matWorld);

		void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, const D3DXMATRIX* pParentMatrix);

		//インスタンシング描画用のデータを更新
		//param[in] 頂点バッファにコピーするデータ
		void UpdateInstancingDrawData(const void* data)
		{
			m_instanceVertexBuffer.Update(data);
		}

		//インスタンシング描画用のときに使用する頂点定義を取得
		//return 頂点定義
		IDirect3DVertexDeclaration9* GetVertexDeclForInstancingDraw()const
		{
			return m_vertexDeclForInstancingDraw;
		}

		//インスタンシング描画用の頂点バッファを取得
		//return ストリーム１に流す頂点バッファ
		const CVertexBuffer& GetInstancingVertexBuffer() const
		{
			return(const_cast<CSkinModelData&>(*this)).GetInstancingVertexBuffer();
		}
		//インスタンシング描画用の頂点バッファを取得
		//return 頂点バッファ
		CVertexBuffer& GetInstancingVertexBuffer()
		{
			return m_instanceVertexBuffer;
		}

		//インスタンスの数を取得
		//return インスタンス数
		int GetNumInstance()
		{
			return m_numInstance;
		}

		//頂点バッファのストライドを取得
		int GetVertexBufferStride() const
		{
			return m_vertexBufferStride;
		}

		//メッシュコンテナの削除
		//HRESULT DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase);

	private:

		//スケルトンのクローンを作成
		//param[out] クローン先のスケルトンの格納先
		//param[in] クローン元のスケルトン
		void CloneSkeleton(LPD3DXFRAME& dstFrame, D3DXFRAME* srcFrame);

		//スケルトンのクローンを削除
		//param[in]　削除するスケルトン
		void DeleteCloneSkeleton(D3DXFRAME* frame);

		//インスタンシング描画用のデータを作成
		//param[in] フレーム
		//param[in] インスタンスの数
		//param[in] インスタンシング描画用の頂点ストリーム1に流し込む頂点バッファの頂点レイアウト
		//return trueが帰ってきたら再帰処理終了
		bool CreateInstancingDrawData(D3DXFRAME* frame, int numInstance, D3DVERTEXELEMENT9* vertexElement);

		//謎
		HRESULT SetupBoneMatrixPointers(D3DXFRAME* pFrame, D3DXFRAME* pRootFrame);
	private:
		D3DXFRAME* m_FrameRoot; //フレームルート
		ID3DXAnimationController* m_AnimController; //アニメーションコントローラー
		bool m_isClone; //クローン
		CVertexBuffer m_instanceVertexBuffer; //インスタンシング描画用の頂点バッファのリスト
		IDirect3DVertexDeclaration9* m_vertexDeclForInstancingDraw; //インスタンシング描画用の頂点定義
		int m_numInstance; //インスタンスの数
		int m_vertexBufferStride; //頂点ストライド
	};
}