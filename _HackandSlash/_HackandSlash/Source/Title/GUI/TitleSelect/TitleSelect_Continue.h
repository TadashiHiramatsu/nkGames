/**
* タイトルセレクトのコンティニュークラスの定義.
*/
#pragma once

#include"ITitleSelect.h"

/**
* タイトルセレクトのコンティニュークラス.
*/
class TitleSelect_Continue : public ITitleSelect
{
public:

	/**
	* コンストラクタ.
	*/
	TitleSelect_Continue()
	{
	}

	/**
	* デストラクタ.
	*/
	virtual ~TitleSelect_Continue()
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