#pragma once
#include "CBRInstance.h"
class CBRDiskManager
{
public:
	CBRDiskManager();
	~CBRDiskManager();
	void SaveCaseBase(std::string loc, CBRInstance * cbr);
	void LoadCaseBase(std::string loc, CBRInstance * cbr);
};

