/**
 * @file	Source\Game\GUI\ExpGage.h
 *
 * �o���l�Q�[�W�N���X�̒�`.
 */
#pragma once

#include"..\Player\Player.h"

/**
 * �o���l�Q�[�W�N���X.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class ExpGage : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	ExpGage();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~ExpGage();

	/**
	 * ������.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Update()override;

	/**
	 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void PostRender()override;

	/**
	 * �v���C���[�̃|�C���^��ݒ�.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @param [in,out]	p	If non-null, the p.
	 */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** �t���[���p. */
	RectTransform ExpFrameTransform_;
	/** �t���[����Image. */
	Image ExpFrameImage_;
	/** �{�̗p. */
	RectTransform ExpTransform_;
	/** �{�̂�Image. */
	Image ExpImage_;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;
	/** ���݂̕K�v�o���l. */
	int* NextExp_;
	/** ���݂̎擾�o���l. */
	int* NowExp_;

	/** ���݂̃��x����\������. */
	TestFont Level_;

};