#pragma once

class CPlayer : public CGameObject
{
public:
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//�����B
		AnimationWalk,		//�����B
		AnimationRun,		//����B
		AnimationJump,		//�W�����v�B
	};
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

	//�A�j���[�V�����Đ�
	void PlayAnimation(AnimationNo animNo);

private:
	//��]
	void Rotation();
	//�ړ�
	void Move();
private:
	CModelRender m_model; //���f��
	CLight m_light; //���C�g
	CTexture m_normal; //�@���e�N�X�`��
	CTexture m_spec; //�X�y�L�����e�N�X�`��
	CAnimation* m_anim; //�A�j���[�V����
	AnimationNo currentAnimSetNo; //���݂̃A�j���[�V����

	CTransform m_trans; //�g�����X�t�H�[��
	
	D3DXVECTOR3 m_Target; //�����_
	D3DXVECTOR3 m_direction_Z;
	D3DXVECTOR3 m_direction_X;
	float m_TargetLen;
};