/**
* �^�C�g���Z���N�g�̃G�O�W�b�g�N���X�̒�`.
*/
#pragma once

#include"ITitleSelect.h"

/**
* �^�C�g���Z���N�g�̃G�O�W�b�g�N���X.
*/
class TitleSelect_Exit : public ITitleSelect
{
public:

	/**
	* �R���X�g���N�^.
	*/
	TitleSelect_Exit()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	virtual ~TitleSelect_Exit()
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