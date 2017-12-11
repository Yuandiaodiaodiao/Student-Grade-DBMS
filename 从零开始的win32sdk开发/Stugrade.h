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
	int readdata();
	int deldata(set <int> x);
	 bool orcmp;
	 string cmpkey;
	 bool cmp(const int &ax,const int &bx);
	int sortviakey(int x);
	int savedata();
	int displayallitem();
	int deldisplay(set<int>x);
};



