/**
 * @file Source\Title\TitleSystem.h
 *
 * タイトルシステムクラスの定義.
 */
#pragma once

#include"HUD\TitleBack.h"
#include"GUI\TitleStart.h"
#include"GUI\TitleContinue.h"

/**
 * タイトルシステムクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
class TitleSystem : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	TitleSystem()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	~TitleSystem()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Update()override;

};