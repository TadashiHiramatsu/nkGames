/**
* �t�F�[�h�N���X�̒�`.
*/
#pragma once

/**
* �t�F�[�h�N���X.
*/
class Fade : public IGameObject
{
public:

	/** �t�F�[�h�̏��. */
	enum FadeStateE
	{
		FadeIn,			//!< �t�F�[�h�C��.
		FadeOut,		//!< �t�F�[�h�A�E�g.
		FadeCompletion,	//!< �t�F�[�h����.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	Fade()
	{
		SetActive(false);
	}

	/**
	* �f�X�g���N�^.
	*/
	~Fade()
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
	* �t�F�[�h�A�E�g�J�n.
	*/
	void StartFadeOut()
	{
		State_ = FadeOut;
		FadeNowAlpha_ = 0;
		SetActive(true);
	}

	/**
	* �t�F�[�h�C���J�n.
	*/
	void StartFadeIn()
	{
		State_ = FadeIn;
		FadeNowAlpha_ = 1;
		SetActive(true);
	}
	
	/**
	* ���݂̏�Ԃ��擾.
	*/
	FadeStateE GetState()
	{
		return State_;
	}

	/**
	* �t�F�[�h�̑�����ݒ�.
	*/
	void SetFadeSpeed(float speed)
	{
		FadeSpeed_ = speed;
	}

private:

	/** �t�F�[�h�̉摜�`��. */
	Image FadeImage_;
	/** �t�F�[�h�̃g�����X�t�H�[��. */
	RectTransform FadeTransform_;

	/** ���݂̃A���t�@�l. */
	float FadeNowAlpha_ = 0;

	/** �t�F�[�h�̏��. */
	FadeStateE State_ = FadeStateE::FadeCompletion;

	/** �t�F�[�h�̑���(�b). */
	float FadeSpeed_ = 1;

};