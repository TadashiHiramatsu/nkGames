/**
 * @file _Graphics\_ModelRender\nkModelRender.h
 *
 * モデルレンダークラスの定義.
 */
#pragma once 

#include"nkSkinModelData.h"
#include"nkAnimation.h"
#include"nkLight.h"
#include"../nkCamera.h"
#include"../nkTexture.h"

namespace nkEngine
{

	/**
	 * モデルレンダクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class ModelRender
	{
	public:

		/** フォグのパラメータ. */
		enum FogFuncE
		{
			FogFuncNone,	//!< フォグなし
			FogFuncDist,	//!< 距離フォグ
			FogFuncHeight,	//!< 高さフォグ
		};

	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		ModelRender();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~ModelRender();

		/**
		 * 読み取り.
		 * "Asset/Model/"フォルダ内にあるXファイルのモデルをロード
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param 		   filePath Xファイルのファイルパス、"Asset/Model/"を省いたファイルパス.
		 * @param [in,out] anim	    アニメーションクラス.
		 */
		void Load(LPCSTR filePath, Animation* anim);

		/**
		 * 読み取り.
		 * モデルデータをコピーしてロード
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] modeldata If non-null, the modeldata to load.
		 */
		void Load(SkinModelData* modeldata);

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Update();

		/**
		 * インスタンシング描画用の更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param data 頂点バッファにコピーするデータ.
		 */
		void UpdateInstancinfRenderData(const void* data)
		{
			ModelData_->UpdateInstancingRenderData(data);
		}

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Render();

		/**
		 * シャドウマップに描画. 
		 * シャドウマップに呼び出される.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void RenderToShadowMap();

		/**
		 * ライトを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] light ライトのアドレス.
		 */
		void SetLight(Light* light)
		{
			Light_ = light;
		}

		/**
		 * 法線マップを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] normalmap テクスチャ.
		 */
		void SetNormalMap(Texture* normalmap)
		{
			NormalMap_ = normalmap;
		}

		/**
		 * スペキュラマップを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] spec テクスチャ.
		 */
		void SetSpecMap(Texture* spec)
		{
			SpecMap_ = spec;
		}

		/**
		 * シャドウキャスターのフラグを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param flag シャドウキャスターのフラグ.
		 */
		void SetShadowCasterFlag(bool flag)
		{
			isShadowCaster_ = flag;
		}

		/**
		 * シャドウレシーバーのフラグを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param flag シャドウレシーバーのフラグ.
		 */
		void SetShadowReceiverFlag(bool flag)
		{
			isShadowReceiver_ = flag;
		}

		/**
		 * リムライトフラグを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param flag リムライトのフラグ.
		 */
		void SetRimLight(bool flag)
		{
			isRimLight_ = flag;
		}

		/**
		 * 輝度を埋め込むフラグを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param flag 輝度を埋め込むフラグ.
		 */
		void SetLuminance(bool flag)
		{
			isLuminance_ = flag;
		}

		/**
		 * カメラのアドレスを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] camera カメラ.
		 */
		void SetCamera(Camera* camera)
		{
			Camera_ = camera;
		}

		/**
		 * トランスフォームを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] trans トランスフォームのアドレス.
		 */
		void SetTransform(Transform* trans)
		{
			Transform_ = trans;
		}

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Release()
		{
			ModelData_->Release();
			Light_ = nullptr;
			Camera_ = nullptr;
			Transform_ = nullptr;
		}

		/**
		 * フォグパラメータを設定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param fogfunc The フォグの種類.
		 * @param idx0    The フォグがかかり始める距離.
		 * @param idx1    The フォグがかかりきる距離.
		 */
		void SetFogParam(FogFuncE fogfunc, float idx0, float idx1)
		{
			FogFunc_ = fogfunc;
			FogParam_[0] = idx0;
			FogParam_[1] = idx1;
		}

		/**
		 * メッシュを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The mesh.
		 */
		LPD3DXMESH GetMesh()
		{
			static D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)(ModelData_->GetFrameRoot()->pMeshContainer);
			return pMeshContainer->OrigMesh_;
		}

		/**
		 * 先頭のメッシュを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The organisation mesh first.
		 */
		LPD3DXMESH GetOrgMeshFirst() const
		{
			return ModelData_->GetOrgMeshFirst();
		}

		/**
		 * フレームの検索.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the frame.
		 */
		D3DXFRAME* GetFrame()
		{
			return ModelData_->GetFrameRoot();
		}
		/**
		 * フレームの検索.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param name The name.
		 *
		 * @return Null if it fails, else the frame.
		 */
		D3DXFRAME* GetFrame(const char* name)
		{
			return D3DXFrameFind(GetFrame(), name);
		}

		/**
		 * フレームのワールド行列の取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param name The name.
		 *
		 * @return Null if it fails, else the found bone world matrix.
		 */
		D3DXMATRIX* FindBoneWorldMatrix(const char* name)
		{
			D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)GetFrame(name);
			return &frame->CombinedTransformationMatrix_;
		}

	protected:

		/**
		 * Renders the frame.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param pFrame			  The frame.
		 * @param isRenderToShadowMap True if this object is render to shadow map.
		 */
		void RenderFrame(
			LPD3DXFRAME pFrame,
			bool isRenderToShadowMap);

		/**
		 * Renders the mesh container.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param pMeshContainerBase  The mesh container base.
		 * @param pFrameBase		  The frame base.
		 * @param isRenderToShadowMap True if this object is render to shadow map.
		 */
		void RenderMeshContainer(
			LPD3DXMESHCONTAINER pMeshContainerBase,
			LPD3DXFRAME pFrameBase,
			bool isRenderToShadowMap);

		/**
		 * RenderMeshContainerから呼ばれるインスタンシング描画の共通処理。.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] meshContainer If non-null, the mesh container.
		 * @param 		   materialID    Identifier for the material.
		 */
		void RenderMeshContainer_InstancingRenderCommon(D3DXMESHCONTAINER_DERIVED* meshContainer, int materialID);

	protected:

		/** スキンモデルのデータ. */
		SkinModelData* ModelData_;
		/** ライトクラス. */
		Light* Light_;
		/** エフェクト. */
		ID3DXEffect* Effect_;
		/** カメラのアドレス. */
		Camera* Camera_;
		/** トランスフォーム 委譲したクラスのトランスフォームのアドレス. */
		Transform* Transform_;

		/** マトリクスパレットの最大数. */
		static const int MAX_MATRIX_PALLET = 128;
		/** マトリクスパレット. */
		D3DXMATRIX BoneMatrixPallets_[MAX_MATRIX_PALLET];

		/** 影を落とすかどうか. */
		bool isShadowReceiver_;
		/** 影が出るかどうか. */
		bool isShadowCaster_;
		/** リムライトをするかどうか. */
		bool isRimLight_;
		/** 輝度を埋め込むか. */
		bool isLuminance_;

		/** 法線マップのTexture. */
		Texture* NormalMap_;
		/** 鏡面反射マップのTexture. */
		Texture* SpecMap_;

		/** フォグの種類. */
		FogFuncE FogFunc_;
		/** フォグのパラメータ. */
		float FogParam_[2];

	};

}// namespace nkEngine