/**
 * @file	_Resources\nkSkinModelDataHandle.cpp
 *
 * �X�L�����f���̃n���h���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSkinModelDataHandle.h"

namespace nkEngine
{

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	SkinModelDataHandle::SkinModelDataHandle() :
		SkinModelData_(nullptr)
	{
	}

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	SkinModelDataHandle::~SkinModelDataHandle()
	{
	}

	/**
	 * ������.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param 		  	skin   	�X�L��.
	 * @param [in,out]	anim   	�A�j���[�V����.
	 * @param 		  	isClone	�N���[���t���O.
	 */
	void SkinModelDataHandle::Init(const SkinModelDataPtrT& skin, Animation* anim, bool isClone)
	{
		OriginSkinModelData_ = skin;
		if (isClone)
		{
			//�N���[�����쐬
			SkinModelData_.reset(new SkinModelData);
			SkinModelData_->CloneModelData(*skin, anim);
		}
	}

}
