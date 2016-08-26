//スキンモデルのアニメーションを管理するクラス
#pragma once

namespace nkEngine
{
	//アニメーションクラス
	class CAnimation
	{
	public:
		//コンストラクタ
		CAnimation();
		//デストラクタ
		~CAnimation();
		//初期化
		//引数 アニメーションコントローラ
		void Init(ID3DXAnimationController* animcon);
		//アニメーションの終了タイムを設定する
		//第１引数 アニメーションナンバー
		//第２引数 エンドタイム
		void SetAnimationEndTime(int animationIndex, double endTime)
		{
			m_animationEndTime[animationIndex] = endTime;
		}
		//アニメーションの再生
		void PlayAnimation(int aniSetIndex);
		//アニメーションの再生
		//補間時間
		void PlayAnimation(int aniSetIndex, float interpolateTime);
		//アニメーションセットの取得
		int GetNumAnimationSet()const
		{
			return m_numAnimSet;
		}
		//アニメーションの更新
		void Update(float deltaTime);
	private:
		ID3DXAnimationController* m_pAnimationController; //アニメーションコントローラ
		int m_numAnimSet; //アニメーションの数
		unique_ptr<ID3DXAnimationSet*[]> m_animationSets; //アニメーションセットの配列
		unique_ptr<float[]> blendRateTable; //ブレンディングレートのテーブル。
		unique_ptr<double[]> m_animationEndTime; //アニメーションのエンドタイム
		double m_localAnimationTime; //ローカルアニメーションタイム
		int m_currentAnimationSetNo; //現在再生中のアニメーショントラックの番号
		int m_currentTrackNo; //現在のトラックの番号
		int m_numMaxTracks; //アニメーショントラックの最大数

		bool m_isInterpolate; //補間中か？｛補間中：true、未補間：false｝
		float m_interpolateEndTime; //補間終了時間
		float m_interpolateTime; //補間時間
	};
}