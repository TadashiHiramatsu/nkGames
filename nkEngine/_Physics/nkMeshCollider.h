/**
 * @file	_Physics\nkMeshCollider.h
 *
 * ���b�V���R���C�_�[�N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"
#include"../_Graphics/_ModelRender/nkModelRender.h"

namespace nkEngine
{

	/**
	 * ���b�V���R���C�_�[�N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class MeshCollider : public ICollider
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		MeshCollider()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~MeshCollider()
		{
		}

		/**
		 * ModelRender����Mesh�R���C�_�[�𐶐�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	model			�X�L�����f��.
		 * @param 		  	offsetMatrix	�I�t�Z�b�g�s��.
		 */
		void Create(ModelRender* model, const Matrix* offsetMatrix);

		/**
		 * �{�f�B���擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		btCollisionShape* GetBody() override
		{
			return MeshShape_;
		}

		/**
		* ���.
		*/
		void Release()override
		{
			//���_�o�b�t�@�z��̍폜
			for (auto& vb : VertexBufferArray_)
			{
				delete vb;
			}

			//�C���f�b�N�X�o�b�t�@�̍폜
			for (auto& ib : IndexBufferArray_)
			{
				delete ib;
			}
			delete StridingMeshInterface_;
		}

	private:

		/** ���_�o�b�t�@. */
		typedef std::vector<Vector3> VertexBufferT;
		/** �C���f�b�N�X�o�b�t�@. */
		typedef std::vector<unsigned int> IndexBufferT;
		/** ���_�o�b�t�@�̔z��. */
		std::vector<VertexBufferT*> VertexBufferArray_;
		/** �C���f�b�N�X�o�b�t�@�̔z��. */
		std::vector<IndexBufferT*> IndexBufferArray_;
		/** ���b�V���`��. */
		btBvhTriangleMeshShape* MeshShape_ = nullptr;
		/** �g���C�A���O���C���f�b�N�X�o�b�t�@. */
		btTriangleIndexVertexArray* StridingMeshInterface_ = nullptr;

	};

}// namespace nkEngine