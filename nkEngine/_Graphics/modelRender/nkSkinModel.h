//スキンモデル
#pragma once 

#include"nkSkinModelData.h"
#include"nkAnimation.h"
#include"nkLight.h"

namespace nkEngine
{
	class CSkinModelData;
	class CLight;
	class CTransform;
	class CCamera;

	enum EFogFunc
	{
		enFogFuncNone, //フォグなし
		enFogFuncDist, //距離フォグ
		enFogFuncHeight, //高さフォグ
	};

	//モデルレンダー
	class CModelRender
	{
	public:
		//コンストラクタ
		CModelRender();

		//デストラクタ
		~CModelRender();

		//初期化
		//param[in] Xファイルのファイルパス
		void Init(LPCSTR Filepass, CAnimation* anim);
		//初期化
		//param[in] スキンモデルデータ
		void Init(CSkinModelData* ModelData);

		//更新
		void Update();

		//インスタンシング描画用の更新
		//pram[in] 頂点バッファにコピーするデータ
		void UpdateInstancinfDrawData(const void* data)
		{
			m_Skinmodel->UpdateInstancingDrawData(data);
		}

		//描画
		void Draw();

		//シャドウマップに描画
		//シャドウマップに呼び出される
		void DrawToShadowMap();

		//ライトを設定
		//param[in] ライトのアドレス
		void SetLight(CLight* light)
		{
			m_Light = light;
		}

		//法線マップを設定
		//param[in] テクスチャ
		void SetNormalMap(CTexture* normalmap)
		{
			m_NormalMap = normalmap;
		}

		//スペキュラマップを設定
		//param[in] テクスチャ
		void SetSpecMap(CTexture* spec)
		{
			m_SpecMap = spec;
		}

		//シャドウキャスターのフラグを設定
		//param[in] シャドウキャスターのフラグ
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}

		//シャドウレシーバーのフラグを設定
		//param[in] シャドウレシーバーのフラグ
		void SetShadowReceiverFlag(bool flag)
		{
			m_isShadowReceiver = flag;
		}

		//リムライトフラグを設定
		//param[in]	リムライトのフラグ
		void SetRimLight(bool flag)
		{
			m_isRimLight = flag;
		}

		//輝度を埋め込むフラグを設定
		//param[in] 輝度を埋め込むフラグ
		void SetLuminance(bool flag)
		{
			m_isLuminance = flag;
		}

		//カメラのアドレスを設定
		//param[in] カメラ
		void SetCamera(CCamera* camera)
		{
			m_camera = camera;
		}

		//トランスフォームを設定
		//param[in] トランスフォームのアドレス
		void SetTransform(CTransform* trans)
		{
			m_Transform = trans;
		}

		//リリース関数
		void Release()
		{
			m_Skinmodel->Release();
			m_Light = nullptr;
			m_camera = nullptr;
			m_Transform = nullptr;
		}

		//フォグパラメータを設定
		//param[in] フォグの種類
		//param[in] フォグがかかり始める距離
		//param[in] フォグがかかりきる距離
		void SetFogParam(EFogFunc fogfunc, float idx0, float idx1)
		{
			m_fogFunc = fogfunc;
			m_fogParam[0] = idx0;
			m_fogParam[1] = idx1;
		}

	private:

		void DrawFrame(
			LPD3DXFRAME pFrame,
			bool isDrawToShadowMap);

		void DrawMeshContainer(
			LPD3DXMESHCONTAINER pMeshContainerBase,
			LPD3DXFRAME pFrameBase,
			bool isDrawToShadowMap);

		//DrawMeshContainerから呼ばれるインスタンシング描画の共通処理。
		void DrawMeshContainer_InstancingDrawCommon(D3DXMESHCONTAINER_DERIVED* meshContainer, int materialID);

	private:
		CSkinModelData* m_Skinmodel; //スキンモデルのデータ
		CLight* m_Light; //ライトクラス
		ID3DXEffect* m_Effect; //エフェクト

		CCamera* m_camera; //カメラのアドレス

		CTransform* m_Transform; // トランスフォーム 委譲したクラスのトランスフォームのアドレス
		D3DXMATRIX m_mWorld; //ワールド行列
		D3DXMATRIX m_mRotation; //ローテーション行列　

		static const int MAX_MATRIX_PALLET = 128; //マトリクスパレットの最大数
		D3DXMATRIX m_BoneMatrixPallet[MAX_MATRIX_PALLET]; //マトリクスパレット

		bool m_isShadowReceiver; //影を落とすかどうか
		bool m_isShadowCaster; //影が出るかどうか
		bool m_isRimLight; //リムライトをするかどうか
		bool m_isLuminance; //輝度を埋め込むか
		CTexture* m_NormalMap; //法線マップのTexture
		CTexture* m_SpecMap; //鏡面反射マップのTexture

		EFogFunc m_fogFunc;	//フォグの種類
		float m_fogParam[2]; //フォグのパラメータ
	};
}