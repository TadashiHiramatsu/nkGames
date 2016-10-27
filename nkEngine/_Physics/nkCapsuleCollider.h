#pragma once

#include"CCollider.h"

namespace nkEngine
{
	//�J�v�Z���R���C�_�[
	class CCapsuleCollider : public CCollider
	{
	public:
		CCapsuleCollider();
		~CCapsuleCollider();

		//�J�v�Z���R���C�_�[�쐬
		//param[in] �T�C�Y
		void Create(float radius, float height)
		{
			m_Shape = new btCapsuleShape(radius, height);
		}

		//�{�f�B�̎擾
		btCollisionShape* GetBody()override
		{
			return m_Shape;
		}

	private:
		btCapsuleShape* m_Shape; //�{�b�N�X�`��
	};
}