/**
* ���j���[�o�[�N���X�̒�`.
*/
#pragma once

/**
* ���j���[�o�[�N���X.
*/
class MenuBar : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	MenuBar()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~MenuBar()
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
	* �`��.
	*/
	void Render()override;

	/** 
	*�g�����X�t�H�[���̎擾. 
	*/
	RectTransform* GetTransform()
	{
		return &BarTransform_;
	}

private:

	/** �{�̂̉摜. */
	Image BarImage_;
	/** �{�̂̃g�����X�t�H�[��. */
	RectTransform BarTransform_;

};