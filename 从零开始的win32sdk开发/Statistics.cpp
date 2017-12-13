#include "stdafx.h"
#include "Statistics.h"


Statistics::Statistics()
{
}


Statistics::~Statistics()
{
}
string Statistics::cmpstring;
Stugrade * Statistics::datasx;
 HWND Statistics::drop1;
 HWND Statistics::drop2;
HWND Statistics::texts;
string Statistics::stringkey[3]={"最高分","最低分","平均分"};
double Statistics::maxcmp()
{
	Stugrade &datap = *datasx;
	double maxn = 0;
	for (unsigned int a = 0; a <= datap.stanum.size() - 1; ++a) {
		maxn = max(atof(datap.datas[a][cmpstring].c_str()), maxn);
	}
	return maxn;
}

double Statistics::mincmp()
{
	Stugrade &datap = *datasx;
	double minn = -1;
	for (unsigned int a = 0; a <= datap.stanum.size() - 1; ++a) {
		if (minn == -1)minn = atof(datap.datas[a][cmpstring].c_str());
		else minn = min(atof(datap.datas[a][cmpstring].c_str()), minn);
	}
	return minn;

}

double Statistics::averagecmp()
{
	Stugrade &datap = *datasx;
	double ave = 0;
	for (unsigned int a = 0; a <= datap.stanum.size() - 1; ++a) {
		ave += atof(datap.datas[a][cmpstring].c_str());
	}
	return ave/(datap.stanum.size());

}
double Statistics::cmp(int status)
{
	if(status==0)
	{
		return maxcmp();

	}
	else if(status==1)
	{
		return mincmp();
	}
	else return averagecmp();

}
INT_PTR Statistics::DlgStatistics(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	atoi("");
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		//对话框创建完成
		datasx = (Stugrade*)lParam;
		Stugrade &datap = *datasx;
		
		texts = GetDlgItem(hDlg, IDC_STATIC);
		drop1 = GetDlgItem(hDlg, IDC_COMBO1);
		drop2 = GetDlgItem(hDlg, IDC_COMBO2);
		
	
	
		for (unsigned int a = 0; a <= datap.keyord.size() - 1; ++a)
		{
			if(datap.keytype[datap.keyord[a]]=="成绩")
			ComboBox_AddString(drop1, datap.keyord[a].c_str());
		
		}
		ComboBox_AddString(drop2, "最高分");
		ComboBox_AddString(drop2, "最低分");
		ComboBox_AddString(drop2, "平均分");
		ComboBox_SetCurSel(drop1,0);
		ComboBox_SetCurSel(drop2,0);
		char ss[100];
		ComboBox_GetText(drop1,ss,99);
		string s=ss;
		cmpstring=s;
		
		Static_SetText(texts,to_string(cmp(0)).c_str());
		return (INT_PTR)TRUE;
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_COMBO1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{//list选择改变
				Stugrade &datap = *datasx;
				//MessageBoxA(hDlg,"lbnchange","辣鸡",0);
				int x1=ComboBox_GetCurSel(drop1);
				int x2=ComboBox_GetCurSel(drop2);
				cmpstring=stringkey[x2];
				char ss[100];
				 ComboBox_GetText(drop1,ss,99);
				 string s=ss;
				 cmpstring=s;
				 double ans=cmp(x2);
					Static_SetText(texts,to_string(ans).c_str());
				
				break;
			}
			}
			break;
		}
		case IDC_COMBO2:
		{

			switch(HIWORD(wParam))
			{
				case CBN_SELCHANGE:
				{//list选择改变
					Stugrade &datap=*datasx;
					//MessageBoxA(hDlg,"lbnchange","辣鸡",0);
					int x1=ComboBox_GetCurSel(drop1);
					int x2=ComboBox_GetCurSel(drop2);
					cmpstring=stringkey[x2];
					char ss[100];
					ComboBox_GetText(drop1,ss,99);
					string s=ss;
					cmpstring=s;
					double ans=cmp(x2);
					Static_SetText(texts,to_string(ans).c_str());

					break;
				}
			}
			break;
		}
		case IDCANCEL:
		{
			//MessageBoxA(hDlg,to_string(addpos).c_str(),"辣鸡",0);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		
		}
		break;
	}
	}
	return (INT_PTR)FALSE;
}
