#pragma once

#include"CCollider.h"

namespace nkEngine
{
	class CSphereCollider : public CCollider
	{
	public:

		//�R���X�g���N�^
		CSphereCollider();

		//�f�X�g���N�^
		~CSphereCollider();

		//���̃R���C�_�[�쐬
		//param[in] �T�C�Y
		void Create(const float _radius);

		//�{�f�B�̎擾
		btCollisionShape* GetBody()override
		{
			return m_Shape;
		}

	private:
		btSphereShape* m_Shape; //���̌`��
	};

}