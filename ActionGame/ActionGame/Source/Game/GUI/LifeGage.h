/**
 * @file	Source\Game\GUI\LifeGage.h
 *
 * Declares the life gage class.
 */
#pragma once

#include"..\Player\Player.h"


/**
 * A life gage.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
class LifeGage : public IGameObject
{
public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	LifeGage();

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	~LifeGage();

	/**
	 * Starts this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void Start()override;

	/**
	 * Updates this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void Update()override;

	/**
	 * Renders this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void Render()override;

	/**
	 * Sets a player.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 *
	 * @param [in]	_p	If non-null, the p.
	 */
	void SetPlayer(Player* _p)
	{
		player = _p;
	}

private:

	RectTransform LifeFrameTransform; ///フレーム用
	Image LifeFrameImage; ///フレームのImage
	RectTransform LifeTransform; ///本体用
	Image LifeImage; ///LifeのImage

	Player* player; ///プレイヤーのポインタ
	
	int* MaxLife;
	int* NowLife;
};