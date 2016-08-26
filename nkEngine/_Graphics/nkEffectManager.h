#pragma once

namespace nkEngine
{
	class CEffectManager
	{
	public:
	
		//�G�t�F�N�g�̃��[�h
		//param[in] �t�@�C���p�X
		//return ���[�h�����G�t�F�N�g
		ID3DXEffect* LoadEffect(const char* filePath);

		//�����[�X
		void Release();

		//�C���X�^���X�擾
		inline static CEffectManager& instance()
		{
			static CEffectManager instance;
			return instance;
		}
	private:
		//�R���X�g���N�^
		CEffectManager();

		//�f�X�g���N�^
		~CEffectManager();
	private:
		map<int, ID3DXEffect*> m_effectDictinary; //�G�t�F�N�g�̃f�B�N�V���i���A�t�@�C���p�X�̃n�b�V���l���L�[�ɂ���
	};
	inline static CEffectManager& EffectManager()
	{
		return CEffectManager::instance();
	}
}