//ライトクラス
#pragma once

namespace nkEngine
{
	//ライトクラス
	class CLight
	{
	public:
		//コンストラクタ
		CLight();
		//デストラクタ
		~CLight();
		
		//ディフューズライトの向きを設定
		//param[in] ライトの番号
		//param[in] ライトの方向
		void SetDiffuseLightDirection(int no, const D3DXVECTOR3 lightDir)
		{
			NK_ASSERT(no < LIGHT_NUM, "ライトの数大杉ぃぃぃ");
			m_diffuseLightDirection[no] = lightDir;
		}

		
		//ディフューズライトの向きを取得。
		//param[in]	ライトの番号
		//return	ライトの向き
		const D3DXVECTOR3& GetDiffuseLightDirection(int no) const
		{
			return m_diffuseLightDirection[no];
		}

		//ディフューズライトの色を設定
		//param[in] ライトの番号
		//param[in] ライトの色
		void SetDiffuseLightColor(int no, const D3DXVECTOR4 lightDir)
		{
			NK_ASSERT(no < LIGHT_NUM, "ライトの色大杉ぃぃぃ");
			m_diffuseLightColor[no] = lightDir;
		}


		//ディフューズライトの色を取得。
		//param[in]	ライトの番号
		//return	ライトの色
		const D3DXVECTOR4& GetDiffuseLightColor(int no) const
		{
			return m_diffuseLightColor[no];
		}

		//アンビエントライトを設定
		//param[in] アンビエントの色
		void SetAmbientLight(const D3DXVECTOR3 amb)
		{
			m_ambientLight = amb;
		}

		//アンビエントライトを取得
		//return アンビエントライト
		const D3DXVECTOR3& GetAmbientLight()const
		{
			return m_ambientLight;
		}

	public:
		static const int LIGHT_NUM = 6;//ライトの数
	private:
		D3DXVECTOR3 m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
		D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
		D3DXVECTOR3	m_ambientLight;						//環境光
	};

}