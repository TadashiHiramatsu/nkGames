/**
* タイトルセレクトのニューゲームクラスの定義.
*/
#pragma once

#include"ITitleSelect.h"

/**
* タイトルセレクトのニューゲームクラス.
*/
class TitleSelect_NewGame : public ITitleSelect
{
public:

	/**
	* コンストラクタ.
	*/
	TitleSelect_NewGame() 
	{
	}

	/**
	* デストラクタ.
	*/
	virtual ~TitleSelect_NewGame()
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