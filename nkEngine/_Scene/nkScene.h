//�V�[���̊��N���X
#ifndef _NKSCENE_
#define _NKSCENE_

namespace nkEngine
{
	/*
		�V�[���̊��N���X
		���̃N���X���p������
	*/
	class CScene
	{
	public:
		CScene(){}
		virtual ~CScene(){}
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;
	};
}

#endif // !_NKSCENE_