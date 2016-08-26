#pragma once

class CGround : public CGameObject
{
public:
	//�R���X�g���N�^
	CGround();

	//�f�X�g���N�^
	~CGround();

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