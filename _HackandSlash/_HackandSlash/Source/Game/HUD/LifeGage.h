/**
 * @file	Source\Game\GUI\LifeGage.h
 *
 * �v���C���[�̃��C�t��`�悷��N���X�̒�`.
 */
#pragma once

#include"..\Player\Player.h"

/**
 * ���C�t�Q�[�W�N���X.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
class LifeGage : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	LifeGage()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	~LifeGage()
	{
	}

	/**
	 * ������.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void Update()override;

	/**
	 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void PostRender()override;

	/**
	 * �v���C���[�̃|�C���^��ݒ�.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 *
	 * @param [in]	p	If non-null, the p.
	 */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** �t���[���p. */
	RectTransform LifeFrameTransform_;
	/** �t���[����Image. */
	Image LifeFrameImage_;
	/** �{�̗p. */
	RectTransform LifeTransform_;
	/** Life��Image. */
	Image LifeImage_;

	/** ���C�t�̐��l��\������t�H���g. */
	Text Life_;
	RectTransform TextTransform_;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;
	/** ���݂̗̑͂̍ő�l. */
	int* MaxLife_;
	/** ���݂̗̑͂̒l. */
	int* NowLife_;

	D3DXVECTOR2 value;

};