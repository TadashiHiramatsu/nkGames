#pragma once

namespace nkEngine
{

	//�C���[�W�N���X
	//2D�̉摜���X�N���[���ɕ`�悵�܂�
	class Image
	{
	public:

		//�R���X�g���N�^
		Image();
		//�f�X�g���N�^
		~Image();

		//�t�@�C���̃��[�h���s��
		void Load(const char* _filepass);
		void Load(shared_ptr<CTexture>& _tex);
		void Load();

		//�������݂̂��s��
		void Init();
		
		//�`��
		void Render();
		
		//�e�N�X�`����ݒ肷��
		void SetTexture(shared_ptr<CTexture>& _tex)
		{
			Texture = _tex;
		}

		//�g�����X�t�H�[����ݒ肷��
		void SetTransform(RectTransform* _rt)
		{
			rectTransform = _rt;
		}

	private:
		ID3DXEffect* pEffect; //�����Ȃ��Ă���
		CPrimitive Primitive;
		shared_ptr<CTexture> Texture;

		RectTransform* rectTransform;
	};
}