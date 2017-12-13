#pragma once
#include"stdafx.h"
#include"Stugrade.h"
#include<string>
using namespace std;
class Statistics
{
public:
	Statistics();
	~Statistics();
	static HWND drop1;
	static HWND drop2;
	static HWND texts;
	static string stringkey[3];
	static double maxcmp();
	static double mincmp();
	static double averagecmp();
	static double cmp(int status);
	static string cmpstring;
	static Stugrade * datasx;
	static INT_PTR CALLBACK    DlgStatistics(HWND, UINT, WPARAM, LPARAM);
};

