#pragma once
#include "2DImage.h"
#include"IncludeManagers.h"
#include"SceneManager.h"

#define MAX_COMMAND_NUM 2	//COMMAND��MAX��
enum COMMAND_SELECT { START = 0, EXIT }; //enum�ŗ񋓌^COMMAND_SELECT���쐬


class CTitleCursor : public C2DImage
{
public:
	CTitleCursor();
	~CTitleCursor();
	void Initialize()override;
	void Update()override;
private:
	int m_selectIndex;
};

