#include "stdafx.h"
using namespace std;

using std::placeholders::_1;
using std::placeholders::_2;
Stugrade::Stugrade()
{
}
Stugrade::~Stugrade()
{
}
 bool Stugrade::cmp(const int &ax,const int &bx)
 {
	 map<string,string> &a=datas[ax];
	 map<string,string> &b=datas[bx];
if(keytype[cmpkey]=="成绩")
	//	return orcmp^((a.find(cmpkey)->second)<(b.find(cmpkey)->second));
	return orcmp ? atof(a.find(cmpkey)->second.c_str())<atof(b.find(cmpkey)->second.c_str()) :atof(a.find(cmpkey)->second.c_str())>atof(b.find(cmpkey)->second.c_str());
	else //if(keytype[cmpkey]=="字符")
		return orcmp ? (a.find(cmpkey)->second)>(b.find(cmpkey)->second):(a.find(cmpkey)->second)<(b.find(cmpkey)->second);
//	return false;
}
int Stugrade::sortviakey(int x)
{
	auto bound_cmp=bind(&Stugrade::cmp,this,_1,_2);

	if(cmpkey==keyord[x])orcmp=!orcmp;
	else cmpkey=keyord[x];
	stable_sort(displayord.begin(),displayord.end(),bound_cmp);
	return 0;
}
int Stugrade::deldata(set<int>x)
{
	set<int>deldis;
	int delcounts=0;
	std::vector<map<string,string> >::iterator it=datas.begin();
	for(int a=0; it!=datas.end(); ++a)
	{
		
		
		if(x.count(a))
		{
			delcounts++;
			deldis.insert(atoi(it->find("显示标号")->second.c_str()));
			it->find("显示标号")->second="-1";
			it=datas.erase(it);

		}
		else
		{
			int sx=atoi(it->find("显示标号")->second.c_str());
			displayord[sx]-=delcounts;
			it->find("显示标号")->second=to_string(displayord[sx]);
			++it;
		}
	}
	deldisplay(deldis);
	return 0;
}
int Stugrade::printdata(vector<map<string,string> > x)
{
	for(int a=1-1; a<=x.size()-1; ++a)
	{
		for(int b=1-1; b<=keyord.size()-1; ++b)
		{
			cout<<x[a][keyord[b]]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
int Stugrade::readdata()
{
	orcmp=true;
	fstream file;
	file.open("d:\\qq295\\Desktop\\file.txt",ios::in|ios::out);//数据保存的文件 
	if(!file.good())cout<<"文件打开失败";
	string sline;

	string skey;
	stringstream ss;
	
	getline(file,sline);
	ss=stringstream(sline);
	while(ss>>skey)keyord.push_back(skey);//输入所有的key 
	getline(file,sline);
	ss=stringstream(sline);
	for(int a=0; a<=keyord.size()-1; ++a)
	{
		string typ; ss>>typ; keytype[keyord[a]]=typ;
	}
	while(getline(file,sline))
	{
		map<string,string>m;
		ss=stringstream(sline);
		for(int b=1-1; b<=keyord.size()-1; ++b)
		{
			ss>>skey; m[keyord[b]]=skey;//循环读入每条数据的每一个key对应的value 
		}
		datas.push_back(m);
	}
	file.close();
	return 0;
}
int Stugrade::savedata()
{
	fstream file;
	file.open("d:\\qq295\\Desktop\\fileout.txt",ios::trunc|ios::out);
	
	for(int a=0; a<=keyord.size()-1; ++a)file<<keyord[a]<<" "; file<<endl;
	for(int a=0; a<=keyord.size()-1; ++a)file<<keytype[keyord[a]]<<" "; file<<endl;
	for(int a=0; a<=datas.size()-1; ++a)
	{
		for(int b=0; b<=keyord.size()-1; ++b)
		{
			file<<datas[a][keyord[b]]<<" ";
		}file<<endl;
	}
	file.close();
	return 1;
}

int Stugrade::displayallitem()
{
	displayord.clear();
	for(int a=0; a<=datas.size()-1; ++a)
	{
		displayord.push_back(a);
		datas[a]["显示标号"]=to_string(a);

	}
	return 0;
}

int Stugrade::deldisplay(set<int> x)
{
	
	std::vector<int>::iterator it=displayord.begin();
	for(int a=0; it!=displayord.end(); ++a)
	{
	
		if(x.count(a))
		{
			
			it=displayord.erase(it);
		} else
			++it;
	}
	return 0;
}
