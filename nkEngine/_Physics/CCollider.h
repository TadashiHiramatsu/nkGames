//�R���C�_�[
#pragma once

namespace nkEngine
{
	class CCollider
	{
	public:

		//�{�f�B�̎擾
		virtual btCollisionShape* GetBody() = 0;
	};

}