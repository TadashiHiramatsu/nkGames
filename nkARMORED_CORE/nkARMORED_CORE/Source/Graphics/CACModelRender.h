#pragma once

class CACModelRender : public CModelRender
{
public:
	CACModelRender();
	~CACModelRender();
	
	//�X�V�̃I�[�o�[���C�h
	void Update()override;
	
	//�e�s��̐ݒ�
	void SetParentMatrix(D3DXMATRIX* parent)
	{
		m_mParent = parent;
	}

private:
	D3DXMATRIX* m_mParent; //�e�̃��[���h�s��
};