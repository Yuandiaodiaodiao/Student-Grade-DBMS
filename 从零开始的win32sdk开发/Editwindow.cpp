#include "stdafx.h"
#include "Editwindow.h"


Editwindow::Editwindow()
{}


Editwindow::~Editwindow()
{}
Stugrade*	Editwindow::datasx;
 int Editwindow::selectlist;
map<string,string> Editwindow::editbuff;
//编辑框消息处理
INT_PTR CALLBACK   Editwindow::Dlgedit(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
		case WM_INITDIALOG:
		{
			datasx=(Stugrade*)lParam;
			Stugrade &datap=*datasx;
			editbuff=datap.datas[selectlist];
			HWND editbox=GetDlgItem(hDlg,IDC_EDIT1);
			HWND listbox=GetDlgItem(hDlg,IDC_LIST1);
			for(int a=0; a<=((int)datap.keyord.size())-1; ++a)
			{
				ListBox_AddString(listbox,datap.keyord[a].c_str());
			}
			Edit_SetText(editbox,datap.datas[selectlist][datap.keyord[0]].c_str());
			ListBox_SetCurSel(listbox,0);
			break;
		}
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDC_BUTTON1:
				{
					Stugrade &datap=*datasx;
					datap.datas[selectlist]=editbuff;
					EndDialog(hDlg,LOWORD(wParam));
					break;
				}
				case IDCANCEL:
				{
					EndDialog(hDlg,LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				case IDC_EDIT1://edit控件
				{
					switch(HIWORD(wParam))
					{
						case EN_KILLFOCUS://失去焦点 这时对edit进行一次保存
						{
							Stugrade &datap=*datasx;
							HWND listbox=GetDlgItem(hDlg,IDC_LIST1);
							char ss[101];
							Edit_GetText((HWND)lParam,ss,100);
							int x=ListBox_GetCurSel(listbox);
							string s=ss;
							//	MessageBoxA(hDlg,s.c_str(),"辣鸡",0);
							editbuff[datap.keyord[x]]=s;
							break;
						}
					}
					break;
				}
				case IDC_LIST1:
				{//list控件
					switch(HIWORD(wParam))
					{
						case LBN_SELCHANGE:
						{//list选择改变
						 //MessageBoxA(hDlg,"lbnchange","辣鸡",0);
							Stugrade &datap=*datasx;
							int x=ListBox_GetCurSel((HWND)lParam);
							HWND editbox=GetDlgItem(hDlg,IDC_EDIT1);
							Edit_SetText(editbox,editbuff[datap.keyord[x]].c_str());
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}