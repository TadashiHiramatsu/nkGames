/**
 * @file _Graphics\nkEffectManager.h
 *
 * �G�t�F�N�g�}�l�[�W���N���X�̒�`.
 */
#pragma once

#include"nkEffect.h"

namespace nkEngine
{

	/**
	 * �G�t�F�N�g�}�l�[�W���N���X.
	 * �V���O���g���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CEffectManager : Noncopyable
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CEffectManager()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CEffectManager()
		{
			Release();
		}
	
	public:

		/**
		 * �G�t�F�N�g�̃��[�h.
		 * "Asset/Shader/"�t�H���_���烍�[�h���܂�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param filePath �t�@�C���p�X�B"Asset/Shader/"���Ȃ����t�@�C���p�X.
		 *
		 * @return ���[�h�����G�t�F�N�g.
		 */
		Effect* LoadEffect(const char* filePath);

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * �C���X�^���X�擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return A reference to a CEffectManager.
		 */
		inline static CEffectManager& instance()
		{
			static CEffectManager instance;
			return instance;
		}

	private:
		
		/** �G�t�F�N�g�̃f�B�N�V���i���A�t�@�C���p�X�̃n�b�V���l���L�[�ɂ���. */
		map<int, Effect*> EffectDictinary_;

	};

	/**
	 * �G�t�F�N�g�}�l�[�W���N���X�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CEffectManager.
	 */
	inline static CEffectManager& EffectManager()
	{
		return CEffectManager::instance();
	}

}// namespace nkEngine