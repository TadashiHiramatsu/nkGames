#pragma once

#include"../modelRender/nkSkinModel.h"
#include"..\nkCamera.h"
#include"..\nkBlur.h"

namespace nkEngine
{

	class CCamera;

	class CShadowMap
	{
	public:
		//!<ライトビューの計算の仕方。
		enum EnCalcLightViewFunc {
			enCalcLightViewFunc_PositionDirection,	//ライトの位置と方向で計算する。
			enCalcLightViewFunc_PositionTarget,		//ライトの位置と注視点で計算する。
		};
			
		//作成
		//param[in] 横幅
		//param[in] 縦幅
		void Create(int w, int h);

		//更新
		void Update();

		//描画
		void Render();

		//開放
		void Release();

		//モデルをエントリー
		//param[in] モデル
		void Entry(CModelRender* SkinModel);

		//テクスチャを取得
		const CTexture* GetTexture() const
		{
			return m_blur.GetTexture();
		}

		//ライトの方向を設定
		void SetLightDirection(const D3DXVECTOR3& dir)
		{
			m_vLDirection = dir;
		}

		//ライトの視点を設定
		void SetLightPosition(const D3DXVECTOR3& pos)
		{
			m_vLPosition = pos;
		}

		//ライトの注視点を設定
		void SetLightTarget(const D3DXVECTOR3& ter)
		{
			m_vLTarget = ter;
		}

		//ライトビュープロジェクション行列の取得
		D3DXMATRIX* GetLVPMatrix()
		{
			return &m_mLViewProj;
		}

		//近平面を取得
		float GetNear() const
		{
			return m_near;
		}

		//近平面を設定
		void SetNear(float fnear)
		{
			m_near = fnear;
		}
		
		//遠平面を取得
		float GetFar() const
		{
			return m_far;
		}

		//遠平面を設定
		void SetFar(float ffar)
		{
			m_far = ffar;
		}
		
		//有効フラグの取得
		bool IsActive()const
		{
			return m_isActive;
		}

		//カメラを設定。PSMを行うときに使用される
		void SetCamera(CCamera* camera)
		{
			m_camera = camera;
		}

		//ライトビューの設定の仕方を設定
		void SetCalcLightViewFunc(EnCalcLightViewFunc func)
		{
			m_calcLightViewFunc = func;
		}

		//インスタンス取得
		inline static CShadowMap& instance()
		{
			static CShadowMap instance;
			return instance;
		}
	private:
		//コンストラクタ
		CShadowMap();
		//デストラクタ
		~CShadowMap();
	private:
		bool m_isActive; //有効フラグ	
		
		CRenderTarget m_shadowMapRT; //シャドウマップ用レンダーターゲット
		vector<CModelRender*> m_shadowModels; //影を書き込むモデル
	
		D3DXVECTOR3 m_vLPosition; //ライトの視点
		D3DXVECTOR3 m_vLDirection; //ライトの方向
		D3DXVECTOR3 m_vLTarget; //ライトの注視点

		D3DXMATRIX m_mLView; //ライトビュー行列
		D3DXMATRIX m_mLViewProj; //ライトビュープロジェクション行列
		D3DXMATRIX m_mProj; //プロジェクション行列

		EnCalcLightViewFunc	m_calcLightViewFunc; //ライトビューの計算方法。

		float m_near; //近平面
		float m_far; //遠平面
		float m_Aspect; //アスペクト比
		float m_shadowAreaW; //影を落とす範囲の幅
		float m_shadowAreaH; //影を落とす範囲の高さ

		CCamera* m_camera; //PSMを計算するときに使用するカメラ

		CBlur m_blur;
	};
	inline static CShadowMap& Shadow()
	{
		return CShadowMap::instance();
	}
}