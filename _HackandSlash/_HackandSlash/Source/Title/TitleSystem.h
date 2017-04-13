/**
 * @file Source\Title\GUI\TitleSystem.h
 *
 * タイトルシステムクラスの定義.
 */
#pragma once

#include"HUD/TitleBack.h"
#include"HUD\TitleName.h"

#include"../Common/SceneEffect/Fade.h"

#include"GUI/TitleSelect\ITitleSelect.h"

/**
 * タイトルシステムクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
class TitleSystem : public IGameObject
{
public:

	/** 選択の状態. */
	enum class SelectStateE
	{
		StateBegin = 0,			//!< ステートの先頭.
		NewGame = StateBegin,	//!< 初めから.
		Continue,				//!< 続きから.
		Exit,					//!< 終了.
		StateEnd = Exit,		//!< ステートの終端.
		StateNum,				//!< ステート数
	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	TitleSystem()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	~TitleSystem()
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

private:

	/**
	* セレクトの初期化.
	*/
	void InitSelect();

	/**
	* カーソルの上下移動.
	*/
	bool CursorUpDownMove();

private:

	/** ゲーム名表示クラスのポインタ. */
	TitleName* TitleName_ = nullptr;

	/** フェードクラスのポインタ*/
	Fade* Fade_ = nullptr;

	/** タイトルBGM. */
	SoundSource* TitleBGM_ = nullptr;

	/** 現在選択中のもの. */
	int NowSelect_;
	/** セレクトリスト. */
	ITitleSelect* SelectList_[(int)SelectStateE::StateNum];

	Image CursorImage_;
	RectTransform CursorRT_;

	/** 決定が押されたフラグ. */
	bool isDecision_ = false;

};