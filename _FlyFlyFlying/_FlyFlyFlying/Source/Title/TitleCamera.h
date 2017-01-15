/**
 * @file Source\Title\TitleCamera.h
 *
 * �^�C�g���J�����N���X�̒�`.
 */
#pragma once

/**
 * �^�C�g���J�����N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
class TitleCamera : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	TitleCamera()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	~TitleCamera()
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
	 * �J�����N���X�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 *
	 * @return Null if it fails, else the camera.
	 */
	Camera* GetCamera()
	{
		return &Camera_;
	}

private:

	/** �J����. */
	Camera Camera_;

};