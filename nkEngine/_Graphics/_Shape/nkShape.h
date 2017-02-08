/**
 * @file _Graphics\_Shape\nkShape.h
 *
 * �`��̊��N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �`��̊��N���X.
	 * ���ׂĂ̌`��͂��̃N���X���p������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/18
	 */
	class IShape
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		IShape();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/18
		 */
		virtual ~IShape();

		/**
		 * ���[���h�s��̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @return The world matrix.
		 */
		const D3DXMATRIX& GetWorldMatrix()const
		{
			return WorldMatrix_;
		}

		/**
		 * ��]�s��̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @return The rotation matrix.
		 */
		const D3DMATRIX& GetRotationMatrix()const
		{
			return RotationMatrix_;
		}

		/**
		 * ���W��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param pos The position.
		 */
		void SetPosition(const D3DXVECTOR3& pos)
		{
			Position_ = pos;
		}

		/**
		 * ��]��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @param rot The rot.
		 */
		void SetRotation(const D3DXQUATERNION& rot)
		{
			Rotation_ = rot;
		}

		/**
		 * �v���~�e�B�u���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 *
		 * @return Null if it fails, else the primitive.
		 */
		Primitive* GetPrimitive()
		{
			return Primitive_;
		}

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 */
		void Update();

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 */
		void Render();

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/19
		 */
		void Release();

	protected:

		/** �����Ńv���~�e�B�u���쐬�������t���O. */
		bool isCreatePrimitive_ = false;
		/** �v���~�e�B�u�̃|�C���^. */
		Primitive* Primitive_ = nullptr;

		/** ���W. */
		D3DXVECTOR3 Position_ = D3DXVECTOR3(0, 0, 0);
		/** ��]. */
		D3DXQUATERNION Rotation_ = D3DXQUATERNION(0, 0, 0, 1);

		/** ���[���h�s��. */
		D3DXMATRIX WorldMatrix_;
		/** ��]�s��. */
		D3DXMATRIX RotationMatrix_;

		/** �G�t�F�N�g. */
		Effect* Effect_ = nullptr;
		
		/** ���C�g�N���X. */
		static Light DefaultLight_;
		/** ���C�g�N���X�������t���O. */
		static bool isInitDefaultLight_;
	
	};

	/**
	 * �|���S�����\����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 */
	struct PolygonInfoS
	{
	public:

		/** �ʖ@��. */
		D3DXVECTOR3 Normal_;
		/** �ʂ��\�����钸�_. */
		int VertexNo_[3];

	};

	/**
	 * ���_�o�b�t�@�̖@�����쐬.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 *
	 * @tparam TVertex ���_�o�b�t�@.
	 * @tparam TIndex  �C���f�b�N�X�o�b�t�@.
	 * @param [in,out] vertexBuffer ���_�o�b�t�@�o�b�t�@��vector.
	 * @param [in,out] indexBuffer  �C���f�b�N�X�o�b�t�@��vector.
	 * @param 		   primType	    �v���~�e�B�u�^�C�v.
	 */
	template<class TVertex,class TIndex>
	void CreateVertexNormal(vector<TVertex>& vertexBuffer, vector<TIndex>& indexBuffer, Primitive::TypeE primitiveType)
	{
		//�ʖ@�������߂�
		
		int numFace = (int)indexBuffer.size() / 3;

		//�|���S�����
		unique_ptr<PolygonInfoS[]> polygonInfoPtr;
		//�|���S�����z��
		vector<list<PolygonInfoS>> polygonInfoList;
	
		polygonInfoList.resize(vertexBuffer.size());

		for (int i = 0; i < numFace; i++)
		{
			//���W
			D3DXVECTOR3 pos[3];
			int t = i * 3;

			//�|���S�����
			PolygonInfoS polygonInfo;

			//���_�ԍ����R�s�[
			polygonInfo.VertexNo_[0] = indexBuffer.at(t);
			polygonInfo.VertexNo_[1] = indexBuffer.at(t+1);
			polygonInfo.VertexNo_[2] = indexBuffer.at(t+2);

			if (polygonInfo.VertexNo_[0] == polygonInfo.VertexNo_[1] ||
				polygonInfo.VertexNo_[0] == polygonInfo.VertexNo_[2] ||
				polygonInfo.VertexNo_[1] == polygonInfo.VertexNo_[2]) 
			{
				//�k�ރ|���S��
				//���_����v���Ă��ĕ`�悵�Ȃ��|���S���H�������ԁH
				continue;
			}

			//�@��
			D3DXVECTOR3 normal = D3DXVECTOR3(0, 0, 0);
			//���_���W
			D3DXVECTOR3 vertexPos[3];
			
			for (int i = 0; i < 3; i++)
			{
				//���_�o�b�t�@���R�s�[
				const TVertex& vertex = vertexBuffer.at(polygonInfo.VertexNo_[i]);
				//���_���W���R�s�[
				vertexPos[i] = D3DXVECTOR3(vertex.pos[0], vertex.pos[1], vertex.pos[2])
			}

			D3DXVECTOR3 t0, t1;
			t0 = vertexPos[1] - vertexPos[0];
			t1 = vertexPos[2] - vertexPos[0];
			//���K��
			D3DXVec3Normalize(&t0, &t0);
			D3DXVec3Normalize(&t1, &t1);

			//�@�����v�Z
			D3DXVec3Cross(&polygonInfo.Normal_, &t0, &t1);
			
			//���X�g�ɓo�^
			polygonInfoList.at(polygonInfo.VertexNo_[0]).push_back(polygonInfo);
			polygonInfoList.at(polygonInfo.VertexNo_[1]).push_back(polygonInfo);
			polygonInfoList.at(polygonInfo.VertexNo_[2]).push_back(polygonInfo);
		
		}

		//���_�@�������߂�
		for (int vertexNo = 0; vertexNo < (int)vertexBuffer.size(); vertexNo++)
		{
			//���X�g���擾
			list<PolygonInfoS>& polygonInfo = polygonInfoList.at(vertexNo);

			//�@��
			D3DXVECTOR3 normal = D3DXVECTOR3(0, 0, 0);

			//���v
			for (const auto& it : polygonInfo)
			{
				normal += it.Normal_;
			}
			
			//���ϒl���v�Z
			normal /= s_cast<float>(polygonInfo.size());
		
			float* pNormal = vertexBuffer.at(vertexNo).Normal_;
			pNormal[0] = normal.x;
			pNormal[1] = normal.y;
			pNormal[2] = normal.z;
			pNormal[3] = 1.0f;
		}
	}

	/**
	 * ���_�o�b�t�@�̖@�����쐬.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 *
	 * @tparam TVertex ���_�o�b�t�@.
	 * @tparam TIndex  �C���f�b�N�X�o�b�t�@.
	 * @param [in,out] vertexBuffer  ���_�o�b�t�@�̐擪�A�h���X.
	 * @param 		   numVertex	 ���_��.
	 * @param [in,out] indexBuffer   �C���f�b�N�X�o�b�t�@�̐擪�A�h���X.
	 * @param 		   numIndex		 �C���f�b�N�X��.
	 * @param 		   primiteveType �v���~�e�B�u�^�C�v.
	 */
	template<class TVertex, class TIndex>
	void CreateVertexNormalArray(
		TVertex* vertexBuffer, int numVertex,
		TIndex* indexBuffer, int numIndex,
		Primitive::TypeE primiteveType)
	{
		//�ʖ@�������߂�

		int numFace = numIndex / 3;

		//�|���S�����
		unique_ptr<PolygonInfoS[]> polygonInfoPtr;
		//�|���S�����z��
		vector<list<PolygonInfoS>> polygonInfoList;

		polygonInfoList.resize(numVertex);

		for (int i = 0; i < numFace; i++)
		{
			//���W
			D3DXVECTOR3 pos[3];
			int t = i * 3;

			//�|���S�����
			PolygonInfoS polygonInfo;

			//���_�ԍ����R�s�[
			polygonInfo.VertexNo_[0] = indexBuffer[t];
			polygonInfo.VertexNo_[1] = indexBuffer[t + 1];
			polygonInfo.VertexNo_[2] = indexBuffer[t + 2];

			if (polygonInfo.VertexNo_[0] == polygonInfo.VertexNo_[1] ||
				polygonInfo.VertexNo_[0] == polygonInfo.VertexNo_[2] ||
				polygonInfo.VertexNo_[1] == polygonInfo.VertexNo_[2])
			{
				//�k�ރ|���S��
				//���_����v���Ă��ĕ`�悵�Ȃ��|���S���H�������ԁH
				continue;
			}

			//�@��
			D3DXVECTOR3 normal = D3DXVECTOR3(0, 0, 0);
			//���_���W
			D3DXVECTOR3 vertexPos[3];

			for (int i = 0; i < 3; i++)
			{
				//���_�o�b�t�@���R�s�[
				const TVertex& vertex = vertexBuffer[polygonInfo.VertexNo_[i]];
				//���_���W���R�s�[
				vertexPos[i] = D3DXVECTOR3(vertex.pos[0], vertex.pos[1], vertex.pos[2])
			}

			D3DXVECTOR3 t0, t1;
			t0 = vertexPos[1] - vertexPos[0];
			t1 = vertexPos[2] - vertexPos[0];
			//���K��
			D3DXVec3Normalize(&t0, &t0);
			D3DXVec3Normalize(&t1, &t1);

			//�@�����v�Z
			D3DXVec3Cross(&polygonInfo.Normal_, &t0, &t1);

			//���X�g�ɓo�^
			polygonInfoList.at(polygonInfo.VertexNo_[0]).push_back(polygonInfo);
			polygonInfoList.at(polygonInfo.VertexNo_[1]).push_back(polygonInfo);
			polygonInfoList.at(polygonInfo.VertexNo_[2]).push_back(polygonInfo);

		}

		//���_�@�������߂�
		for (int vertexNo = 0; vertexNo < numVertex; vertexNo++)
		{
			//���X�g���擾
			list<PolygonInfoS>& polygonInfo = polygonInfoList.at(vertexNo);

			//�@��
			D3DXVECTOR3 normal = D3DXVECTOR3(0, 0, 0);

			//���v
			for (const auto& it : polygonInfo)
			{
				normal += it.Normal_;
			}

			//���ϒl���v�Z
			normal /= s_cast<float>(polygonInfo.size());

			float* pNormal = vertexBuffer[vertexNo].Normal_;
			pNormal[0] = normal.x;
			pNormal[1] = normal.y;
			pNormal[2] = normal.z;
			pNormal[3] = 1.0f;
		}
	}

	/**
	 * ���_�}�[�W.
	 * ���_����������
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/19
	 *
	 * @tparam TVertex ���_�o�b�t�@.
	 * @tparam TIndex  �C���f�b�N�X�o�b�t�@.
	 * @param [in,out] vertexBuffer		 �}�[�W�Ώۂ̒��_�o�b�t�@.
	 * @param [in,out] indexBuffer		 �}�[�W�Ώۂ̃C���f�b�N�X�o�b�t�@.
	 * @param 		   margeLenThreshold �}�[�W���钸�_���m�̋�����臒l�B���̒l�ȉ��̒��_�̓}�[�W����܂�.
	 */
	template<class TVertex, class TIndex>
	void MergeVertex(vector<TVertex>& vertexBuffer, vector<TIndex>& indexBuffer, float margeLenThreshold)
	{
		float margeLenThresholdSq = margeLenThreshold * margeLenThreshold;

		//�}�[�W���B�폜���钸�_�ԍ��ƁA�u�������钸�_�ԍ��̃y�A���B
		typedef pair<int, int>	MergeInfoT;
		//�폜���钸�_�ԍ��̃��X�g�B
		list<MergeInfoT> mergeInfoList;

		//���_�폜�̃t���O�̃��X�g�B
		typename vector<bool> isDeleteVertexs;	
		//���g��菬�����ԍ��̒��_�������폜���ꂽ���̃J�E���g����
		typename vector<int>  deleteCount;			
		
		//������
		isDeleteVertexs.resize(vertexBuffer.size());
		deleteCount.resize(vertexBuffer.size());
		for (auto& it : isDeleteVertexs) 
		{
			it = false;
		}
		for (auto& it : deleteCount) 
		{
			it = 0;
		}

		for (int vertexNo = 0; vertexNo != vertexBuffer.size(); vertexNo++) 
		{
			if (isDeleteVertexs[vertexNo]) 
			{
				//�폜�\��̒��_�Ȃ̂Œ��ׂ�K�v�Ȃ��B
				continue;
			}

			//���_�擾
			const TVertex& v0 = vertexBuffer[vertexNo];

			//���W
			D3DXVECTOR3 pos;
			//����
			D3DXVECTOR3 len;

			//���W��ݒ�
			pos = D3DXVECTOR3(v0.pos[0], v0.pos[1], v0.pos[2]);

			for (int delvertexNo = 0; delvertexNo < (int)vertexBuffer.size(); delvertexNo++)
			{
				//�d�Ȃ��ĂȂ��������ĂȂ��݂����ȁH
				if (vertexNo != delvertexNo && !isDeleteVertexs[delvertexNo]) 
				{
					//���_���m�̋����𒲂ׂ�
					const TVertex& v1 = vertexBuffer[delvertexNo];

					//������ݒ�
					len = D3DXVECTOR3(v1.pos[0], v1.pos[1], v1.pos[2]);

					len = pos - len;

					//�����̓����擾
					float lenSq = D3DXVec3LengthSq(&len);

					if (lenSq < margeLenThresholdSq) 
					{
						//��������������

						//�폜����������B
						isDeleteVertexs[delvertexNo] = true;	
									
						//�}�[�W�����쐬����B
						MergeInfoT mergeInfo;
						mergeInfo.first = delvertexNo;
						mergeInfo.second = vertexNo;
						//�ǉ�
						mergeInfoList.push_back(mergeInfo);
					}
				}
			}
		}

		for (auto& mergeInfoIt : mergeInfoList)
		{
			for (TIndex index = mergeInfoIt.first + 1; index < (int)deleteCount.size(); index++) 
			{
				deleteCount[index]++;
			}
		}

		//���_�o�b�t�@���擾
		vector<TVertex> vertexBufferTmp = vertexBuffer;
		//����
		vertexBuffer.clear();

		for (int i = 0; i < (int)vertexBufferTmp.size(); i++) 
		{
			if (!isDeleteVertexs[i]) 
			{
				//�����Ȃ����_��ݒ�
				vertexBuffer.push_back(vertexBufferTmp[i]);
			}
		}

		//���_���폜�����̂ŃC���f�b�N�X�o�b�t�@�𒲐��B
		{
			for (auto& mergeInfoIt : mergeInfoList) {
				//�C���f�b�N�X�o�b�t�@����폜�Ώۂ̒��_��T���A�폜�Ώۂ̒��_���ԍ����傫�����̂͌��Z����.
				for (auto& indexIt : indexBuffer) 
				{
					if (mergeInfoIt.first == indexIt) 
					{
						//�폜�Ώ�.
						indexIt = mergeInfoIt.second;
					}
				}
			}
		}

		for (auto& indexIt : indexBuffer) 
		{
			indexIt -= deleteCount[indexIt];
		}
	}

}