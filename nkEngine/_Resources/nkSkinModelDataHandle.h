#pragma once

namespace nkEngine
{
	//�X�L�����f���̃n���h���N���X
	class CSkinModelDataHandle
	{
	public:
		//�X�L�����f���f�[�^�̐��|�C���^���擾
		CSkinModelData* GetBody()
		{
			//�N���[���쐬���Ă�����
			if (SkinModelData)
			{
				return SkinModelData.get();
			}
			return OriginSkinModelData.get();
		}

		//������
		void Init(const shared_ptr<CSkinModelData>& _Skin, CAnimation* _Anim, bool _isClone);
	
	private:
		//�I���W�i�����f���f�[�^
		shared_ptr<CSkinModelData> OriginSkinModelData;
		//���f���f�[�^
		//�A�j���[�V����������ꍇ
		//�N���[���쐬���Ȃ��Ɠ������������Ă��܂�
		unique_ptr<CSkinModelData> SkinModelData;
	};
}