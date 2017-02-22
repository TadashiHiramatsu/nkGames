#pragma once

class GameLight
{
public:

	/** コンストラクタ. */
	GameLight()
	{
	}

	/** デストラクタ. */
	~GameLight()
	{
	}

	/**
	* 初期化.
	*/
	void Start();

	/**
	* ライトを取得
	*/
	Light* GetLight()
	{
		return &Light_;
	}

private:

	/** ライトクラス. */
	Light Light_;

};

extern GameLight* g_GameLight;