#pragma once

namespace nkEngine
{
	struct SpriteTransform
	{
		D3DXVECTOR2 Position = D3DXVECTOR2(0, 0); //�|�W�V����
		D3DXVECTOR2 Size = D3DXVECTOR2(100, 100);	//�T�C�Y
		D3DXVECTOR2 Pivot = D3DXVECTOR2(0.5f, 0.5f);	//���S
		D3DXQUATERNION Rotation = D3DXQUATERNION(0, 0, 0, 1);	//��]
	};

	class CSprite
	{
	public:

		//�R���X�g���N�^
		CSprite();
		
		//�f�X�g���N�^
		~CSprite();

		//�t�@�C���̃��[�h���s��
		void Load(const char* filepass);
		void Load();

		//�������݂̂��s��
		void Init();
		
		//�X�V
		void Update();
		
		//�`��
		void Render();
		
		//���
		void Release();
		
		//�e�N�X�`����ݒ肷��
		void SetTexture(CTexture* tex)
		{
			Texture = tex;
		}

		//�g�����X�t�H�[���ݒ�
		void SetSTransform(SpriteTransform* _ST)
		{
			STransform = _ST;
		}

	private:
		ID3DXEffect* m_pEffect = nullptr;
		CPrimitive Primitive;
		CTexture* Texture = nullptr;

		D3DXMATRIX  m_mWorld;

		SpriteTransform* STransform;
	};
}