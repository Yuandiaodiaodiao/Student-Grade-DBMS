#pragma once
#include "stdafx.h"
#include <vector>
#include<map>
#include<set>
using namespace std;

class Stugrade{
public:
	Stugrade();
	~Stugrade();
	vector<string> keyord;
	map<string,string>keytype;
	vector<int>displayord;
	vector<map<string,string> >datas;
	int printdata(vector<map<string,string> >x);
	//	void savedata();
	//	vector<map<string,string> > findvalue(string keystring,string valuestring);
	int readdata(HWND hDlg);
	int deldata(set <int> x);
	 bool orcmp;
	 string cmpkey;
	 bool cmp(const int &ax,const int &bx);
	int sortviakey(int x);
	int savedata();
	int displayallitem();
	int deldisplay(set<int>x);
	string filestring;
	int readfile();
	int writefile(HWND hDlg);
	int savefile(HWND hDlg);
};



