/**
 * @file _Graphics\_ModelRender\nkAnimation.cpp
 *
 * アニメーションクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkAnimation.h"

namespace nkEngine
{

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] animcon If non-null, the animation.
	 */
	void Animation::Init(ID3DXAnimationController * animcon)
	{
		//アニメーションコントローラ受け取り
		D3DAnimController_ = animcon;


		//アニメーションセットの作成
		ID3DXAnimationSet* animSet;
		D3DAnimController_->GetAnimationSet(0, &animSet);

		//アニメーションの数を設定
		AnimNum_ = D3DAnimController_->GetMaxNumAnimationSets();
		AnimationSets_.reset(new ID3DXAnimationSet*[AnimNum_]);
		AnimationEndTime_.reset(new double[AnimNum_]);
		isAnimationLoops_.reset(new bool[AnimNum_]);

		//アニメーション事に設定
		for (int i = 0; i < AnimNum_; i++)
		{
			D3DAnimController_->GetAnimationSet(i, &AnimationSets_[i]);
			AnimationEndTime_[i] = -1.0;
			isAnimationLoops_[i] = true;
		}

		D3DAnimController_->AddRef();

		//アニメーショントラック設定
		NumMaxTracks_ = D3DAnimController_->GetMaxNumTracks();

		//ブレンドレートテーブルの設定
		BlendRateTable_.reset(new float[NumMaxTracks_]);
		for (int i = 0; i < NumMaxTracks_; i++)
		{
			BlendRateTable_[i] = 1.0f;
		}

		//ローカルアニメーションタイムの初期化
		LocalAnimationTime_ = 0.0;

	}

	/**
	 * Play animation.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param aniSetIndex Zero-based index of the animation set.
	 */
	void Animation::PlayAnimation(int aniSetIndex)
	{
		//アニメーションが存在していたら
		if (aniSetIndex < AnimNum_)
		{
			//アニメーションコントローラーがnullptr以外なら
			if (D3DAnimController_)
			{

				//アニメーション再生中に変更
				isAnimEnd_ = false;

				//アニメーション補間を設定
				isInterpolate_ = false;

				//アニメーションリクエストを削除
				PlayAnimRequest_.clear();

				//アニメーションナンバーを設定
				CurrentAnimationSetNo_ = aniSetIndex;

				CurrentTrackNo_ = 0;

				//0番目以外のトラックは無効にする
				for (int i = 1; i < NumMaxTracks_; i++)
				{
					D3DAnimController_->SetTrackEnable(i, FALSE);
				}

				D3DAnimController_->SetTrackWeight(0, 1.0f);
				D3DAnimController_->SetTrackAnimationSet(CurrentTrackNo_, AnimationSets_[CurrentAnimationSetNo_]);
				D3DAnimController_->SetTrackEnable(0, TRUE);
				D3DAnimController_->SetTrackPosition(0, 0.0f);

				//ローカルアニメーションタイムの初期化
				LocalAnimationTime_ = 0.0;

			}

		}

	}

	/**
	 * Play animation.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param aniSetIndex	   Zero-based index of the animation set.
	 * @param interpolateTime The interpolate time.
	 */
	void Animation::PlayAnimation(int aniSetIndex, float interpolateTime)
	{
		//アニメーションが存在していれば
		if (aniSetIndex < AnimNum_)
		{
			//アニメーションコントローラがnullptr以外なら
			if (D3DAnimController_) 
			{

				//アニメーション再生中に変更
				isAnimEnd_ = false;

				//補間開始に設定
				isInterpolate_ = true;
				//補間時間の初期化
				InterpolateTime_ = 0.0f;
				//補間終了時間の設定
				InterpolateEndTime_ = interpolateTime;

				//現在のトラックを取得
				int prevTrackNo = CurrentTrackNo_;

				//トラックの更新
				CurrentTrackNo_ = (CurrentTrackNo_ + 1) % NumMaxTracks_;

				D3DAnimController_->SetTrackAnimationSet(CurrentTrackNo_, AnimationSets_[aniSetIndex]);
				D3DAnimController_->SetTrackSpeed(prevTrackNo, 0.0f);
				D3DAnimController_->SetTrackEnable(CurrentTrackNo_, TRUE);
				D3DAnimController_->SetTrackSpeed(CurrentTrackNo_, 1.0f);
				D3DAnimController_->SetTrackPosition(CurrentTrackNo_, 0.0f);

				//ローカルアニメーションタイムの初期化
				LocalAnimationTime_ = 0.0;

				//現在のアニメーションナンバーを設定
				CurrentAnimationSetNo_ = aniSetIndex;

				//保管時間をもとにトラックの重みを更新
				UpdateTrackWeights();

			}

		}

	}

	/**
	* 保管時間をもとにトラックの重みを更新.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/10
	*/
	void Animation::UpdateTrackWeights()
	{

		//重み.
		float weight = 0.0f;

		//補間時間内なら
		if (InterpolateTime_ < InterpolateEndTime_)
		{
			//重みを計算
			weight = InterpolateTime_ / InterpolateEndTime_;

			//重みの逆を計算
			float invWeight = 1.0f - weight;

			//ウェイトを設定
			for (int i = 0; i < NumMaxTracks_; i++)
			{
				//現在のトラックでない
				if (i != CurrentTrackNo_)
				{
					D3DAnimController_->SetTrackWeight(i, BlendRateTable_[i] * invWeight);
				}
				else
				{
					D3DAnimController_->SetTrackWeight(i, weight);
				}
			}
		}
		else
		{
			for (int i = 0; i < NumMaxTracks_; i++)
			{
				if (i != CurrentTrackNo_)
				{
					D3DAnimController_->SetTrackWeight(i, 0.0f);
				}
				else
				{
					D3DAnimController_->SetTrackWeight(i, 1.0f);
				}
			}
		}

	}

	/**
	* アニメーション再生リクエストをポップ.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/10
	*/
	void Animation::PopRequestPlayAnimation()
	{
		if (!PlayAnimRequest_.empty())
		{
			if (AnimationSets_[CurrentAnimationSetNo_]->GetPeriod() - PlayAnimRequest_.front().InterpolateTime_ < LocalAnimationTime_)
			{
				//先頭のものを取得.
				RequestPlayAnimationS& req = PlayAnimRequest_.front();
				//設定.
				PlayAnimation(req.AnimationSetIndex_, req.InterpolateTime_);
				//排出.
				PlayAnimRequest_.pop_front();
			}
		}
	}

	/**
	 * Updates the given deltaTime.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param deltaTime The delta time.
	 */
	void Animation::Update(float deltaTime)
	{
		if (D3DAnimController_ && !isAnimEnd_)
		{
			//ローカルアニメーションタイムを計算
			LocalAnimationTime_ += deltaTime;

			if (isInterpolate_)
			{
				//補間中
				InterpolateTime_ += deltaTime;

				float weight = 0.0f;
				if (InterpolateTime_ > InterpolateEndTime_)
				{
					//補間終了
					isInterpolate_ = false;

					weight = 1.0f;

					//現在のトラック以外を無効にする
					for (int i = 0; i < NumMaxTracks_; i++)
					{
						if (i != CurrentTrackNo_)
						{
							D3DAnimController_->SetTrackEnable(i, FALSE);
						}
					}

				}
				else
				{
					//重みを計算
					UpdateTrackWeights();
				}
			}

			if (AnimationEndTime_[CurrentAnimationSetNo_] > 0.0 && //アニメーションの終了時間が設定されている. 
				LocalAnimationTime_ > AnimationEndTime_[CurrentAnimationSetNo_]) //アニメーションの終了時間を超えた.
			{
				//ループする
				if (isAnimationLoops_[CurrentAnimationSetNo_])
				{
					//ローカルアニメーションタイムを減算
					LocalAnimationTime_ -= AnimationEndTime_[CurrentAnimationSetNo_];

					D3DAnimController_->SetTrackPosition(CurrentTrackNo_, LocalAnimationTime_);
					D3DAnimController_->AdvanceTime(0, NULL);
				}
				else
				{
					//アニメーションの終了
					isAnimEnd_ = true;
				}
			}
			else
			{
				//普通に再生。
				if (AnimationSets_[CurrentAnimationSetNo_]->GetPeriod() < LocalAnimationTime_
					&& !isAnimationLoops_[CurrentAnimationSetNo_])
				{
					//アニメーション終了
					LocalAnimationTime_ = AnimationSets_[CurrentAnimationSetNo_]->GetPeriod();
					isAnimEnd_ = true;
				}
				else
				{
					D3DAnimController_->AdvanceTime(deltaTime, NULL);
				}

				//ローカルタイムをトラックから取得して同期
				D3DXTRACK_DESC trackDesk;
				D3DAnimController_->GetTrackDesc(CurrentTrackNo_, &trackDesk);

				//ローカルアニメーションタイムの計算
				LocalAnimationTime_ = fmod(trackDesk.Position, AnimationSets_[CurrentAnimationSetNo_]->GetPeriod());

			}

			//アニメーション終了
			//アニメーションの連続再生のリクエストをポップ
			PopRequestPlayAnimation();

		}

	}

}// namespace nkEngine