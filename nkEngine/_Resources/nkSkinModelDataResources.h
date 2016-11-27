#pragma once

namespace nkEngine
{
	//�����₷���Z�k
	typedef shared_ptr<CSkinModelData> CSkinModelDataPtr;

	//�X�L�����f���̃��\�[�X�Ǘ�
	class CSkinModelDataResources
	{
	private:
		//�R���X�g���N�^
		CSkinModelDataResources();
		//�f�X�g���N�^
		~CSkinModelDataResources();
	
	public:

		static CSkinModelDataResources& GetInstance()
		{
			static CSkinModelDataResources instance;
			return instance;
		}

		//�ǂݎ��
		//param[out] �X�L�����f���f�[�^�n���h��
		//param[in]  �t�@�C���p�X
		//param[in]  �A�j���[�V����
		//param[in]  �C���X�^���V���O�t���O
		//param[in]  �C���X�^���X��
		void Load(CSkinModelDataHandle& _SkinModelDataHandle, const char* _FilePath, CAnimation* _Anim, bool _isInstancing = false, int _NumInstancing = 0);

		//�X�V
		void Update();

	private:
		typedef map<int, CSkinModelDataPtr> CSkinModelDataMap;
		//�C���X�^���V���O���Ȃ���������g�����f����ۑ�
		CSkinModelDataMap SkinModelDataMap;
		//�C���X�^���V���O���f����ۑ�
		list<CSkinModelDataPtr> InstancingList;
	};

	static CSkinModelDataResources& SMDResources()
	{
		return CSkinModelDataResources::GetInstance();
	}
}