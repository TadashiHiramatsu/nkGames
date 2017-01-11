/**
 * @file Source\Title\HUD\TitleBack.h
 *
 * �^�C�g���o�b�N�N���X�̒�`.
 */
#pragma once

/**
 * �^�C�g���o�b�N�N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class TitleBack : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	TitleBack();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~TitleBack();

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update()override;

	/**
	 * �|�X�g�G�t�F�N�g��̕`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void PostRender()override;

private:

	/** �w�i�摜. */
	Image BackImage_;
	/** �w�i�摜�p�g�����X�t�H�[��. */
	RectTransform BackRT_;

};