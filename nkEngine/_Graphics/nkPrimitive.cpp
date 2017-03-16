/**
 * @file _Graphics\nkPrimitive.cpp
 *
 * �v���~�e�B�u�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkPrimitive.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
    Primitive::Primitive() :
		numVertex_(0),
		numIndex_(0),
		VertexStride_(0),
		Type_(TypeE::TriangleList),
		D3DPrimitiveType_(D3DPT_TRIANGLELIST)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Primitive::~Primitive()
	{
		Release();
	}

	/**
	 * �쐬.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/07
	 *
	 * @param 		   primitiveType   �v���~�e�B�u�^�C�v.
	 * @param 		   numVertex	   ���_��.
	 * @param 		   vertexStride    ���_�X�g���C�h.
	 * @param 		   vertexLayout    ���_���C�A�E�g.
	 * @param [in,out] srcVertexBuffer �\�[�X���_�o�b�t�@.
	 * @param 		   numIndex		   �C���f�b�N�X�̐�.
	 * @param 		   indexFormat	   �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g.
	 * @param [in,out] srcIndexbuffer  �\�[�X�C���f�b�N�X�o�b�t�@.
	 */
	void Primitive::Create(
		TypeE 						primitiveType,
		int 						numVertex,
		int 						vertexStride,
		const D3DVERTEXELEMENT9*	vertexLayout,
		void*						srcVertexBuffer,
		int 						numIndex,
		IndexFormatE				indexFormat,
		void*						srcIndexbuffer
	)
	{

		NK_ASSERT(primitiveType < TypeE::TypeNum, "primitiveType is invalid");
		NK_ASSERT(numVertex != 0, "numVertex is zero");
		NK_ASSERT(vertexStride != 0, "vertexStrid is zero");
		NK_ASSERT(numIndex != 0, "numIndex is zero");

		//�^�C�v���R�s�[
		Type_ = primitiveType;
		//���_�����R�s�[
		numVertex_ = numVertex;
		//���_�X�g���C�h���R�s�[
		VertexStride_ = vertexStride;
		//�C���f�b�N�X�̐����R�s�[
		numIndex_ = numIndex;

		//���
		Release();
		
		//���_�o�b�t�@���쐬
		VertexBuffer_.Create(numVertex_, VertexStride_, vertexLayout, srcVertexBuffer);

		//�C���f�b�N�X�o�b�t�@���쐬
		IndexBuffer_.Create(numIndex_, indexFormat, srcIndexbuffer);

		if (Type_ == TypeE::TriangleList)
		{
			numPolygon_ = numIndex / 3;
			D3DPrimitiveType_ = D3DPT_TRIANGLELIST;
		}
		else if (Type_ == TypeE::TriangleStrip)
		{
			numPolygon_ = numIndex - 2;
			D3DPrimitiveType_ = D3DPT_TRIANGLESTRIP;
		}

	}

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Primitive::Release()
	{
		VertexBuffer_.Release();
		IndexBuffer_.Release();
	}

}// namespace nkEngine