/**
 * @file Source\Title\GUI\TitleSystem.h
 *
 * �^�C�g���V�X�e���N���X�̒�`.
 */
#pragma once

#include"../HUD/TitleBack.h"
#include"../../Common/SceneEffect/Fade.h"

/**
 * �^�C�g���V�X�e���N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
class TitleSystem : public IGameObject
{
public:

	/** �^�C�g���̏��. */
	enum class TitleStateE
	{
		StartUp,	//!< �N��
		Run,		//!< �ғ�
		BlackOut,	//!< �u���b�N�A�E�g
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
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void Update()override;

	/**
	 * �|�X�g�G�t�F�N�g��̕`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void PostRender()override;

private:

	/** �^�C�g���l�[���摜. */
	Image TitleNameImage_;
	/** �^�C�g���l�[���p�g�����X�t�H�[��. */
	RectTransform TitleNameRT_;

	/** �j���[�Q�[���摜. */
	Image NewGameImage_;
	/** �j���[�Q�[���p�g�����X�t�H�[��. */
	RectTransform NewGameRT_;

	/** �R���e�B�j���[�摜. */
	Image ContinueImage_;
	/** �R���e�B�j���[�p�g�����X�t�H�[��. */
	RectTransform ContinueRT_;

	/** �X�e�[�g. */
	TitleStateE State_ = TitleStateE::StartUp;

	/** �t�F�[�h�N���X�̃|�C���^*/
	Fade* Fade_ = nullptr;

	/** �^�C�g��BGM. */
	SoundSource* TitleBGM_ = nullptr;

};