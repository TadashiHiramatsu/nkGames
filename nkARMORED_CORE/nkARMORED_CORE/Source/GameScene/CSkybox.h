#pragma once

class CSkybox : public CGameObject
{
public:
	//�R���X�g���N�^
	CSkybox();

	//�f�X�g���N�^
	~CSkybox();

	//������
	void Init()override;

	//�X�V
	void Update()override;

	//�`��
	void Render()override;

	//�J��
	void Release()override;
private:
	CModelRender m_model;
	CTransform m_trans;
	CLight m_light;
};