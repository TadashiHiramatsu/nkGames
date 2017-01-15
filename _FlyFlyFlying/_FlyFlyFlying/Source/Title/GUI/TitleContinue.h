/**
 * @file Source\Title\GUI\TitleContinue.h
 *
 * �^�C�g���R���e�B�j���[�N���X�̒�`.
 */
#pragma once

/**
 * �^�C�g���R���e�B�j���[�N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
class TitleContinue : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	TitleContinue()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	~TitleContinue()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	void Update()override;

	/**
	 * �|�X�g�G�t�F�N�g��̕`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	void PostRender()override;

private:

	/** �R���e�B�j���[�摜. */
	Image ContinueImage_;
	/** �R���e�B�j���[�摜�p�g�����X�t�H�[��. */
	RectTransform ContinueRT_;

};