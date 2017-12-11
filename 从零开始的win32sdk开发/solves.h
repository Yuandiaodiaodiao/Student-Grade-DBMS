#pragma once
#include<iostream>
#include<fstream>
#include<cstdio>
#include<map>
#include<vector>
#include<string>
#include<stdlib.h>
#include<sstream>
#include<set>
using namespace std;
class solves{
public:
	solves();
	~solves();
};
HWND createlistview(HWND hDlg);
int reflashline(HWND hDlg);

int reflashdata(HWND hDlg);
int GetIndex(HWND hList);
std::wstring StringToWString(const std::string& str);
