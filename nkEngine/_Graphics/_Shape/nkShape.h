/**
 * @file _Graphics\_Shape\nkShape.h
 *
 * 形状の基底クラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * 形状の基底クラス.
	 * すべての形状はこのクラスを継承する.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/18
	 */
	class IShape
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		IShape();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		virtual ~IShape();

		/**
		 * ワールド行列の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @return The world matrix.
		 */
		const D3DXMATRIX& GetWorldMatrix()const
		{
			return WorldMatrix_;
		}

		/**
		 * 回転行列の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @return The rotation matrix.
		 */
		const D3DMATRIX& GetRotationMatrix()const
		{
			return RotationMatrix_;
		}

		/**
		 * 座標を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param pos The position.
		 */
		void SetPosition(const D3DXVECTOR3& pos)
		{
			Position_ = pos;
		}

		/**
		 * 回転を設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param rot The rot.
		 */
		void SetRotation(const D3DXQUATERNION& rot)
		{
			Rotation_ = rot;
		}

		/**
		 * プリミティブを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @return Null if it fails, else the primitive.
		 */
		Primitive* GetPrimitive()
		{
			return Primitive_;
		}

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 */
		void Update();

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 */
		void Render();

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 */
		void Release();

	protected:

		/** 内部でプリミティブを作成したかフラグ. */
		bool isCreatePrimitive_ = false;
		/** プリミティブのポインタ. */
		Primitive* Primitive_ = nullptr;

		/** 座標. */
		D3DXVECTOR3 Position_ = D3DXVECTOR3(0, 0, 0);
		/** 回転. */
		D3DXQUATERNION Rotation_ = D3DXQUATERNION(0, 0, 0, 1);

		/** ワールド行列. */
		D3DXMATRIX WorldMatrix_;
		/** 回転行列. */
		D3DXMATRIX RotationMatrix_;

		/** エフェクト. */
		Effect* Effect_ = nullptr;
		
		/** ライトクラス. */
		static Light DefaultLight_;
		/** ライトクラス初期化フラグ. */
		static bool isInitDefaultLight_;
	
	};

	/**
	 * ポリゴン情報構造体.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	struct PolygonInfoS
	{
	public:

		/** 面法線. */
		D3DXVECTOR3 Normal_;
		/** 面を構成する頂点. */
		int VertexNo_[3];

	};

	/**
	 * 頂点バッファの法線を作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 *
	 * @tparam TVertex 頂点バッファ.
	 * @tparam TIndex  インデックスバッファ.
	 * @param [in,out] vertexBuffer 頂点バッファバッファのvector.
	 * @param [in,out] indexBuffer  インデックスバッファのvector.
	 * @param 		   primType	    プリミティブタイプ.
	 */
	template<class TVertex,class TIndex>
	void CreateVertexNormal(vector<TVertex>& vertexBuffer, vector<TIndex>& indexBuffer, Primitive::TypeE primitiveType)
	{
		//面法線を求める
		
		int numFace = (int)indexBuffer.size() / 3;

		//ポリゴン情報
		unique_ptr<PolygonInfoS[]> polygonInfoPtr;
		//ポリゴン情報配列
		vector<list<PolygonInfoS>> polygonInfoList;
	
		polygonInfoList.resize(vertexBuffer.size());

		for (int i = 0; i < numFace; i++)
		{
			//座標
			D3DXVECTOR3 pos[3];
			int t = i * 3;

			//ポリゴン情報
			PolygonInfoS polygonInfo;

			//頂点番号をコピー
			polygonInfo.VertexNo_[0] = indexBuffer.at(t);
			polygonInfo.VertexNo_[1] = indexBuffer.at(t+1);
			polygonInfo.VertexNo_[2] = indexBuffer.at(t+2);

			if (polygonInfo.VertexNo_[0] == polygonInfo.VertexNo_[1] ||
				polygonInfo.VertexNo_[0] == polygonInfo.VertexNo_[2] ||
				polygonInfo.VertexNo_[1] == polygonInfo.VertexNo_[2]) 
			{
				//縮退ポリゴン
				//頂点が一致していて描画しないポリゴン？がある状態？
				continue;
			}

			//法線
			D3DXVECTOR3 normal = D3DXVECTOR3(0, 0, 0);
			//頂点座標
			D3DXVECTOR3 vertexPos[3];
			
			for (int i = 0; i < 3; i++)
			{
				//頂点バッファをコピー
				const TVertex& vertex = vertexBuffer.at(polygonInfo.VertexNo_[i]);
				//頂点座標をコピー
				vertexPos[i] = D3DXVECTOR3(vertex.pos[0], vertex.pos[1], vertex.pos[2])
			}

			D3DXVECTOR3 t0, t1;
			t0 = vertexPos[1] - vertexPos[0];
			t1 = vertexPos[2] - vertexPos[0];
			//正規化
			D3DXVec3Normalize(&t0, &t0);
			D3DXVec3Normalize(&t1, &t1);

			//法線を計算
			D3DXVec3Cross(&polygonInfo.Normal_, &t0, &t1);
			
			//リストに登録
			polygonInfoList.at(polygonInfo.VertexNo_[0]).push_back(polygonInfo);
			polygonInfoList.at(polygonInfo.VertexNo_[1]).push_back(polygonInfo);
			polygonInfoList.at(polygonInfo.VertexNo_[2]).push_back(polygonInfo);
		
		}

		//頂点法線を求める
		for (int vertexNo = 0; vertexNo < (int)vertexBuffer.size(); vertexNo++)
		{
			//リストを取得
			list<PolygonInfoS>& polygonInfo = polygonInfoList.at(vertexNo);

			//法線
			D3DXVECTOR3 normal = D3DXVECTOR3(0, 0, 0);

			//合計
			for (const auto& it : polygonInfo)
			{
				normal += it.Normal_;
			}
			
			//平均値を計算
			normal /= s_cast<float>(polygonInfo.size());
		
			float* pNormal = vertexBuffer.at(vertexNo).Normal_;
			pNormal[0] = normal.x;
			pNormal[1] = normal.y;
			pNormal[2] = normal.z;
			pNormal[3] = 1.0f;
		}
	}

	/**
	 * 頂点バッファの法線を作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 *
	 * @tparam TVertex 頂点バッファ.
	 * @tparam TIndex  インデックスバッファ.
	 * @param [in,out] vertexBuffer  頂点バッファの先頭アドレス.
	 * @param 		   numVertex	 頂点数.
	 * @param [in,out] indexBuffer   インデックスバッファの先頭アドレス.
	 * @param 		   numIndex		 インデックス数.
	 * @param 		   primiteveType プリミティブタイプ.
	 */
	template<class TVertex, class TIndex>
	void CreateVertexNormalArray(
		TVertex* vertexBuffer, int numVertex,
		TIndex* indexBuffer, int numIndex,
		Primitive::TypeE primiteveType)
	{
		//面法線を求める

		int numFace = numIndex / 3;

		//ポリゴン情報
		unique_ptr<PolygonInfoS[]> polygonInfoPtr;
		//ポリゴン情報配列
		vector<list<PolygonInfoS>> polygonInfoList;

		polygonInfoList.resize(numVertex);

		for (int i = 0; i < numFace; i++)
		{
			//座標
			D3DXVECTOR3 pos[3];
			int t = i * 3;

			//ポリゴン情報
			PolygonInfoS polygonInfo;

			//頂点番号をコピー
			polygonInfo.VertexNo_[0] = indexBuffer[t];
			polygonInfo.VertexNo_[1] = indexBuffer[t + 1];
			polygonInfo.VertexNo_[2] = indexBuffer[t + 2];

			if (polygonInfo.VertexNo_[0] == polygonInfo.VertexNo_[1] ||
				polygonInfo.VertexNo_[0] == polygonInfo.VertexNo_[2] ||
				polygonInfo.VertexNo_[1] == polygonInfo.VertexNo_[2])
			{
				//縮退ポリゴン
				//頂点が一致していて描画しないポリゴン？がある状態？
				continue;
			}

			//法線
			D3DXVECTOR3 normal = D3DXVECTOR3(0, 0, 0);
			//頂点座標
			D3DXVECTOR3 vertexPos[3];

			for (int i = 0; i < 3; i++)
			{
				//頂点バッファをコピー
				const TVertex& vertex = vertexBuffer[polygonInfo.VertexNo_[i]];
				//頂点座標をコピー
				vertexPos[i] = D3DXVECTOR3(vertex.pos[0], vertex.pos[1], vertex.pos[2])
			}

			D3DXVECTOR3 t0, t1;
			t0 = vertexPos[1] - vertexPos[0];
			t1 = vertexPos[2] - vertexPos[0];
			//正規化
			D3DXVec3Normalize(&t0, &t0);
			D3DXVec3Normalize(&t1, &t1);

			//法線を計算
			D3DXVec3Cross(&polygonInfo.Normal_, &t0, &t1);

			//リストに登録
			polygonInfoList.at(polygonInfo.VertexNo_[0]).push_back(polygonInfo);
			polygonInfoList.at(polygonInfo.VertexNo_[1]).push_back(polygonInfo);
			polygonInfoList.at(polygonInfo.VertexNo_[2]).push_back(polygonInfo);

		}

		//頂点法線を求める
		for (int vertexNo = 0; vertexNo < numVertex; vertexNo++)
		{
			//リストを取得
			list<PolygonInfoS>& polygonInfo = polygonInfoList.at(vertexNo);

			//法線
			D3DXVECTOR3 normal = D3DXVECTOR3(0, 0, 0);

			//合計
			for (const auto& it : polygonInfo)
			{
				normal += it.Normal_;
			}

			//平均値を計算
			normal /= s_cast<float>(polygonInfo.size());

			float* pNormal = vertexBuffer[vertexNo].Normal_;
			pNormal[0] = normal.x;
			pNormal[1] = normal.y;
			pNormal[2] = normal.z;
			pNormal[3] = 1.0f;
		}
	}

	/**
	 * 頂点マージ.
	 * 頂点を結合する
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 *
	 * @tparam TVertex 頂点バッファ.
	 * @tparam TIndex  インデックスバッファ.
	 * @param [in,out] vertexBuffer		 マージ対象の頂点バッファ.
	 * @param [in,out] indexBuffer		 マージ対象のインデックスバッファ.
	 * @param 		   margeLenThreshold マージする頂点同士の距離の閾値。この値以下の頂点はマージされます.
	 */
	template<class TVertex, class TIndex>
	void MergeVertex(vector<TVertex>& vertexBuffer, vector<TIndex>& indexBuffer, float margeLenThreshold)
	{
		float margeLenThresholdSq = margeLenThreshold * margeLenThreshold;

		//マージ情報。削除する頂点番号と、置き換える頂点番号のペア情報。
		typedef pair<int, int>	MergeInfoT;
		//削除する頂点番号のリスト。
		list<MergeInfoT> mergeInfoList;

		//頂点削除のフラグのリスト。
		typename vector<bool> isDeleteVertexs;	
		//自身より小さい番号の頂点がいくつ削除されたかのカウントする
		typename vector<int>  deleteCount;			
		
		//初期化
		isDeleteVertexs.resize(vertexBuffer.size());
		deleteCount.resize(vertexBuffer.size());
		for (auto& it : isDeleteVertexs) 
		{
			it = false;
		}
		for (auto& it : deleteCount) 
		{
			it = 0;
		}

		for (int vertexNo = 0; vertexNo != vertexBuffer.size(); vertexNo++) 
		{
			if (isDeleteVertexs[vertexNo]) 
			{
				//削除予定の頂点なので調べる必要なし。
				continue;
			}

			//頂点取得
			const TVertex& v0 = vertexBuffer[vertexNo];

			//座標
			D3DXVECTOR3 pos;
			//距離
			D3DXVECTOR3 len;

			//座標を設定
			pos = D3DXVECTOR3(v0.pos[0], v0.pos[1], v0.pos[2]);

			for (int delvertexNo = 0; delvertexNo < (int)vertexBuffer.size(); delvertexNo++)
			{
				//重なってないかつ消してないみたいな？
				if (vertexNo != delvertexNo && !isDeleteVertexs[delvertexNo]) 
				{
					//頂点同士の距離を調べる
					const TVertex& v1 = vertexBuffer[delvertexNo];

					//距離を設定
					len = D3DXVECTOR3(v1.pos[0], v1.pos[1], v1.pos[2]);

					len = pos - len;

					//距離の二乗を取得
					float lenSq = D3DXVec3LengthSq(&len);

					if (lenSq < margeLenThresholdSq) 
					{
						//消す距離だった

						//削除する印をつける。
						isDeleteVertexs[delvertexNo] = true;	
									
						//マージ情報を作成する。
						MergeInfoT mergeInfo;
						mergeInfo.first = delvertexNo;
						mergeInfo.second = vertexNo;
						//追加
						mergeInfoList.push_back(mergeInfo);
					}
				}
			}
		}

		for (auto& mergeInfoIt : mergeInfoList)
		{
			for (TIndex index = mergeInfoIt.first + 1; index < (int)deleteCount.size(); index++) 
			{
				deleteCount[index]++;
			}
		}

		//頂点バッファを取得
		vector<TVertex> vertexBufferTmp = vertexBuffer;
		//消す
		vertexBuffer.clear();

		for (int i = 0; i < (int)vertexBufferTmp.size(); i++) 
		{
			if (!isDeleteVertexs[i]) 
			{
				//消さない頂点を設定
				vertexBuffer.push_back(vertexBufferTmp[i]);
			}
		}

		//頂点を削除したのでインデックスバッファを調整。
		{
			for (auto& mergeInfoIt : mergeInfoList) {
				//インデックスバッファから削除対象の頂点を探しつつ、削除対象の頂点より番号が大きいものは減算する.
				for (auto& indexIt : indexBuffer) 
				{
					if (mergeInfoIt.first == indexIt) 
					{
						//削除対象.
						indexIt = mergeInfoIt.second;
					}
				}
			}
		}

		for (auto& indexIt : indexBuffer) 
		{
			indexIt -= deleteCount[indexIt];
		}
	}

}