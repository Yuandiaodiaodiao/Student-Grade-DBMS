#pragma once
#include "stdafx.h"
#include<vector>
#include<string>
using namespace std;
class filter
{
public:
	filter();
	~filter();
	//vector<string>filterstring;
	 set<int> return_del_item(string keystring,int flitem,string flstring);
	//bool(filter::*f[6])(string,string);
	 bool cmp0(string x,string cmp);//小于
	 bool cmp1(string x,string cmp);//小于等于
	 bool cmp2(string x,string cmp);//大于
 bool cmp3(string x,string cmp);//大于等于
	 bool cmp4(string x,string cmp);//等于
	 bool cmp5(string x,string cmp);//不等于
	 bool ifstring(string x);
	 bool(filter::*f[6])(string,string)={&filter::cmp0,&filter::cmp1,&filter::cmp2,&filter::cmp3,&filter::cmp4,&filter::cmp5};
	//bool(*f)(string,string);
string cmpstring[6]={"小于","小于等于","大于","大于等于","等于","不等于"};
};
