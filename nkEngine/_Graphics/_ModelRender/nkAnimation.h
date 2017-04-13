/**
 * @file _Graphics\_ModelRender\nkAnimation.h
 *
 * スキンモデルのアニメーションを管理するクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * アニメーションクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class Animation : Noncopyable
	{
	private:

		/**
		* アニメーション再生リクエスト.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/10
		*/
		struct RequestPlayAnimationS
		{
			/** アニメーション番号. */
			int AnimationSetIndex_ = -1;
			/** 補間時間. */
			float InterpolateTime_ = 0;
		};

	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		Animation()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~Animation()
		{
		}

		/**
		 * 初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] animcon アニメーションコントローラ.
		 */
		void Init(ID3DXAnimationController* animcon);

		/**
		 * アニメーションの終了タイムを設定する.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param animationIndex アニメーションナンバー.
		 * @param endTime		 エンドタイム.
		 */
		void SetAnimationEndTime(int animationIndex, double endTime)
		{
			//アニメーションが存在していれば
			if (animationIndex < AnimNum_)
			{
				AnimationEndTime_[animationIndex] = endTime;
			}
		}

		/**
		 * アニメーションのループフラグを設定する.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param animationIndex アニメーションナンバー.
		 * @param _loopflag		 ループフラグ.
		 */
		void SetAnimationLoopFlag(int animationIndex, bool _loopflag)
		{
			//アニメーションが存在していれば
			if (animationIndex < AnimNum_)
			{
				isAnimationLoops_[animationIndex] = _loopflag;
			}
		}

		/**
		 * アニメーションの再生.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param aniSetIndex アニメーションナンバー.
		 */
		void PlayAnimation(int aniSetIndex);

		/**
		 * アニメーションの再生.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param aniSetIndex	  アニメーションナンバー.
		 * @param interpolateTime 補間時間.
		 */
		void PlayAnimation(int aniSetIndex, float interpolateTime);

		/**
		* アニメーション再生リクエストをキューに積む.
		*
		* @param animationSetIndex	アニメーションナンバー.
		* @param interpolateTime	補間時間.
		*/
		void PlayAnimationQueue(int animationSetIndex, float interpolateTime)
		{
			RequestPlayAnimationS req;
			req.AnimationSetIndex_ = animationSetIndex;
			req.InterpolateTime_ = interpolateTime;
			PlayAnimRequest_.push_back(req);
		}

		/**
		 * アニメーションセットの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The number animation set.
		 */
		int GetNumAnimationSet() const
		{
			return AnimNum_;
		}

		/**
		 * アニメーションの更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param deltaTime The delta time.
		 */
		void Update(float deltaTime);

		/**
		 * 現在再生中のアニメーショントラックの番号を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The now animation no.
		 */
		int GetNowAnimationNo() const
		{
			return CurrentAnimationSetNo_;
		}

		/**
		 * アニメーションが再生中判定.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return True if play animation, false if not.
		 */
		bool IsPlayAnim() const
		{
			return !isAnimEnd_;
		}

		/**
		 * ローカルアニメーションタイムを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The local animation time.
		 */
		float GetLocalAnimationTime() const
		{
			return (float)LocalAnimationTime_;
		}

		/**
		 * アニメーションコントローラの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the animation con.
		 */
		ID3DXAnimationController* GetAnimCon()
		{
			return D3DAnimController_;
		}
		
	private:

		/**
		 * 保管時間をもとにトラックの重みを更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void UpdateTrackWeights();

		/**
		 * アニメーション再生リクエストをポップ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PopRequestPlayAnimation();

	private:

		/** アニメーションコントローラ. */
		ID3DXAnimationController* D3DAnimController_ = nullptr;
		/** アニメーションの数. */
		int AnimNum_ = 0;
		/** アニメーションセットの配列. */
		unique_ptr<ID3DXAnimationSet*[]> AnimationSets_;
		/** ブレンディングレートのテーブル. */
		unique_ptr<float[]> BlendRateTable_;
		/** アニメーションのエンドタイム. */
		unique_ptr<double[]> AnimationEndTime_;
		/** アニメーションループフラグ. */
		unique_ptr<bool[]> isAnimationLoops_;
		/** ローカルアニメーションタイム. */
		double LocalAnimationTime_ = 0.0; 
		/** 現在再生中のアニメーショントラックの番号. */
		int CurrentAnimationSetNo_ = -1;
		/** 現在のトラックの番号. */
		int CurrentTrackNo_ = 0;
		/** アニメーショントラックの最大数. */
		int NumMaxTracks_ = 0; 
		/** アニメーションブレンディング. */
		bool isBlending_ = false;
		/** アニメーションの終了フラグ. */
		bool isAnimEnd_ = true;
		/** 補間中か？｛補間中：true、未補間：false｝. */
		bool isInterpolate_ = false;
		/** 補間終了時間. */
		float InterpolateEndTime_ = 0.0f; 
		/** 補間時間. */
		float InterpolateTime_ = 0.0f;
		/** アニメーション再生のリクエスト. */
		deque<RequestPlayAnimationS> PlayAnimRequest_;

	};
}