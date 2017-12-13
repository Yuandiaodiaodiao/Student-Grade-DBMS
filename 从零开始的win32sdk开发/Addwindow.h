#pragma once
#include"stdafx.h"
#include<map>
#include<string>
#include"Stugrade.h"
using namespace std;
class Addwindow
{
public:
	Addwindow();
	~Addwindow();
	static HWND buttonnext;
	static HWND listbox;
	static HWND texts;
	static Stugrade * datasx;
	static HWND edits;
	static int addpos;
	static map<string,string> mapbuff;
	static INT_PTR CALLBACK    Dlgadd(HWND,UINT,WPARAM,LPARAM);
};
