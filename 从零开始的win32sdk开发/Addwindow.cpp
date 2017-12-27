#include "stdafx.h"
#include "Addwindow.h"
Addwindow::Addwindow()
{}
Addwindow::~Addwindow()
{}
int Addwindow::addpos;
Stugrade*	Addwindow::datasx;
HWND Addwindow::texts;
HWND Addwindow::listbox;
HWND Addwindow::buttonnext;
map<string,string> Addwindow::mapbuff;
HWND Addwindow::edits;

INT_PTR CALLBACK Addwindow::Dlgadd(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(message)
	{
		case WM_INITDIALOG:
		{
			//�Ի��򴴽����
			datasx=(Stugrade*)lParam;
			Stugrade &datap=*datasx;
			addpos=0;
			HWND editx=GetDlgItem(hDlg,IDC_EDIT2);
			Edit_SetText(editx,to_string(datap.datas.size()).c_str());
			texts=GetDlgItem(hDlg,IDC_STATIC);
			listbox=GetDlgItem(hDlg,IDC_LIST1);
			buttonnext=GetDlgItem(hDlg,IDC_BUTTON1);
			edits=GetDlgItem(hDlg,IDC_EDIT1);
			SetFocus(texts);
			//Edit_TakeFocus(texts);
			Static_SetText(texts,datap.keyord[0].c_str());
			mapbuff.clear();
			for(unsigned int a=0; a<=datap.keyord.size()-1; ++a)
			{
				ListBox_AddString(listbox,datap.keyord[a].c_str());
				mapbuff[datap.keyord[a]]="";
			}
			ListBox_SetCurSel(listbox,addpos);
			return (INT_PTR)TRUE;
			break;
		}
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDC_LIST1:
				{
					switch(HIWORD(wParam))
					{
						case LBN_SELCHANGE:
						{//listѡ��ı�
							Stugrade &datap=*datasx;
							//MessageBoxA(hDlg,"lbnchange","����",0);
							int x=ListBox_GetCurSel((HWND)lParam);
							char ss[101];
							Edit_GetText(edits,ss,100);
							mapbuff[datap.keyord[addpos]]=ss;
							addpos=x;
							Edit_SetText(edits,mapbuff[datap.keyord[addpos]].c_str());
							if(addpos+1!=datap.keyord.size())
							{
								Button_Enable(buttonnext,true);
							}
							else Button_Enable(buttonnext,false);
							Static_SetText(texts,datap.keyord[addpos].c_str());
							break;
						}
					}
					break;
				}
				case IDC_BUTTON1:
				{
					Stugrade &datap=*datasx;
					char ss[101];
					Edit_GetText(edits,ss,100);
					mapbuff[datap.keyord[addpos]]=ss;
					addpos++;
					if(addpos==datap.keyord.size())
					{
						Button_Enable(buttonnext,false);
						addpos--;
						break;
					}
					Static_SetText(texts,datap.keyord[addpos].c_str());
					ListBox_SetCurSel(listbox,addpos);
					Edit_SetText(edits,mapbuff[datap.keyord[addpos]].c_str());
					break;
				}
				case IDCANCEL:
				{
					//MessageBoxA(hDlg,to_string(addpos).c_str(),"����",0);
					EndDialog(hDlg,LOWORD(wParam));
					return (INT_PTR)TRUE;
					break;
				}
				case IDOK:
				{
					//MessageBoxA(hDlg,to_string(addpos).c_str(),"����",0);
					Stugrade &datap=*datasx;
					HWND editx=GetDlgItem(hDlg,IDC_EDIT2);
					char ss[101];
					Edit_GetText(editx,ss,100);
					int xa=atoi(ss);
					datap.datas.insert(datap.datas.begin()+xa,mapbuff);
					
					EndDialog(hDlg,LOWORD(wParam));
					return (INT_PTR)TRUE;
					break;
				}
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}
