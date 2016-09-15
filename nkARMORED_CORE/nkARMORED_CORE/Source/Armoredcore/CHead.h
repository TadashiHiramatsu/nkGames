#pragma once

class CHead : public CGameObject
{
public:
	//�R���X�g���N�^
	CHead();

	//�f�X�g���N�^
	~CHead();

	//������
	void Init()override;

	//�X�V
	void Update()override;

	//�`��
	void Render()override;

	//�J��
	void Release()override;

	//�R�A�̃��C�g�ݒ�
	void SetLight(CLight* light)
	{
		m_model.SetLight(light);
	}

	//�R�A�̃J�����ݒ�
	void SetCamera(CCamera* camera)
	{
		m_model.SetCamera(camera);
	}

	void SetParentMatrix(D3DXMATRIX* parent)
	{
		m_model.SetParentMatrix(parent);
	}

private:
	CACModelRender m_model; //���r�̃��f��
	CTransform m_trans; //�g�����X�t�H�[��
};