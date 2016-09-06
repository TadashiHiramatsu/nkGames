#pragma once

class CObject : public CGameObject
{
public:
	//�R���X�g���N�^
	CObject();

	//�f�X�g���N�^
	~CObject();

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