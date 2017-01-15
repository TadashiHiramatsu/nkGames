/**
 * @file Source\Title\GUI\TitleStart.h
 *
 * �^�C�g���X�^�[�g�N���X�̒�`.
 */
#pragma once

/**
 * �^�C�g���X�^�[�g�N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
class TitleStart : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	TitleStart()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	~TitleStart()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Update()override;

	/**
	 * �|�X�g�G�t�F�N�g��̕`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void PostRender()override;

private:

	/** �X�^�[�g�摜. */
	Image StartImage_;
	/** �X�^�[�g�摜�p�g�����X�t�H�[��. */
	RectTransform StartRT_;

};