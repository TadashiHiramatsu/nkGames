/**
* �^�C�g���V�[���̃Q�[���^�C�g���\���N���X�̒�`.
*/
#pragma once

/**
* �^�C�g���V�[���̃Q�[���^�C�g���\���N���X.
*/
class TitleName : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	TitleName()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~TitleName()
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
	* �t�F�[�h�t���O�̎擾.
	*/
	bool IsFade()
	{
		return isFade_;
	}

private:

	/** �^�C�g���l�[���摜. */
	Image TitleNameImage_;
	/** �^�C�g���l�[���p�g�����X�t�H�[��. */
	RectTransform TitleNameRT_;

	/** �t�F�[�h�t���O. */
	bool isFade_ = false;

	/** �t�F�[�h�̑��x. */
	float FadeSpeed;


};