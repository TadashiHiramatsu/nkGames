/**
* �^�C�g���V�[���̃Z���N�g�̊��N���X�̒�`.
*/
#pragma once

/**
* �^�C�g���V�[���̃Z���N�g�̊��N���X.
* �^�C�g���̃Z���N�g�͂��ׂĂ�����p������.
*/
class ITitleSelect : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	ITitleSelect()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	virtual ~ITitleSelect()
	{
	}

	/**
	* ������.
	*/
	virtual void Start()override;

	/**
	* �X�V.
	*/
	virtual void Update()override;

	/**
	* �|�X�g�G�t�F�N�g��̕`��.
	*/
	virtual void PostRender()override;

	/**
	* �I�����ꂽ��.
	*/
	virtual bool OnTrigger() = 0;

	/**
	* ���N�g�g�����X�t�H�[���̎擾.
	*/
	RectTransform& GetRectTransform()
	{
		return SelectRT_;
	}

protected:

	/** �摜. */
	Image SelectImage_;
	/** �g�����X�t�H�[��. */
	RectTransform SelectRT_;

};