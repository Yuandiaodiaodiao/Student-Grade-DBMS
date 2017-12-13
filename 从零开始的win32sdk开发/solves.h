#pragma once
#include "stdafx.h"
using namespace std;
class solves{
public:
	solves();
	~solves();
};
HWND createlistview(HWND hDlg);
int reflashline(HWND hDlg);
int dellistview(HWND hDlg);
int reflashdata(HWND hDlg);
int GetIndex(HWND hList);
std::wstring StringToWString(const std::string& str);
