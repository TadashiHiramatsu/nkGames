#pragma once

class CLeg : public CGameObject
{
public:
	//�R���X�g���N�^
	CLeg();

	//�f�X�g���N�^
	~CLeg();

	//������
	void Init()override;

	//�X�V
	void Update()override;

	//�`��
	void Render()override;

	//�J��
	void Release()override;

	void SetLight(CLight* light)
	{
		m_model.SetLight(light);
	}

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