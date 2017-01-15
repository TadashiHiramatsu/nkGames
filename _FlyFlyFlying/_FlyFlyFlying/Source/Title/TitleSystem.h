/**
 * @file Source\Title\TitleSystem.h
 *
 * �^�C�g���V�X�e���N���X�̒�`.
 */
#pragma once

#include"HUD\TitleBack.h"
#include"GUI\TitleStart.h"
#include"GUI\TitleContinue.h"

/**
 * �^�C�g���V�X�e���N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
class TitleSystem : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	TitleSystem()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	~TitleSystem()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Update()override;

};