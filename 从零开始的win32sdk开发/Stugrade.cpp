#include "stdafx.h"
using namespace std;
#include<cstring>
using std::placeholders::_1;
using std::placeholders::_2;
Stugrade::Stugrade()
{
	filestring=".\\file.txt";
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
	for(int a=1-1; a<=(int)x.size()-1; ++a)
	{
		for(int b=1-1; b<=(int)keyord.size()-1; ++b)
		{
			cout<<x[a][keyord[b]]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
int Stugrade::readdata(HWND hDlg)
{
	keyord.clear();
	keytype.clear();
	datas.clear();
	orcmp=true;
	fstream file;
	file.open(filestring,ios::in|ios::out);//数据保存的文件 
	//file.open("\\file.txt",ios::in|ios::out);//数据保存的文件 
	if(!file.good())
	{
		MessageBox(hDlg,"文件打开失败","警告!",MB_OK);
		readfile();
		file.open(filestring,ios::in|ios::out);
	}
	string sline;
	string skey;
	stringstream ss;
	getline(file,sline);
	ss=stringstream(sline);
	while(ss>>skey)keyord.push_back(skey);//输入所有的key 
	getline(file,sline);
	ss=stringstream(sline);
	for(int a=0; a<=(int)keyord.size()-1; ++a)
	{
		string typ; ss>>typ; keytype[keyord[a]]=typ;
	}
	while(getline(file,sline))
	{
		map<string,string>m;
		if(sline=="")continue;
		ss=stringstream(sline);
		for(int b=1-1; b<=(int)keyord.size()-1; ++b)
		{
			ss>>skey; if(skey=="***")skey=""; m[keyord[b]]=skey;//循环读入每条数据的每一个key对应的value 
		}
		datas.push_back(m);
	}
	file.close();
	if(databases.datas.size()==0)MessageBox(hDlg,"文件格式不是有效的 请通过菜单->文件->打开 打开其他有效的文件","警告!",MB_OK);
	return 0;
}
int Stugrade::savedata()
{
	fstream file;
	file.open(filestring,ios::trunc|ios::out);
	for(int a=0; a<=(int)keyord.size()-1; ++a)file<<keyord[a]<<" "; file<<endl;
	for(int a=0; a<=(int)keyord.size()-1; ++a)file<<keytype[keyord[a]]<<" "; file<<endl;
	for(int a=0; a<=(int)datas.size()-1; ++a)
	{
		for(int b=0; b<=(int)keyord.size()-1; ++b)
		{
			string sp=datas[a][keyord[b]];
			if(sp=="")sp="***";
			file<<sp<<" ";
		}file<<endl;
	}
	file.close();
	return 1;
}
int Stugrade::displayallitem()
{if(displayord.size()!=0)
	displayord.clear();
	for(int a=0; a<=(int)datas.size()-1; ++a)
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
int Stugrade::readfile()
{
	OPENFILENAME opfn;
	CHAR strFilename[MAX_PATH];//存放文件名  
								//初始化  
	ZeroMemory(&opfn,sizeof(OPENFILENAME));
	opfn.lStructSize=sizeof(OPENFILENAME);//结构体大小  
										  //设置过滤  
	opfn.lpstrFilter="所有文件\0*.*\0";
	//默认过滤器索引设为1  
	opfn.nFilterIndex=1;
	//文件名的字段必须先把第一个字符设为 \0  
	opfn.lpstrFile=strFilename;
	opfn.lpstrFile[0]='\0';
	opfn.nMaxFile=sizeof(strFilename);
	//设置标志位，检查目录或文件是否存在  
	opfn.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
	//opfn.lpstrInitialDir = NULL;  
	// 显示对话框让用户选择文件  
	if(GetOpenFileName(&opfn))
	{
		//在文本框中显示文件路径  
		filestring=strFilename;
	}
	else return 1;
	return 0;
}
int Stugrade::writefile(HWND hDlg)
{
	TCHAR szPathName[MAX_PATH];
	BROWSEINFO bInfo={0};
	bInfo.hwndOwner=GetForegroundWindow();//父窗口  
	bInfo.lpszTitle=TEXT("浏览文件夹```选择文件夹");
	bInfo.ulFlags=BIF_RETURNONLYFSDIRS|BIF_USENEWUI/*包含一个编辑框 用户可以手动填写路径 对话框可以调整大小之类的..*/|
		BIF_UAHINT/*带TIPS提示*/ /*不带新建文件夹按钮*/;
	//关于更多的 ulFlags 参考 http://msdn.microsoft.com/en-us/library/bb773205(v=vs.85).aspx  
	LPITEMIDLIST lpDlist;
	lpDlist=SHBrowseForFolder(&bInfo);
	if(lpDlist!=NULL)//单击了确定按钮  
	{
		SHGetPathFromIDList(lpDlist,szPathName);
		string s=szPathName;
		MessageBox(hDlg,s.c_str(),"233",0);
	}
	return 0;
}
int Stugrade::savefile(HWND hDlg)
{
	TCHAR szPathName[MAX_PATH];
	OPENFILENAME ofn={OPENFILENAME_SIZE_VERSION_400};//or  {sizeof (OPENFILENAME)}  
													 // lStructSize  
													 // 指定这个结构的大小，以字节为单位。  
													 // Windows 95/98和Windows NT 4.0：特意为Windows 95/98或Windows NT 4.0，及带有WINVER和_WIN32_WINNT >= 0x0500编译时，  
													 //  为这个成员使用OPENFILENAME_SIZE_VERSION_400。  
													 // Windows 2000及更高版本：这个参数使用sizeof (OPENFILENAME) 。  
	ofn.hwndOwner=GetForegroundWindow();// 打开OR保存文件对话框的父窗口  
	ofn.lpstrFilter=TEXT("Text\0*.TXT\0");   
						 //过滤器 如果为 NULL 不使用过滤器  
						 //具体用法看上面  注意 /0  
						 lstrcpy(szPathName,TEXT("file.txt"));
	ofn.lpstrFile=szPathName;
	ofn.nMaxFile=sizeof(szPathName);//存放用户选择文件的 路径及文件名 缓冲区  
	ofn.lpstrTitle=TEXT("选择文件");//选择文件对话框标题  
	TCHAR szCurDir[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurDir),szCurDir);
	ofn.lpstrInitialDir=szCurDir;//设置对话框显示的初始目录  
	ofn.Flags=OFN_EXPLORER|OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST;//如果需要选择多个文件 则必须带有  OFN_ALLOWMULTISELECT标志 
	BOOL bOk=GetSaveFileName(&ofn);//调用对话框打开文件  
	if(bOk)
	{
		string s=szPathName;
		//	MessageBox(hDlg,s.c_str(),"辣鸡",0);
			filestring=s;
	}
	return 0;
}
