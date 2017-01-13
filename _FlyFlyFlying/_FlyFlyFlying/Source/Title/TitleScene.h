/**
 * @file Source\Title\TitleScene.h
 *
 * �^�C�g���V�[���N���X�̒�`.
 */
#pragma once


class TitleScene : public IScene
{
public:
	TitleScene();
	~TitleScene();
	void Start()override;

private:
	CTitle  m_title;
	CTitleStart m_start;
	CTitleContinue m_continue;
	Ccamera m_camera;
	CTitleUnitychan m_Unitychan;

};