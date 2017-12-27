#pragma once
#include<map>
using namespace std;
class Editwindow
{
public:
	Editwindow();
	~Editwindow();
	static Stugrade*	datasx;
	static map<string,string> editbuff;
	static int selectlist;//选中的list中的元素在vector中的位置
	static INT_PTR CALLBACK    Dlgedit(HWND,UINT,WPARAM,LPARAM);//编辑单项界面
};

