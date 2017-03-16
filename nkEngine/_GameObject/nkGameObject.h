/**
 * @file _GameObject\nkGameObject.h
 *
 * �Q�[���I�u�W�F�N�g�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/** �D��x. */
	typedef unsigned char GOPriorityT;

	/**
	 * �Q�[���I�u�W�F�N�g�}�l�[�W���ɓo�^������N���X.
	 * �Q�[���J���ł͊�{���̃N���X���p��������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class IGameObject : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		IGameObject()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual ~IGameObject()
		{
		}

	public:

		/**
		 * �R���X�g���N�^�̌�ɌĂ΂�鏉����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Awake() 
		{
		}

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Start() 
		{
		}

		/**
		 * Update�̑O�ɌĂ΂��X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PreUpdate()
		{
		}

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Update() 
		{
		}

		/**
		 * Update�̌�ɌĂ΂��X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PostUpdate() 
		{
		}

		/**
		 * Render�̑O�ɌĂ΂��`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PreRender() 
		{
		}

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Render() 
		{
		}

		/**
		 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PostRender() 
		{
		}

		/**
		 * �f�X�g���N�^�̑O�ɌĂ΂����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void Release() 
		{
		}

	public:

		/**
		 * �R���X�g���N�^�̌�ɌĂ΂�鏉����.
		 * ���b�p�[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void AwakeWrapper()
		{
			if (!isStart_ && isActive_)
			{
				Awake();
			}
		}

		/**
		 * ������.
		 * ���b�p�[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void StartWrapper()
		{
			if (!isStart_ && isActive_)
			{
				Start();
				isStart_ = true;
			}
		}

		/**
		 * Update�̑O�ɌĂ΂��X�V.
		 * ���b�p�[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PreUpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				PreUpdate();
			}
		}

		/**
		 * �X�V.
		 * ���b�p�[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void UpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				Update();
			}
		}

		/**
		 * Update�̌�ɌĂ΂��X�V.
		 * ���b�p�[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PostUpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				PostUpdate();
			}
		}

		/**
		 * Render�̑O�ɌĂ΂��`��.
		 * ���b�p�[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PreRenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				PreRender();
			}
		}

		/**
		 * �`��.
		 * ���b�p�[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void RenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				Render();
			}
		}

		/**
		 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
		 * ���b�p�[.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		virtual void PostRenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				PostRender();
			}
		}

	public:

		/**
		 * �Q�[���I�u�W�F�N�g��isActive���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool GetActive() const
		{
			return isActive_;
		}

		/**
		 * �Q�[���I�u�W�F�N�g���A�N�e�B�u / ��A�N�e�B�u�ɂ��܂�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param value True to value.
		 */
		void SetActive(bool value)
		{
			isActive_ = value;
		}

		/**
		 * �D��x���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The priority.
		 */
		GOPriorityT GetPriority() const
		{
			return Priority_;
		}

	public:

		/** �g�����X�t�H�[��. */
		Transform Transform_;
		/** �D��x. */
		GOPriorityT Priority_;
		/** �A�N�e�B�u�t���O. */
		bool isActive_ = true;
		/** Start���Ă΂�Ă��邩�t���O. */
		bool isStart_ = false;

	};

}// namespace nkEngine