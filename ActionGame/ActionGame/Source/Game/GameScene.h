/**
 * @file Source\Game\GameScene.h
 *
 * �Q�[���V�[���N���X�̒�`.
 */
#pragma once

/**
 * �Q�[���V�[���N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class GameScene : public IScene
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	GameScene();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~GameScene();

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

};