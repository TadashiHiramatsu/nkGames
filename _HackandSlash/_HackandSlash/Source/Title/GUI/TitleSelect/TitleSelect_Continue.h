/**
* �^�C�g���Z���N�g�̃R���e�B�j���[�N���X�̒�`.
*/
#pragma once

#include"ITitleSelect.h"

/**
* �^�C�g���Z���N�g�̃R���e�B�j���[�N���X.
*/
class TitleSelect_Continue : public ITitleSelect
{
public:

	/**
	* �R���X�g���N�^.
	*/
	TitleSelect_Continue()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	virtual ~TitleSelect_Continue()
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