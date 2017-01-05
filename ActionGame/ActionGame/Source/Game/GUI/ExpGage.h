/**
 * @file	Source\Game\GUI\ExpGage.h
 *
 * Declares the exponent gage class.
 */
#pragma once

#include"..\Player\Player.h"

/**
 * An exponent gage.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class ExpGage : public IGameObject
{
public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	ExpGage();

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~ExpGage();

	/**
	 * Starts this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Start()override;

	/**
	 * Updates this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Update()override;

	/**
	 * Renders this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Render()override;

	/**
	 * Sets a player.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @param [in,out]	_p	If non-null, the p.
	 */
	void SetPlayer(Player* _p)
	{
		player = _p;
	}
private:
	RectTransform ExpFrameTransform; ///�t���[���p
	Image ExpFrameImage; ///�t���[����Image
	RectTransform ExpTransform; ///�{�̗p
	Image ExpImage; ///�{�̗pImage

	Player* player;

	int* NextExp;
	int* NowExp;

	TestFont Level;

};