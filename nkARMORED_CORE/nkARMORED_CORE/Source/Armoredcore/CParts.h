#pragma once

class CParts : public CGameObject
{
public:

	//�R���X�g���N�^
	CParts();

	//�f�X�g���N�^
	~CParts();

	//������
	virtual void Init()override;

	//�X�V
	virtual void Update()override;

	//�`��
	virtual void Render()override;

	//�J��
	virtual void Release()override;

	//�ǂݍ���
	void LoadModel(const char* filepass);

	inline CACModelRender* GetACModel()
	{
		return &m_ACModel;
	}

	inline CAnimation* GetAnimation()
	{
		return &m_Animation;
	}

	inline D3DXMATRIX* GetMatrix(const char* pass)
	{
		D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_ACModel.GetFrame(), pass);
		return &frame->CombinedTransformationMatrix;
	}

protected:
	CACModelRender m_ACModel; //���f��
	CTransform m_Transform; //�g�����X�t�H�[��
	CAnimation m_Animation; //�A�j���[�V�����Ǘ�
};