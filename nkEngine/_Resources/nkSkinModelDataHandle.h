/**
 * @file	_Resources\nkSkinModelDataHandle.h
 *
 * �X�L�����f���̃n���h���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{
	/** shared_ptr<SkinModelData>�������₷���Z�k. */
	typedef shared_ptr<SkinModelData> SkinModelDataPtrT;

	/**
	 * �X�L�����f���̃n���h���N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class SkinModelDataHandle : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		SkinModelDataHandle()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~SkinModelDataHandle()
		{
		}

		/**
		 * �X�L�����f���f�[�^�̐��|�C���^���擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		SkinModelData* GetBody()
		{
			//�N���[���쐬���Ă�����
			if (SkinModelData_)
			{
				return SkinModelData_.get();
			}
			return OriginSkinModelData_.get();
		}

		/**
		 * �ǂݍ���.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param 		  	skin   	�X�L��.
		 * @param [in,out]	anim   	�A�j���[�V����.
		 * @param 		  	isClone	�N���[���t���O.
		 */
		void Load(const SkinModelDataPtrT& skin, Animation* anim, bool isClone);
	
	private:

		/** �I���W�i�����f���f�[�^. */
		SkinModelDataPtrT OriginSkinModelData_;
		/**   
		 * ���f���f�[�^   
		 * �A�j���[�V����������ꍇ 
		 * �N���[���쐬���Ȃ��Ɠ������������Ă��܂�.
		 */
		unique_ptr<SkinModelData> SkinModelData_;

	};

}// namespace nkEngine