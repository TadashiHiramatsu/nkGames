#pragma once

namespace nkEngine
{
	typedef unsigned char GOPriority; //unsigned char

	//�Q�[���I�u�W�F�N�g�}�l�[�W���ɓo�^������N���X
	class IGameObject
	{
	public:

		//�R���X�g���N�^
		IGameObject();
		//�f�X�g���N�^
		virtual ~IGameObject();

	public:
		//�����o�֐�

		//�R���X�g���N�^�̌�ɌĂ΂�鏉����
		virtual void Awake() {}
		//������
		virtual void Start() {}
		//Update�̑O�ɌĂ΂��X�V
		virtual void PreUpdate() {}
		//�X�V
		virtual void Update() {}
		//Update�̌�ɌĂ΂��X�V
		virtual void PostUpdate() {}
		//Render�̑O�ɌĂ΂��`��
		virtual void PreRender() {}
		//�`��
		virtual void Render() {}
		//�|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��
		virtual void PostRender() {}
		//�f�X�g���N�^�̑O�ɌĂ΂����
		virtual void Release() {}

	public:
		//���b�p�[
		//�p����̃N���X��if�����팸�ł���

		//�R���X�g���N�^�̌�ɌĂ΂�鏉����
		virtual void AwakeWrapper()
		{
			if (isStart && isActive)
			{
				Awake();
			}
		}

		//������
		virtual void StartWrapper()
		{
			if (!isStart && isActive)
			{
				Start();
				isStart = true;
			}
		}

		//Update�̑O�ɌĂ΂��X�V
		virtual void PreUpdateWrapper()
		{
			if (isStart && isActive)
			{
				PreUpdate();
			}
		}

		//�X�V
		virtual void UpdateWrapper()
		{
			if (isStart && isActive)
			{
				Update();
			}
		}

		//Update�̌�ɌĂ΂��X�V
		virtual void PostUpdateWrapper()
		{
			if (isStart && isActive)
			{
				PostUpdate();
			}
		}

		//Render�̑O�ɌĂ΂��`��
		virtual void PreRenderWrapper()
		{
			if (isStart && isActive)
			{
				PreRender();
			}
		}

		//�`��
		virtual void RenderWrapper()
		{
			if (isStart && isActive)
			{
				Render();
			}
		}

		//�|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��
		virtual void PostRenderWrapper()
		{
			if (isStart && isActive)
			{
				PostRender();
			}
		}

	public:
		//�Q�b�^�A�Z�b�^

		//�Q�[���I�u�W�F�N�g��isActive���擾
		bool GetActive() const
		{
			return isActive;
		}
		//�Q�[���I�u�W�F�N�g���A�N�e�B�u / ��A�N�e�B�u�ɂ��܂�
		void SetActive(bool _value)
		{
			isActive = _value;
		}

		//�D��x���擾
		GOPriority GetPriority() const
		{
			return priority;
		}

	public:
		//�����o�ϐ�(�O�����猩����)
		
		//�R���|�[�l���g
		Transform transform; //�g�����X�t�H�[��

		GOPriority priority; //�D��x
		bool isActive; //�A�N�e�B�u�t���O
		bool isStart; //Start���Ă΂�Ă��邩�t���O
	};
}