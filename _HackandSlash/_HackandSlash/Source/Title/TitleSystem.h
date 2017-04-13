/**
 * @file Source\Title\GUI\TitleSystem.h
 *
 * �^�C�g���V�X�e���N���X�̒�`.
 */
#pragma once

#include"HUD/TitleBack.h"
#include"HUD\TitleName.h"

#include"../Common/SceneEffect/Fade.h"

#include"GUI/TitleSelect\ITitleSelect.h"

/**
 * �^�C�g���V�X�e���N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
class TitleSystem : public IGameObject
{
public:

	/** �I���̏��. */
	enum class SelectStateE
	{
		StateBegin = 0,			//!< �X�e�[�g�̐擪.
		NewGame = StateBegin,	//!< ���߂���.
		Continue,				//!< ��������.
		Exit,					//!< �I��.
		StateEnd = Exit,		//!< �X�e�[�g�̏I�[.
		StateNum,				//!< �X�e�[�g��
	};

public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	TitleSystem()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	~TitleSystem()
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

private:

	/**
	* �Z���N�g�̏�����.
	*/
	void InitSelect();

	/**
	* �J�[�\���̏㉺�ړ�.
	*/
	bool CursorUpDownMove();

private:

	/** �Q�[�����\���N���X�̃|�C���^. */
	TitleName* TitleName_ = nullptr;

	/** �t�F�[�h�N���X�̃|�C���^*/
	Fade* Fade_ = nullptr;

	/** �^�C�g��BGM. */
	SoundSource* TitleBGM_ = nullptr;

	/** ���ݑI�𒆂̂���. */
	int NowSelect_;
	/** �Z���N�g���X�g. */
	ITitleSelect* SelectList_[(int)SelectStateE::StateNum];

	Image CursorImage_;
	RectTransform CursorRT_;

	/** ���肪�����ꂽ�t���O. */
	bool isDecision_ = false;

};