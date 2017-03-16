/**
* ボス_01クラスの定義.
*/
#pragma once

#include"IBoss.h"

/**
* ボス_01クラス.
*/
class Boss_01 : public IBoss
{
private:

	/** アニメーションコード. */
	enum class AnimationCodeE
	{
		Invalid = -1,	//!< 無効.
		Waiting,		//!< 待機.
	};

public:

	/**
	* コンストラクタ.
	*/
	Boss_01()
	{
	}

	/**
	* デストラクタ.
	*/
	virtual ~Boss_01()
	{
	}

	/**
	* 初期化.
	*/
	void Start()override;

	/**
	* 更新.
	*/
	void Update()override;

	/**
	* 描画.
	*/
	void Render()override;

	/**
	* 解放.
	*/
	void Release()override;

private:

	/**
	* ダメージ関数.
	*/
	void Damage()override;

	/**
	* アニメーションを変更.
	*
	* @param animcode	再生するアニメーションコード.
	* @param time		補間時間.
	*/
	void PlayAnimation(AnimationCodeE animcode, float time)
	{
		//現在再生しているアニメーションでなければ.
		if (Animation_.GetNowAnimationNo() != (int)animcode)
		{
			//変更.
			Animation_.PlayAnimation((int)animcode, time);
		}
	}

	/**
	* アニメーション管理.
	*/
	void AnimationControl()override;

private:



};