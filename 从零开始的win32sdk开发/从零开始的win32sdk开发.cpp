
//

#include "stdafx.h"



using namespace std;
#define MAX_LOADSTRING 100

// 全局变量: 
Stugrade databases;
HINSTANCE hInst1;
HWND mainwindow;//主窗口
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hwdialog; //dialog的句柄
HWND listview1;
int selectlist;


// 此代码模块中包含的函数的前向声明: 
int createlistview(HWND hDlg);
int reflashline(HWND hDlg);
int reflashdata(HWND hDlg);
int GetIndex(HWND hList);
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE,int);
LRESULT CALLBACK    WndProc(HWND,UINT,WPARAM,LPARAM);
INT_PTR CALLBACK    About(HWND,UINT,WPARAM,LPARAM);
INT_PTR CALLBACK    Dlg(HWND,UINT,WPARAM,LPARAM);//处理dialog的消息
INT_PTR CALLBACK    Dlgyesorno(HWND,UINT,WPARAM,LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hInst1=(HINSTANCE)::GetModuleHandle(NULL);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance,IDS_APP_TITLE,szTitle,MAX_LOADSTRING);
	LoadStringW(hInstance,IDC_WIN32SDK,szWindowClass,MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if(!InitInstance(hInstance,nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDC_WIN32SDK));

	MSG msg;

	// 主消息循环: 
	while(GetMessage(&msg,nullptr,0,0))
	{
		if(!TranslateAccelerator(msg.hwnd,hAccelTable,&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize=sizeof(WNDCLASSEX);

	wcex.style=CS_HREDRAW|CS_VREDRAW;
	wcex.lpfnWndProc=WndProc;
	wcex.cbClsExtra=0;
	wcex.cbWndExtra=0;
	wcex.hInstance=hInstance;
	wcex.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDC_WIN32SDK));
	wcex.hCursor=LoadCursor(nullptr,IDC_ARROW);
	wcex.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName=MAKEINTRESOURCEW(IDC_WIN32SDK);
	wcex.lpszClassName=szWindowClass;
	wcex.hIconSm=LoadIcon(wcex.hInstance,MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance,int nCmdShow)
{
	hInst=hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd=CreateWindowW(szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,0,CW_USEDEFAULT,0,nullptr,nullptr,hInstance,nullptr);
	mainwindow=hWnd;
	if(!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
		databases.readdata();
		hwdialog=CreateDialog(hInst,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,(DLGPROC)Dlg);
		if(hwdialog)
		{
			//显示对话框  
			ShowWindow(hwdialog,SW_SHOWNA);
		}

		return 0;
	case WM_COMMAND:
	{

		int wmId=LOWORD(wParam);
		// 分析菜单选择: 
		switch(wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst,MAKEINTRESOURCE(IDD_ABOUTBOX),hWnd,About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd,message,wParam,lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc=BeginPaint(hWnd,&ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hWnd,&ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(message)
	{
	case WM_INITDIALOG: //对话框创建完成
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if(LOWORD(wParam)==IDOK||LOWORD(wParam)==IDCANCEL)
		{
			EndDialog(hDlg,LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Dlg(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(message)
	{

	case WM_COMMAND:
	{
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:{
			databases.savedata();
			reflashdata(hDlg);
			break;
		}
		case ID_233_32771://右键list view编辑

		{
			int xc=ListView_GetHotItem(listview1);
			xc=GetIndex(listview1);

			string sx;
			sx=to_string(xc);
			//if(x!=-1)s="233";
			//MessageBoxA(hDlg,to_string().c_str(),"辣鸡",0);
			break;
		}
		case ID_233_32772:{//删除右键菜单
						   //DialogBox(hInst,MAKEINTRESOURCE(IDD_ABOUTBOX),hDlg,Dlgyesorno);
						   /*DialogBoxParam(hInst,
						   MAKEINTRESOURCE(IDD_PROPPAGE_SMALL),
						   hDlg,
						   (DLGPROC)Dlgyesorno,
						   (LPARAM)"确认要删除吗?");*/
			
			int xc=GetIndex(listview1);
			string sx;
			sx=to_string(xc);
			BOOL returnData=(bool)DialogBoxParam(hInst,MAKEINTRESOURCE(IDD_PROPPAGE_SMALL),hDlg,(DLGPROC)Dlgyesorno,(LPARAM)"确认删除这行数据?");
			if(returnData==FALSE)break;
			/*if(returnData!=NULL)
			{
			//先将字符拷贝一次
			string s=returnData;

			//显示从对话框返回的内容
			MessageBox(hDlg,returnData,"从对话框返回的数据",MB_OK);
			}*/
			
			set<int>s; s.insert(databases.displayord[xc]);
			databases.deldata(s);//执行删除函数
			reflashdata(hDlg);//刷新listview
			break;
		}
		}
	}

	case WM_NOTIFY:{
		switch(wParam)
		{
		case IDC_LIST2:{

			LPNMITEMACTIVATE now;
			now=(LPNMITEMACTIVATE)lParam;//得到NMITEMACTIVATE结构指针  
			char a[50];
			_itoa_s(now->iItem,a,10);//now->iItem项目序号 
									 //ListView_SetHotItem(listview1,now->iItem);
									 //if(now->iItem!=-1)
									 //ListView_SetHotItem(listview1,now->iItem);
			switch(now->hdr.code)
			{
			case LVN_COLUMNCLICK:{
				string s=to_string(now->iSubItem);
				databases.sortviakey(now->iSubItem);
				reflashdata(hDlg);
				//MessageBoxA(hDlg,s.c_str(),s.c_str(),0);
				break;
			}
			case NM_CLICK:{
				if(now->iItem!=-1)
					ListView_SetHotItem(listview1,now->iItem);
				break;
			}
			case NM_DBLCLK:{
				if(now->iItem!=-1)
					ListView_SetHotItem(listview1,now->iItem);
				int x=SendMessage(listview1,LVM_GETHOTITEM,0,0);
				x=ListView_GetHotItem(listview1);

				string s;
				s=to_string(x);
				//if(x!=-1)s="233";
				MessageBoxA(hDlg,s.c_str(),s.c_str(),0);
				break;
			}

			case NM_RCLICK:{
				//MessageBox(hDlg,"23333","提示",MB_OK);
				/*	HMENU hroot=LoadMenu((HINSTANCE)GetWindowLongPtr(listview1,GWLP_HINSTANCE),MAKEINTRESOURCE(IDR_MENU1));
				if(hroot)
				{
				// 获取第一个弹出菜单
				HMENU hpop=GetSubMenu(hroot,0);
				// 获取鼠标右击是的坐标
				//int px = GET_X_LPARAM(lParam);
				//int py = GET_Y_LPARAM(lParam);
				//显示快捷菜单
				TrackPopupMenu(hInst1,
				TPM_LEFTALIGN|TPM_TOPALIGN|TPM_RIGHTBUTTON,
				LOWORD(lParam),
				HIWORD(lParam),
				0,
				(HWND)wParam,
				NULL);
				// 用完后要销毁菜单资源
				DestroyMenu(hroot);
				}*/

				if(now->iItem==-1)break;
				ListView_SetHotItem(listview1,now->iItem);
				//	MessageBoxA(listview1,"2233","右击",0);
				HMENU hroot=LoadMenu((HINSTANCE)GetWindowLongPtr(listview1,GWLP_HINSTANCE),MAKEINTRESOURCE(IDR_MENU1));
				HMENU hMenu=::LoadMenu(hInst1,MAKEINTRESOURCE(IDR_MENU1));
				HMENU hPopMenu=::GetSubMenu(hroot,0);
				POINT pt;
				::GetCursorPos(&pt);
				::SetForegroundWindow(hDlg);
				//::ModifyMenu(hPopMenu,ID_233_32771,MF_BYCOMMAND|MF_GRAYED,ID_233_32771,"剪切    Ctrl + X");
				//::ModifyMenu(hPopMenu,ID_EDITMENU_COPY,MF_BYCOMMAND|MF_GRAYED,ID_EDITMENU_COPY,L"复制    Ctrl + C");
				TrackPopupMenu(hPopMenu,TPM_RIGHTBUTTON,pt.x,pt.y,0,hDlg,NULL);
				DestroyMenu(hMenu);
				//MessageBoxA(listview1,a,"右击",0);
				//MessageBoxA(hDlg,a,"右击",0);
				//	if(now->iItem==-1)break;
				//ListView_SetHotItem(listview1,now->iItem);
				//	int x=ListView_GetHotItem(listview1);

				string s;
				//s=to_string(x);
				//if(x!=-1)s="233";
				//MessageBoxA(hDlg,s.c_str(),s.c_str(),0);

				break;
			}
			}
			break; }

		}
		break; }
	case WM_INITDIALOG:
	{// 获取ListView控件的句柄  
		createlistview(hDlg);

		//ListView_SetExtendedListViewStyle(hListview,LVS_SINGLESEL);

		/*	vcl.pszText="姓名";//列标题
		vcl.cx=90;//列宽
		vcl.iSubItem=0;//子项索引，第一列无子项
		ListView_InsertColumn(hListview,0,&vcl);
		// 第二列
		vcl.pszText=L"年龄";
		vcl.cx=90;
		vcl.iSubItem=1;//子项索引
		ListView_InsertColumn(hListview,1,&vcl);
		// 第三列
		vcl.pszText=L"地址";
		vcl.cx=200;
		vcl.iSubItem=2;
		ListView_InsertColumn(hListview,2,&vcl);*/
		return 0; }
	case WM_SYSCOMMAND:
		if(wParam==SC_CLOSE)
		{
			// 如果执行了关闭  
			// 销毁对话框，将收到WM_DESTROY消息  
			DestroyWindow(hwdialog);
		}
		return 0;
	}

	return (INT_PTR)FALSE;
}
int createlistview(HWND hDlg)
{
	databases.displayallitem();
	HWND hListview=GetDlgItem(hDlg,IDC_LIST2);
	listview1=hListview;
	reflashline(hDlg);
	reflashdata(hDlg);
	ListView_SetView(hListview,LVS_REPORT|LVS_SHOWSELALWAYS);
	ListView_SetExtendedListViewStyle(hListview,LVS_EX_FULLROWSELECT|LVS_EX_DOUBLEBUFFER|LVS_EX_CHECKBOXES);//LVS_EX_TRACKSELECT热追踪
	ListView_SetHotItem(listview1,0);
	return 0;
}
int reflashline(HWND hDlg)
{
	HWND hListview=GetDlgItem(hDlg,IDC_LIST2);
	for(int a=1-1; a<=(int)databases.keyord.size()-1; ++a)
	{
		ListView_DeleteColumn(hListview,a);
	}
	listview1=hListview;
	LVCOLUMN vcl;
	vcl.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
	// 第一列  
	vcl.cx=70;
	for(int a=1-1; a<=(int)databases.keyord.size()-1; ++a)
	{
		vcl.pszText=(char*)databases.keyord[a].c_str();
		vcl.iSubItem=a;
		ListView_InsertColumn(hListview,a,&vcl);
	}
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
		
		//MessageBoxA(hDlg,to_string(databases.displayord[t]).c_str(),"辣鸡",0);
		int a=databases.displayord[t];
		databases.datas[a]["显示标号"]=to_string(t);
		vitem.iSubItem=0;
		vitem.iItem=t;
		vitem.pszText=(char*)databases.datas[a][databases.keyord[0]].c_str();
		ListView_InsertItem(hListview,&vitem);
		for(int b=1; b<=(int)databases.keyord.size()-1; ++b)
		{
			vitem.iSubItem=b;
			vitem.pszText=(char*)databases.datas[a][databases.keyord[b]].c_str();
			ListView_SetItem(hListview,&vitem);
		}
	}
	return 0;
}

INT_PTR CALLBACK Dlgyesorno(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch(message)
	{
	case WM_INITDIALOG: {//对话框创建完成
		LPCWSTR param=(LPCWSTR)lParam;
		//取得显示文本控件的句柄  
		HWND stDisplay=GetDlgItem(hDlg,IDC_STATIC);
		//设置文本  
		SendMessage(stDisplay,WM_SETTEXT,NULL,(WPARAM)param);
		break;
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if(LOWORD(wParam)==IDC_BUTTON1)
		{

			string s="辣鸡";
			char px[40]="辣鸡";
			strcpy_s(px,s.c_str());


			EndDialog(hDlg,(INT_PTR)TRUE);
			return (INT_PTR)TRUE;
		} else if(LOWORD(wParam)==IDC_BUTTON2)
		{
			EndDialog(hDlg,(INT_PTR)FALSE);
			return (INT_PTR)TRUE;

		}
		break;
	}
	return (INT_PTR)FALSE;
	/*switch(message)
	{
	case WM_INITDIALOG:
	{

	}

	}
	switch(message)
	{
	case WM_INITDIALOG: //对话框创建完成
	return (INT_PTR)TRUE;

	case WM_COMMAND:
	if(LOWORD(wParam)==IDC_BUTTON1)
	{
	string s="ok";
	EndDialog(hDlg,(INT_PTR)s.c_str());
	return (INT_PTR)TRUE;
	} else  if(LOWORD(wParam)==IDC_BUTTON2)
	{
	string s="no";
	EndDialog(hDlg,(INT_PTR)s.c_str());
	return (INT_PTR)TRUE;
	}
	break;
	}
	return (INT_PTR)FALSE;
	*/
}
int GetIndex(HWND hList)
{
	int i,n;
	n=ListView_GetItemCount(hList);
	for(i=0; i < n; i++)
		if(ListView_GetItemState(hList,i,LVIS_FOCUSED)==LVIS_FOCUSED)
			return i;
	return -1;
}