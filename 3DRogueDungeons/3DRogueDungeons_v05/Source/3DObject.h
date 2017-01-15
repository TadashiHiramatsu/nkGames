#pragma once
#include"3DData.h"

class C3DObject :public C3DData
{
public:
	void Initialize(LPCTSTR XName){ XfileName = XName; C3DData::Initialize(); }
};