/**
 * @file _Graphics\_Shape\nkShape.cpp
 *
 * �`��̊��N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkShape.h"

namespace nkEngine
{
	
	//�X�^�e�B�b�N�ϐ��̒�`
	Light IShape::DefaultLight_;
	bool IShape::isInitDefaultLight_ = false;

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	IShape::IShape()
	{
		if (!isInitDefaultLight_) {
			//�f�t�H���g���C�g�̏������B
			DefaultLight_.SetAmbientLight(Vector3(1.0f, 1.0f, 1.0f));
			isInitDefaultLight_ = true;
		}
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	IShape::~IShape()
	{
		Release();
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	void IShape::Update()
	{
	}

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	void IShape::Render()
	{
	}

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	void IShape::Release()
	{
	}

}