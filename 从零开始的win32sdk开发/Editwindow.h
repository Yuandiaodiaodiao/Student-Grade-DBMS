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
	static int selectlist;//ѡ�е�list�е�Ԫ����vector�е�λ��
	static INT_PTR CALLBACK    Dlgedit(HWND,UINT,WPARAM,LPARAM);//�༭�������
};

