#pragma once

#include"nkUITransform.h"

namespace nkEngine
{
	class Image
	{
	public:

		//�R���X�g���N�^
		Image();
		
		//�f�X�g���N�^
		~Image();

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
		void SetTexture(shared_ptr<CTexture>& tex)
		{
			Texture = tex;
		}

		void SetTransform(UITransform* _tf)
		{
			Transform = _tf;
		}

	private:
		ID3DXEffect* m_pEffect = nullptr;
		CPrimitive Primitive;
		shared_ptr<CTexture> Texture;

		UITransform* Transform;
	};
}