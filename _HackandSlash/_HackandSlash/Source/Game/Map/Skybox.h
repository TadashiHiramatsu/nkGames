/**
 * @file Source\Game\Map\Skybox.h
 *
 * �X�J�C�{�b�N�X�N���X�̒�`.
 */
#pragma once

#include"..\Player\Player.h"

/**
 * �X�J�C�{�b�N�X�N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class Skybox : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Skybox()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~Skybox()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Update()override;

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Render()override;

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Release()override;

	/**
	 * �v���C���[�̃|�C���^��ݒ�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] p If non-null, the pla.
	 */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** ���f�������_�[. */
	ModelRender ModelRender_;
	/** ���C�g. */
	Light Light_;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;

};