/**
 * @file _Graphics\_ModelRender\nkSkinModelData.h
 *
 * �X�L�����f���f�[�^�N���X�̒�`.
 */
#pragma once

#include"..\_Buffer\nkVertexBuffer.h"
#include"../nkTexture.h"

namespace nkEngine
{

	/**
	 * A 3D xframe derived.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct D3DXFRAME_DERIVED : public D3DXFRAME 
	{
	public:

		/** �����ςݍs��. */
		D3DXMATRIXA16 CombinedTransformationMatrix_;

	};

	/**
	 * A 3D xmeshcontainer derived.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
	{
	public:

		/** D3D�e�N�X�`��. */
		LPDIRECT3DTEXTURE9* D3DTexture_;
		/** �e�N�X�`��. */
		Texture* Texture_;
		/** �I���W�i�����b�V��. */
		LPD3DXMESH OrigMesh_;
		/** �����e�[�u��. */
		LPD3DXATTRIBUTERANGE AttributeTable_;
		/** �����e�[�u���O���[�v. */
		DWORD NumAttributeGroup_;
		/** �C���t���[�V�����H. */
		DWORD NumInfl_;
		/** �O��̃{�[���R���r�l�[�V����. */
		LPD3DXBUFFER BoneCombinationBuf_;
		/** �{�[���s��|�C���^. */
		D3DXMATRIX** BoneMatrixPtrs_;
		/** �{�[���I�t�Z�b�g�s��. */
		D3DXMATRIX* BoneOffsetMatrix_;
		/** Number of palette entries. */
		DWORD NumPaletteEntries;
		/** True to use software vp. */
		bool UseSoftwareVP;
		/** Zero-based index of the attribute software. */
		DWORD iAttributeSW;

	};

	class Animation;

	/**
	 * �X�L�����f���f�[�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class SkinModelData : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		SkinModelData();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~SkinModelData();

		/**
		 * ���f���f�[�^�����[�h.
		 * �A�j���[�V�����t�����f���̏ꍇ�A�j���[�V�����N���X���\�z.
		 * �A�j���[�V�����Ȃ��̏ꍇnull��OK.
		 * "Asset/Model/" �t�@�C������X�t�@�C�����f�������[�h
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param 		   filepath �t�@�C���p�X�A"Asset/Model/"���Ȃ����t�@�C���p�X.
		 * @param [in,out] anim	    �A�j���[�V�����N���X�|�C���^�Anull.
		 */
		void LoadModelData(const char* filepath, Animation* anim);

		/**
		 * �C���X�^���V���O�`����s�����߂̃f�[�^���쐬����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param 		   numInstance   �C���X�^���X�̐�.
		 * @param [in,out] vertexElement �C���X�^���V���O�`��p�̒��_�X�g���[���P�ɗ������ޒ��_�o�b�t�@�̒��_���C�A�E�g.
		 */
		void CreateInstancingRenderData(int numInstance, D3DVERTEXELEMENT9* vertexElement);

		/**
		 * ���f���f�[�^�̃N���[�����쐬.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param 		   modelData ���f���f�[�^.
		 * @param [in,out] anim		 �A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�A�j���[�V�����N���X���\�z����܂�.
		 */
		void CloneModelData(const SkinModelData& modelData, Animation* anim);

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Release();

		/**
		 * �X�P���g���폜.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param frame The frame.
		 */
		void DeleteSkeleton(LPD3DXFRAME frame);

		/**
		 * �t���[�����[�g�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the frame root.
		 */
		D3DXFRAME* GetFrameRoot()
		{
			return FrameRoot_;
		}

		/**
		 * �I���W�i�����b�V�����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param frame The frame.
		 *
		 * @return The organisation mesh.
		 */
		LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame) const;

		/**
		 * �擪�̃��b�V�����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The organisation mesh first.
		 */
		LPD3DXMESH GetOrgMeshFirst() const;

		/**
		 * �e�X�g �Ӗ��s.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] frame  �t���[��.
		 * @param [in,out] aniCon �A�j���[�V�����R���g���[��.
		 */
		void SetupOutputAnimationRegist(D3DXFRAME* frame, ID3DXAnimationController* aniCon);

		/**
		 * �{�[���s����X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param matWorld ���[���h�s��.
		 */
		void UpdateBoneMatrix(const Matrix& matWorld);

		/**
		 * �e�t���[���̍s����X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param frameBase    The frame base.
		 * @param parentMatrix The parent matrix.
		 */
		void UpdateFrameMatrices(LPD3DXFRAME frameBase, const D3DXMATRIX* parentMatrix);

		/**
		 * �C���X�^���V���O�`��p�̃f�[�^���X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param data ���_�o�b�t�@�ɃR�s�[����f�[�^.
		 */
		void UpdateInstancingRenderData(const void* data)
		{
			InstanceVertexBuffer_.Update(data);
		}

		/**
		 * �C���X�^���V���O�`��p�̂Ƃ��Ɏg�p���钸�_��`���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the vertex declaration for instancing render.
		 */
		IDirect3DVertexDeclaration9* GetVertexDeclForInstancingRender() const
		{
			return VertexDeclForInstancingRender_;
		}

		/**
		 * �C���X�^���V���O�`��p�̒��_�o�b�t�@���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return �X�g���[���P�ɗ������_�o�b�t�@.
		 */
		const VertexBuffer& GetInstancingVertexBuffer() const
		{
			return(const_cast<SkinModelData&>(*this)).GetInstancingVertexBuffer();
		}

		/**
		 * �C���X�^���V���O�`��p�̒��_�o�b�t�@���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return ���_�o�b�t�@.
		 */
		VertexBuffer& GetInstancingVertexBuffer()
		{
			return InstanceVertexBuffer_;
		}

		/**
		 * �C���X�^���X�̐����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The number instance.
		 */
		int GetNumInstance() const
		{
			return numInstance_;
		}

		/**
		 * ���_�o�b�t�@�̃X�g���C�h���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The vertex buffer stride.
		 */
		int GetVertexBufferStride() const
		{
			return VertexBufferStride_;
		}

		/**
		* �擪�̃{�[���s����擾.
		*
		* @return �擪�̃{�[���s��.
		*/
		Matrix* GetRootBoneWorldMatrix()
		{
			D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)FrameRoot_;
			return (Matrix*)&frameDer->CombinedTransformationMatrix_;
		}

	private:

		/**
		 * �X�P���g���̃N���[�����쐬.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] dstFrame �N���[����̃X�P���g���̊i�[��.
		 * @param [in,out] srcFrame �N���[�����̃X�P���g��.
		 */
		void CloneSkeleton(LPD3DXFRAME& dstFrame, D3DXFRAME* srcFrame);

		/**
		 * �X�P���g���̃N���[�����폜.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] frame �폜����X�P���g��.
		 */
		void DeleteCloneSkeleton(D3DXFRAME* frame);

		/**
		 * �C���X�^���V���O�`��p�̃f�[�^���쐬.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] frame		 �t���[��.
		 * @param 		   numInstance   �C���X�^���X�̐�.
		 * @param [in,out] vertexElement �C���X�^���V���O�`��p�̒��_�X�g���[��1�ɗ������ޒ��_�o�b�t�@�̒��_���C�A�E�g.
		 *
		 * @return true���A���Ă�����ċA�����I��.
		 */
		bool CreateInstancingRenderData(D3DXFRAME* frame, int numInstance, D3DVERTEXELEMENT9* vertexElement);

		/**
		 * ��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] frame	  If non-null, the frame.
		 * @param [in,out] rootFrame If non-null, the root frame.
		 *
		 * @return A hResult.
		 */
		HRESULT SetupBoneMatrixPointers(D3DXFRAME* frame, D3DXFRAME* rootFrame);

	private:

		/** �t���[�����[�g. */
		D3DXFRAME* FrameRoot_;
		/** �A�j���[�V�����R���g���[��. */
		ID3DXAnimationController* D3DAnimController_;
		/** �N���[���t���O. */
		bool isClone_;
		/** �C���X�^���V���O�`��p�̒��_�o�b�t�@�̃��X�g. */
		VertexBuffer InstanceVertexBuffer_;
		/** �C���X�^���V���O�`��p�̒��_��`. */
		IDirect3DVertexDeclaration9* VertexDeclForInstancingRender_;
		/** �C���X�^���X�̐�. */
		int numInstance_;
		/** ���_�X�g���C�h. */
		int VertexBufferStride_;

	};
}