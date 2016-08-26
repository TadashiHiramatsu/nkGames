//シーンの基底クラス
#ifndef _NKSCENE_
#define _NKSCENE_

namespace nkEngine
{
	/*
		シーンの基底クラス
		このクラスを継承する
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