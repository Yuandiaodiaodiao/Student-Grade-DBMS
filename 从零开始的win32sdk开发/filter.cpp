#include "stdafx.h"
using namespace std;
filter::filter()
{}
filter::~filter()
{}
set<int> filter::return_del_item(string keystring,int flitem,string flstring)
{
	set<int>delsets;
	for(int a=0; a<=((int)databases.displayord.size())-1; ++a)
	{
		//(this->**f)(flstring,flstring);
		if(!((this->**(f+flitem))(databases.datas[databases.displayord[a]][keystring],flstring)))
		{
			delsets.insert(a);
		}
	}
	return delsets;
}
bool filter::cmp0(string x,string cmp)
{
	if(ifstring(x))return x<cmp;
	else return atoi(x.c_str())<atoi(cmp.c_str());
}
bool filter::cmp1(string x,string cmp)
{
	if(ifstring(x))return x<=cmp;
	else return atoi(x.c_str())<=atoi(cmp.c_str());
}
bool filter::cmp2(string x,string cmp)
{
	if(ifstring(x))return x>cmp;
	else return atoi(x.c_str())>atoi(cmp.c_str());
}
bool filter::cmp3(string x,string cmp)
{
	if(ifstring(x))return x>=cmp;
	else return atoi(x.c_str())>=atoi(cmp.c_str());
}
bool filter::cmp4(string x,string cmp)
{
	if(x==cmp)return true;
	else return false;
}
bool filter::cmp5(string x,string cmp)
{
	if(x!=cmp)return true;
	else return false;
}
bool filter::ifstring(string x)
{
	int xc=atoi(x.c_str());
	if(xc!=0||to_string(xc)==x)return false;
	else return true;
}
