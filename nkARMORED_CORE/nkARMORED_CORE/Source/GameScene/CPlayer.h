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
	CModelRender m_model;
	CTransform m_trans;
	CLight m_light;
	CTexture normal; //�@��
	CAnimation* m_anim;
	AnimationNo currentAnimSetNo;
};