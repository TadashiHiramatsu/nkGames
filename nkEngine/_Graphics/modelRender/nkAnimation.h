//スキンモデルのアニメーションを管理するクラス
#pragma once

#include <deque>

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
			if (animationIndex < AnimNum)
			{
				AnimationEndTime[animationIndex] = endTime;
			}
		}

		//アニメーションのループフラグを設定する
		//第１引数 アニメーションナンバー
		//第２引数 ループフラグ
		void SetAnimationLoopFlags(int animationIndex, bool _loopflag)
		{
			if (animationIndex < AnimNum)
			{
				AnimationLoopFlags[animationIndex] = _loopflag;
			}
		}

		//アニメーションの再生
		void PlayAnimation(int aniSetIndex);

		//アニメーションの再生
		//補間時間
		void PlayAnimation(int aniSetIndex, float interpolateTime);
		
		
		//アニメーションセットの取得
		int GetNumAnimationSet()const
		{
			return AnimNum;
		}

		//アニメーションの更新
		void Update(float deltaTime);

		//現在再生中のアニメーショントラックの番号を取得
		int GetNowAnimationNo()
		{
			return CurrentAnimationSetNo;
		}

		//アニメーションが再生中判定
		bool IsPlayAnim()
		{
			return !isAnimEnd;
		}

		//ローカルアニメーションタイムを取得
		float GetLocalAnimationTime()const
		{
			return(float)LocalAnimationTime;
		}
		
	private:
		//保管時間をもとにトラックの重みを更新
		void UpdateTrackWeights();

		//アニメーション再生リクエストをポップ
		void PopRequestPlayAnimation();

	private:
		//アニメーション再生リクエスト
		struct RequestPlayAnimation
		{
			int AnimationSetIndex;
			float InterpolateTime;
		};
		//アニメーションコントローラ
		ID3DXAnimationController* pAnimController;
		//アニメーションの数
		int AnimNum;
		//アニメーションセットの配列
		unique_ptr<ID3DXAnimationSet*[]> AnimationSets;
		//ブレンディングレートのテーブル。
		unique_ptr<float[]> BlendRateTable;
		//アニメーションのエンドタイム
		unique_ptr<double[]> AnimationEndTime;
		//アニメーションループフラグ
		unique_ptr<bool[]> AnimationLoopFlags;
		//ローカルアニメーションタイム
		double LocalAnimationTime; 
		//現在再生中のアニメーショントラックの番号
		int CurrentAnimationSetNo; 
		//現在のトラックの番号
		int CurrentTrackNo;
		//アニメーショントラックの最大数
		int NumMaxTracks; 
		//アニメーションブレンディング
		bool isBlending;
		//アニメーションの終了フラグ
		bool isAnimEnd;
		//補間中か？｛補間中：true、未補間：false｝
		bool isInterpolate; 
		//補間終了時間
		float InterpolateEndTime; 
		//補間時間
		float InterpolateTime;
		//アニメーション再生のリクエスト
		deque<RequestPlayAnimation> PlayAnimRequest;
	};
}