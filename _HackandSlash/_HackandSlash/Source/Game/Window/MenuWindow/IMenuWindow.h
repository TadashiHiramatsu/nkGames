/**
* ���j���[�E�B���h�E�̊��N���X�̒�`.
*/
#pragma once

#include"../../Player/Player.h"

/**
* ���j���[�E�B���h�E�̊��N���X.
*/
class IMenuWindow
{
public:

	/**
	* �R���X�g���N�^.
	*/
	IMenuWindow()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	virtual ~IMenuWindow()
	{
	}

	/** 
	* ������
	*/
	virtual void Start(RectTransform* rt, float namepos) = 0;

	/**
	* �X�V
	*/
	virtual void Update() = 0;

	/**
	* �`��
	*/
	virtual void Render() = 0;

	/**
	* �\�����̏�����.
	*/
	void NameStart(RectTransform* parent, const char* filepath, float pos,float width);

	/**
	* �\�����̍X�V
	*/
	void NameUpdate()
	{
		NameTransform_.Update();
	}

	/**
	* �\�����̕`��
	*/
	void NameRender()
	{
		NameImage_.Render();
	}

	/**
	* �\�����̃��N�g�g�����X�t�H�[�����擾.
	*
	* @return	���N�g�g�����X�t�H�[��.
	*/
	const RectTransform& GetNameTransform() const
	{
		return NameTransform_;
	}

	RectTransform* GetNameTransformPointer()
	{
		return &NameTransform_;
	}

	/** 
	* �E�B���h�E�����Ƃ��̏���.
	*/
	virtual void Close() 
	{
	}

	/**
	* �v���C���[�̃|�C���^��ݒ�.
	*/
	void SetPlayer(Player* player)
	{
		Player_ = player;
	}

protected:

	/** ���O�摜. */
	Image NameImage_;
	/** ���O�g�����X�t�H�[��. */
	RectTransform NameTransform_;

	/** �v���C���[�̃|�C���^. */
	Player* Player_ = nullptr;

};
