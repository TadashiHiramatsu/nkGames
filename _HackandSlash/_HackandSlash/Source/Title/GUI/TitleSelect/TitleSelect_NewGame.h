/**
* �^�C�g���Z���N�g�̃j���[�Q�[���N���X�̒�`.
*/
#pragma once

#include"ITitleSelect.h"

/**
* �^�C�g���Z���N�g�̃j���[�Q�[���N���X.
*/
class TitleSelect_NewGame : public ITitleSelect
{
public:

	/**
	* �R���X�g���N�^.
	*/
	TitleSelect_NewGame() 
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	virtual ~TitleSelect_NewGame()
	{
	}

	/**
	* ������.
	*/
	void Start()override;

	/**
	* �X�V.
	*/
	void Update()override;

	/**
	* �|�X�g�G�t�F�N�g��̕`��.
	*/
	void PostRender()override;

	/**
	* �I�����ꂽ��.
	*/
	bool OnTrigger()override;
	
private:

};