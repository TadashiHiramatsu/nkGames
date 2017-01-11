/**
 * @file _GameObject\nkGameObject.cpp
 *
 * �Q�[���I�u�W�F�N�g�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkGameObject.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	IGameObject::IGameObject() :
		isActive_(true),
		isStart_(false)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	IGameObject::~IGameObject()
	{
	}

}// namespace nkEngine