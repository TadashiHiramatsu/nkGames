/**
 * @file	_Resources\nkSkinModelDataResources.h
 *
 * �X�L�����f���̃��\�[�X�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �X�L�����f���̃��\�[�X�Ǘ��N���X.
	 * �V���O���g���N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CSkinModelDataResources
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CSkinModelDataResources();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CSkinModelDataResources();
	
	public:

		/**
		 * �C���X�^���X�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The instance.
		 */
		static CSkinModelDataResources& GetInstance()
		{
			static CSkinModelDataResources instance;
			return instance;
		}

		/**
		 * �ǂݎ��.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	skinModelDataHandle	�X�L�����f���f�[�^�n���h��.
		 * @param 		  	filePath		   	�t�@�C���p�X.
		 * @param [in,out]	anim			   	�A�j���[�V����.
		 * @param 		  	isInstancing	   	(Optional) �C���X�^���V���O�t���O.
		 * @param 		  	numInstancing	   	(Optional) �C���X�^���X��.
		 */
		void Load(
			SkinModelDataHandle& skinModelDataHandle, 
			const char* filePath, 
			CAnimation* anim,
			bool isInstancing = false,
			int numInstancing = 0
		);

	private:

		/** Defines an alias representing the skin model data map. */
		typedef map<int, SkinModelDataPtrT> SkinModelDataMapT;
		/** �C���X�^���V���O���Ȃ���������g�����f����ۑ�. */
		SkinModelDataMapT SkinModelDataMap_;
		/** �C���X�^���V���O���f����ۑ�. */
		list<SkinModelDataPtrT> InstancingList_;

	};

	/**
	 * �X�L�����f���̃��\�[�X�Ǘ��N���X�̎擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to the CSkinModelDataResources.
	 */
	static CSkinModelDataResources& SMDResources()
	{
		return CSkinModelDataResources::GetInstance();
	}

}// namespace nkEngine