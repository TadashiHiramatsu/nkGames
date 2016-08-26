#pragma once

class CPlayer : public CGameObject
{
public:
	//�R���X�g���N�^
	CPlayer();
	
	//�f�X�g���N�^
	~CPlayer();

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