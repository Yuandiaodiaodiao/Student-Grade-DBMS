#include "stdafx.h"
#include "solves.h"
solves::solves()
{
}
solves::~solves()
{
}
HWND createlistview(HWND hDlg)
{
	databases.displayallitem();
	HWND hListview=GetDlgItem(hDlg,IDC_LIST2);
	reflashline(hDlg);
	reflashdata(hDlg);
	ListView_SetView(hListview,LVS_REPORT|LVS_SHOWSELALWAYS);
	ListView_SetExtendedListViewStyle(hListview,LVS_EX_FULLROWSELECT|LVS_EX_DOUBLEBUFFER|LVS_EX_CHECKBOXES);//LVS_EX_TRACKSELECT热追踪
	ListView_SetHotItem(hListview,0);
	return hListview;
}
int dellistview(HWND hDlg)
{
	HWND hListview=GetDlgItem(hDlg,IDC_LIST2);
	for(int a=(int)databases.keyord.size()-1+1; a>=0; --a)
	{
		ListView_DeleteColumn(hListview,0);
		//MessageBoxA(hDlg,to_string(a).c_str(),"23",0);
	}
	ListView_DeleteAllItems(hListview);
	return 0;
}
int reflashline(HWND hDlg)
{
	HWND hListview=GetDlgItem(hDlg,IDC_LIST2);
	for(int a=1-1; a<=(int)databases.keyord.size()-1+1; ++a)
	{
		ListView_DeleteColumn(hListview,0);
		//MessageBoxA(hDlg,to_string(a).c_str(),"23",0);
	}
	LVCOLUMN vcl;
	vcl.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
	// 第一列  
	vcl.cx=70;
	int a;
	for( a=1-1; a<=(int)databases.keyord.size()-1; ++a)
	{
		vcl.pszText=(char*)databases.keyord[a].c_str();
		vcl.iSubItem=a;
		ListView_InsertColumn(hListview,a,&vcl);
	}
	
	string s1="排名";
	vcl.pszText=(char*)s1.c_str();
	vcl.iSubItem=a;
	ListView_InsertColumn(hListview,a,&vcl);
	return 0;
}
int reflashdata(HWND hDlg)
{
	HWND hListview=GetDlgItem(hDlg,IDC_LIST2);
	LVITEM vitem;
	vitem.mask=LVIF_TEXT;
	ListView_DeleteAllItems(hListview);
	for(int t=1-1; t<=(int)databases.displayord.size()-1; ++t)
	{
		string sx;
		sx=to_string(databases.displayord[t]);
		int a=databases.displayord[t];
		databases.datas[a]["显示标号"]=to_string(t);
		vitem.iSubItem=0;
		vitem.iItem=t;
		vitem.pszText=(char*)databases.datas[a][databases.keyord[0]].c_str();
		ListView_InsertItem(hListview,&vitem);
		//DialogBoxParam(hInst,MAKEINTRESOURCE(IDD_PROPPAGE_SMALL),hDlg,(DLGPROC)Dlgyesorno,(LPARAM)sx.c_str());
		int b;
		for( b=1; b<=(int)databases.keyord.size()-1; ++b)
		{
			vitem.iSubItem=b;
			vitem.pszText=(char*)databases.datas[a][databases.keyord[b]].c_str();
			ListView_SetItem(hListview,&vitem);
		}
		vitem.iSubItem=b;
		string st=to_string(t+1);
		vitem.pszText=(char*)st.c_str();
		ListView_SetItem(hListview,&vitem);
	}
	return 0;
}
int GetIndex(HWND hList)
{
	int i,n;
	n=ListView_GetItemCount(hList);
	for(i=0; i < n; i++)
		if(ListView_GetItemState(hList,i,LVIS_FOCUSED)==LVIS_FOCUSED)
		{
			return i;
		}
	return -1;
}
std::wstring StringToWString(const std::string& str)
{
	int num=MultiByteToWideChar(CP_UTF8,0,str.c_str(),-1,NULL,0);
	wchar_t *wide=new wchar_t[num];
	MultiByteToWideChar(CP_UTF8,0,str.c_str(),-1,wide,num);
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}
