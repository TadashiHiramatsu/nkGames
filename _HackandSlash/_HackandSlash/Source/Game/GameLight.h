#pragma once

class GameLight
{
public:

	/** �R���X�g���N�^. */
	GameLight()
	{
	}

	/** �f�X�g���N�^. */
	~GameLight()
	{
	}

	/**
	* ������.
	*/
	void Start();

	/**
	* ���C�g���擾
	*/
	Light* GetLight()
	{
		return &Light_;
	}

private:

	/** ���C�g�N���X. */
	Light Light_;

};

extern GameLight* g_GameLight;