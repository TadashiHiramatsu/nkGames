/**
* ���j���[�E�B���h�E�̃I�v�V�����E�B���h�E�N���X�̒�`.
*/
#pragma once

#include"../IMenuWindow.h"

/**
* ���j���[�E�B���h�E�̃I�v�V�����E�B���h�E�N���X.
*/
class OptionWindow : public IMenuWindow
{
private:

	/** ��ԃR�[�h. */
	enum SelectStateE
	{
		SelectBegin = 0,	//!< ��Ԃ̐擪.
		Save = SelectBegin,	//!< �Z�[�u.
		Title,				//!< �^�C�g��.
		Exit,				//!< �G�O�W�b�g.
		SelectEnd = Exit,	//!< ��Ԃ̏I�[.
		SelectNum,			//!< ��.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	OptionWindow()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~OptionWindow()
	{
	}

	/**
	* ������.
	*/
	void Start(RectTransform* rt, float namepos)override;

	/**
	* �X�V.
	*/
	void Update()override;

	/**
	* �`��.
	*/
	void Render()override;

	/**
	* �E�B���h�E�����Ƃ��̓���.
	*/
	void Close()override
	{
	}

private:

	/** 
	* �I���ړ�. 
	*/
	bool SelectUpDownMove();

	/**
	* ����.
	*/
	void Decision();

private:

	/** �摜. */
	Image WindowImage_;
	/** �摜�p�g�����X�t�H�[��. */
	RectTransform WindowRT_;

	Image ControllerImage_;
	RectTransform ControllerRT_;

	/** �I�����Ă�����. */
	int SelectState_ = SelectStateE::Save;

	/** �Z���N�g�t���[���摜. */
	Image SelectFrameImage_[SelectStateE::SelectNum];
	/** �Z���N�g�t���[���p�g�����X�t�H�[��. */
	RectTransform SelectFrameRT_[SelectStateE::SelectNum];

	Text OptionName_[SelectStateE::SelectNum];
	RectTransform OptionNameRT_[SelectStateE::SelectNum];


	Image SelectImage_;
	RectTransform SelectRT_;

};