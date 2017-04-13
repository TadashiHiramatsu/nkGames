/**
* タイトルセレクトのエグジットクラスの定義.
*/
#pragma once

#include"ITitleSelect.h"

/**
* タイトルセレクトのエグジットクラス.
*/
class TitleSelect_Exit : public ITitleSelect
{
public:

	/**
	* コンストラクタ.
	*/
	TitleSelect_Exit()
	{
	}

	/**
	* デストラクタ.
	*/
	virtual ~TitleSelect_Exit()
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
	* ポストエフェクト後の描画.
	*/
	void PostRender()override;

	/**
	* 選択された時.
	*/
	bool OnTrigger()override;

private:

};