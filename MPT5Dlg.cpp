// MPT5Dlg.cpp : 实现文件
//
#include "stdafx.h"
#include "MPT5.h"
#include "MPT5Dlg.h"
#include "NewName.h"
#include "CWMPControls.h"
#include "BreakPoint.h"
#include "m_close.h"
#include "About.h"
#include "DelHistory.h"
#include <shlwapi.h>//判断文件是否存在的头文件
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int hide_button;//控制功能按钮出现与隐藏
int hide_list=0;//控制播放列表出现与隐藏
CString m_pathname;//当前播放曲目的路径
CString now_list;//记录当前播放列表
const int length = 338;//进度条长度
bool lyrics=0;//确定歌词是否显示
CString now_pathname="12";//当前正在播放歌词的曲目
bool delh=0;//播放痕迹的清除

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMPT5Dlg 对话框




CMPT5Dlg::CMPT5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMPT5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MPT5ICON);
}

void CMPT5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX, m_player);
	DDX_Control(pDX, IDC_PListBox, m_list);
	DDX_Control(pDX, IDC_PListBox2, m_list2);
	DDX_Control(pDX, IDC_ListCombo, m_combobox);
	DDX_Control(pDX, IDC_ModeCombo, m_combobox2);
	DDX_Control(pDX, IDC_EDIT1, m_time);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_Pause, m_play);
	DDX_Control(pDX, IDC_Previous, m_previous);
	DDX_Control(pDX, IDC_Next, m_next);
	DDX_Control(pDX, IDC_Stop, m_stop);
	DDX_Control(pDX, IDC_Up, m_up);
	DDX_Control(pDX, IDC_Down, m_down);
	DDX_Control(pDX, IDC_List, m_flexlist);
	DDX_Control(pDX, IDC_SetAB, m_setab);
	DDX_Control(pDX, IDC_DelAB, m_delab);
	DDX_Control(pDX, IDC_AddList, m_addlist);
	DDX_Control(pDX, IDC_ReNameList, m_renamelist);
	DDX_Control(pDX, IDC_DelList, m_dellist);
	DDX_Control(pDX, IDC_AddFolder, m_addfolder);
	DDX_Control(pDX, IDC_FastForward, m_fastforward);
	DDX_Control(pDX, IDC_BUTTON1, m_mute);
	DDX_Control(pDX, IDC_ResetList, m_trash);
	DDX_Control(pDX, IDC_AddFile, m_addfile);
	DDX_Control(pDX, IDC_RemoveFile, m_removefile);
	DDX_Control(pDX, IDC_Exit, m_esc);
	DDX_Control(pDX, IDC_BUTTON2, m_marka);
	DDX_Control(pDX, IDC_BUTTON3, m_markb);
	DDX_Control(pDX, IDC_EDIT2, m_lyric);
	DDX_Control(pDX, IDC_CHECK1, m_geci);
	DDX_Control(pDX, IDC_SLIDER2, m_valumSlider);
}

BEGIN_MESSAGE_MAP(CMPT5Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SetAB, &CMPT5Dlg::OnBnClickedSetAB)
	ON_BN_CLICKED(IDC_DelAB, &CMPT5Dlg::OnBnClickedDelaB)
	ON_BN_CLICKED(IDC_List, &CMPT5Dlg::OnBnClickedList)
	ON_BN_CLICKED(IDC_AddList, &CMPT5Dlg::OnBnClickedAddlist)
	ON_BN_CLICKED(IDC_ReNameList, &CMPT5Dlg::OnBnClickedRenamelist)
	ON_BN_CLICKED(IDC_AddFile, &CMPT5Dlg::OnBnClickedAddfile)
	ON_BN_CLICKED(IDC_DelList, &CMPT5Dlg::OnBnClickedDellist)
	ON_BN_CLICKED(IDC_ResetList, &CMPT5Dlg::OnBnClickedResetlist)
	ON_BN_CLICKED(IDC_AddFolder, &CMPT5Dlg::OnBnClickedAddfolder)
	ON_BN_CLICKED(IDC_RemoveFile, &CMPT5Dlg::OnBnClickedRemovefile)
	ON_BN_CLICKED(IDC_Pause, &CMPT5Dlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_FastForward, &CMPT5Dlg::OnBnClickedFastforward)
	ON_BN_CLICKED(IDC_Previous, &CMPT5Dlg::OnBnClickedPrevious)
	ON_BN_CLICKED(IDC_Next, &CMPT5Dlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_Stop, &CMPT5Dlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_Exit, &CMPT5Dlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_Up, &CMPT5Dlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_Down, &CMPT5Dlg::OnBnClickedDown)
	ON_LBN_DBLCLK(IDC_PListBox, &CMPT5Dlg::OnLbnDblclkPlistbox)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_ListCombo, &CMPT5Dlg::OnCbnSelchangeListcombo)
	ON_WM_DROPFILES()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CMPT5Dlg::OnNMReleasedcaptureSlider1)

	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CMPT5Dlg::OnBnClickedButton1)

	ON_MESSAGE(WM_MYMESSAGE2, Handler)
	ON_MESSAGE(WM_MYMESSAGE1, Handler1)
	ON_MESSAGE(WM_MYMESSAGE_CLICKED, Handler2)

	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENU_T,OpenWindow)
	ON_COMMAND(ID_MENU_N,OnBnClickedAddlist)
	ON_COMMAND(ID_32779,OnBnClickedAddfile)
	ON_COMMAND(ID_32780,OnBnClickedAddfolder)
	ON_COMMAND(ID_32781,OnBnClickedRemovefile)
	ON_COMMAND(ID_32782,OnBnClickedDellist)
	ON_COMMAND(ID_32776,OnBnClickedAddlist)
	ON_COMMAND(ID_32777,OnBnClickedRenamelist)
	ON_COMMAND(ID_Menu,OnBnClickedResetlist)
	ON_COMMAND(ID_32783,OnBnClickedSetAB)
	ON_COMMAND(ID_32785,OnBnClickedDelaB)
	ON_COMMAND(ID_32787,OnBnClickedList)
	ON_COMMAND(ID_32788,AboutUs)
	ON_COMMAND(ID_MENU_32794,OnBnClickedPause)
	ON_COMMAND(ID_MENU_32795,OnBnClickedPrevious)
	ON_COMMAND(ID_MENU_32796,OnBnClickedNext)
	ON_COMMAND(ID_MENU_32797,OnBnClickedExit)
	ON_COMMAND(ID_MENU_32798,OnBnClickedRenamelist)
	ON_COMMAND(ID_MENU_32799,OnBnClickedResetlist)
	ON_COMMAND(ID_MENU_32800,OnBnClickedDellist)
	ON_COMMAND(ID_MENU_32801,OnBnClickedAddfile)
	ON_COMMAND(ID_MENU_32802,OnBnClickedAddfolder)
	ON_COMMAND(ID_MENU_32807,OnBnClickedRemovefile)
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK1, &CMPT5Dlg::OnBnClickedCheck1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
VOID CMPT5Dlg::OpenWindow()
{
	this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿  
	DeleteTray();
}
LRESULT CMPT5Dlg::Handler(WPARAM wParam,LPARAM lParam)
{
	ToTray();
	return 0;
}
LRESULT CMPT5Dlg::Handler1(WPARAM wParam,LPARAM lParam)//关闭
{
	CStdioFile file;
	int j=file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate|CFile::modeWrite);
	now_list+="\n";
	file.WriteString(now_list);
	m_pathname+="\n";
	file.WriteString(m_pathname);
	CString time1;//给人看的时间**：**：**\**:**:**
	m_time.GetWindowText(time1);
	time1+="\n";
	file.WriteString(time1);
	CString time2;//int型时间
	time2.Format("%d",(int)m_ctr.GetCurrentPosition());
	file.WriteString(time2);
	file.Close();
	if(m_ctr.GetCurrentPosition()==0)//如果一开始没播任何曲目或者断点时间为0，要让breakpoint.txt是空的
	{
		file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate);
		file.Close();
	}
	CDialog::OnCancel();
	KillTimer(1);//一定要记住在退出程序时删除计数器,释放内存，这是个很好的习惯
	return 0;
}
LRESULT CMPT5Dlg::Handler2(WPARAM wParam,LPARAM lParam)
{
	delh=1;
	return 0;
}

// CMPT5Dlg 消息处理程序

BOOL CMPT5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	startP = -1;
	endP = -1;
	flagAB = 3;//表示不在两点播放

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

		
	EnableToolTips(TRUE);//enable use it
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.SetTipTextColor(RGB(0,0,0));//文字颜色
	m_tooltip.SetDelayTime(TTDT_INITIAL, 10); //鼠标指向多久后显示提示，毫秒
	m_tooltip.SetDelayTime(TTDT_AUTOPOP, 2000); //鼠标保持指向，提示显示多久，毫秒
	m_tooltip.SetMaxTipWidth(200);//设定显示宽度，超长内容自动换行
	m_tooltip.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
	//////////////////////按钮提示/////////////////////////////
	m_tooltip.AddTool(GetDlgItem(IDC_SetAB), (LPCTSTR)"设置A-B点");
	m_tooltip.AddTool(GetDlgItem(IDC_AddFile), (LPCTSTR)"添加文件");
	m_tooltip.AddTool(GetDlgItem(IDC_AddList), (LPCTSTR)"添加列表");
	m_tooltip.AddTool(GetDlgItem(IDC_DelAB), (LPCTSTR)"退出两点播放模式");
	m_tooltip.AddTool(GetDlgItem(IDC_DelList), (LPCTSTR)"删除列表");
	m_tooltip.AddTool(GetDlgItem(IDC_ReNameList),(LPCTSTR) "重命名列表");
	m_tooltip.AddTool(GetDlgItem(IDC_ResetList),(LPCTSTR) "清空列表");
	m_tooltip.AddTool(GetDlgItem(IDC_RemoveFile),(LPCTSTR) "移除文件");
	m_tooltip.AddTool(GetDlgItem(IDC_AddFolder), (LPCTSTR)"添加文件夹");
	m_tooltip.AddTool(GetDlgItem(IDC_Stop), (LPCTSTR)"停止播放");
	m_tooltip.AddTool(GetDlgItem(IDC_Pause), (LPCTSTR)"播放/暂停");
	m_tooltip.AddTool(GetDlgItem(IDC_FastForward), (LPCTSTR)"快进播放");
	m_tooltip.AddTool(GetDlgItem(IDC_Previous), (LPCTSTR)"上一曲");
	m_tooltip.AddTool(GetDlgItem(IDC_Next), (LPCTSTR)"下一曲");
	m_tooltip.AddTool(GetDlgItem(IDC_List), (LPCTSTR)"展开/隐藏播放列表");
	m_tooltip.AddTool(GetDlgItem(IDC_ListCombo), (LPCTSTR)"选择播放列表");
	m_tooltip.AddTool(GetDlgItem(IDC_ModeCombo), (LPCTSTR)"选择播放模式");
	m_tooltip.AddTool(GetDlgItem(IDC_Exit), (LPCTSTR)"退出播放器");
	m_tooltip.AddTool(GetDlgItem(IDC_Up), (LPCTSTR)"向上调整");
	m_tooltip.AddTool(GetDlgItem(IDC_Down), (LPCTSTR)"向下调整");
	m_tooltip.AddTool (GetDlgItem(IDC_PListBox),(LPCTSTR)"");
	m_tooltip.AddTool (GetDlgItem(IDC_BUTTON1),(LPCTSTR)"静音");
	/////////////////////////按钮贴图//////////////////////////////////
	m_background.LoadBitmap(IDB_BackGround);
	m_play.LoadBitmaps(IDB_Play1,IDB_Play2);
	m_previous.LoadBitmaps(IDB_Previous1,IDB_Previous2);
	m_next.LoadBitmaps(IDB_Next1,IDB_Next2);
	m_stop.LoadBitmaps(IDB_Stop2,IDB_Stop1);
	m_up.LoadBitmaps(IDB_Up1,IDB_Up2);
	m_down.LoadBitmaps(IDB_Down1,IDB_Down2);
	m_flexlist.LoadBitmaps(IDB_Back1,IDB_Back2);
	m_setab.LoadBitmaps(IDB_SetA);
	m_delab.LoadBitmaps(IDB_Del1,IDB_Del2);
	m_fastforward.LoadBitmaps(IDB_FastForeward1,IDB_FastForeward2);
	m_mute.LoadBitmaps(IDB_Volume1,IDB_Volume2);
	m_trash.LoadBitmaps(IDB_Trash1,IDB_Trash2);
	m_addfile.LoadBitmaps(IDB_AddFile1,IDB_AddFile2);
	m_removefile.LoadBitmaps(IDB_RemoveFile1,IDB_RemoveFile2);
	m_esc.LoadBitmaps(IDB_Esc2,IDB_Esc1);
	m_marka.LoadBitmaps(IDB_MarkA);
	m_markb.LoadBitmaps(IDB_MarkB);
	m_marka.ShowWindow(SW_HIDE);
	m_markb.ShowWindow(SW_HIDE);
	m_addlist.ShowWindow(SW_HIDE);
	m_renamelist.ShowWindow(SW_HIDE);
	m_dellist.ShowWindow(SW_HIDE);
	m_addfolder.ShowWindow(SW_HIDE);

	if(!PathIsDirectory(".\\List"))//最开始使用时自建文件
	{
		CreateDirectory(".\\List",NULL);
		CreateDirectory(".\\List\\EachList",NULL);
		CreateDirectory(".\\List\\Lyrics",NULL);
		CStdioFile file;
		int k=file.Open(".\\List\\ListName.txt",CFile::modeCreate|CFile::modeWrite);
		file.WriteString("默认列表");
		file.Close();
		file.Open(".\\List\\EachList\\默认列表.txt",CFile::modeCreate);
		file.Close();
		file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate);
		file.Close();
	}
	else
		SetTimer(2,500,NULL);//放在这里是因为一开始breakpoint.txt是空的
	m_list.SetHorizontalExtent(500);
	CStdioFile *fsp1=new CStdioFile(".\\List\\EachList\\默认列表.txt",CFile::modeRead);
	CString str1;
	while(fsp1->ReadString(str1))
	{
		m_list2.AddString(str1);
		str1=str1.Right(str1.GetLength()-str1.ReverseFind('\\') -1);//只显示歌曲名
		m_list.AddString(str1);
	}
	fsp1->Close();
	delete fsp1;
	m_list.SetSel(0);
	m_list2.SetSel(0);//载入播放列表

	CStdioFile *fsp2=new CStdioFile(".\\List\\ListName.txt",CFile::modeRead);
	CString str2;
	while(fsp2->ReadString(str2))
	{
		m_combobox.AddString(str2);
	}
	fsp2->Close();
	delete fsp2;
	m_combobox.SetCurSel(0);
	now_list="默认列表";//载入播放列表名称

	m_combobox2.AddString("顺序播放");
	m_combobox2.AddString("列表循环");
	m_combobox2.AddString("单曲循环");
	m_combobox2.AddString("随机播放");
	m_combobox2.SetCurSel(0);//默认播放模式为顺序播放

	m_ctr = m_player.GetControls();

	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	pSlidCtrl->SetRange(-100,0,TRUE);//设置滑动条范围
	pSlidCtrl->SetPos(-66);//设置滑动条位置
	m_settings = m_player.GetSettings();
    
	counts=0;
	for(int i=0;i<100;i++)
		dtime[i]=0;
	m_lyric.ShowWindow(SW_HIDE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CMPT5Dlg::ToTray()//隐藏主窗口
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDI_MPT5ICON;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_MPT5ICON));
	strcpy(nid.szTip,"MPT5");    //信息提示条 
	Shell_NotifyIcon(NIM_ADD,&nid);    //在托盘区添加图标
	ShowWindow(SW_HIDE);    //隐藏主窗口
}
void CMPT5Dlg::DeleteTray()//删除托盘图标
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDI_MPT5ICON;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;          //自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_MPT5ICON));
	strcpy(nid.szTip,"MPT5");    //信息提示条为“计划任务提醒”   
	Shell_NotifyIcon(NIM_DELETE,&nid);    //在托盘区删除图标 
}
LRESULT CMPT5Dlg::OnShowTask(WPARAM wParam,LPARAM lParam)//托盘
{
	if(wParam!=IDI_MPT5ICON) 
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，
		{
			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);//得到鼠标位置
			CMenu menu;
			menu.LoadMenu(IDR_MENU2); 
			menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); //确定弹出式菜单的位置                 
			HMENU hmenu=menu.Detach(); 
			menu.DestroyMenu(); //资源回收 
			delete lpoint; 
			//DeleteTray();
		}  break;
	case WM_LBUTTONDBLCLK:      //双击左键的处理 
		{ 
			this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿  
			DeleteTray();
		}  break;
	default:   break; 
	} 
	return 0; 
}
void CMPT5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID==SC_CLOSE)
	{
		m_close mclose;
		mclose.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMPT5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
				CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem; 
		dcMem.CreateCompatibleDC(&dc); 
		BITMAP bitMap;
		m_background.GetBitmap(&bitMap);
		CBitmap *pbmpOld=dcMem.SelectObject(&m_background);
		dc.StretchBlt(0,0,753,rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
		//m_flexlist.MoveWindow(281,14,20,203,false);
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMPT5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMPT5Dlg::Save()//自动保存
{
	CString str;
	int index=m_combobox.GetCurSel();
	m_combobox.GetLBText(index,str);

	CString path;
	path.Format(".\\List\\EachList\\%s.txt",str);
	CStdioFile file;
	file.Open(path,CFile::modeCreate|CFile::modeWrite);

	for(int i=0;i<m_list.GetCount();i++)
	{
		CString strtemp;
		m_list2.GetText(i,strtemp);	
		strtemp+="\n";//需要换行
		file.WriteString(strtemp);	
	}
	file.Close();
}

void CMPT5Dlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	CRect rect;//定义矩形区域

	GetDlgItem(IDC_PListBox)->GetWindowRect(&rect);//获取控件区域的矩形
	if(rect.PtInRect(point))
	{
		CMenu   menu;  
		VERIFY(menu.LoadMenu(IDR_MENU3));  
		CMenu*   pPopup=menu.GetSubMenu(0);  
		ASSERT(pPopup!=NULL); 
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this); //在鼠标当前位置显示指定菜单
	}
}
void CMPT5Dlg::SetList()//设置成正在播放的列表
{
	CString str;
	m_combobox.GetLBText(m_combobox.GetCurSel(),str);
	if(str!=now_list)//如果播放的列表和当前列表不一致，转换列表
	{
		for(int i=0;i<m_combobox.GetCount();i++)
		{
			m_combobox.GetLBText(i,str);
			if(str==now_list)
				m_combobox.SetCurSel(i);
		}//先自动跳到正在播放的列表
		CString m_strFolderPath;
		m_strFolderPath.Format(".\\List\\EachList\\%s.txt",now_list);
		m_list.ResetContent();
		m_list2.ResetContent();

		CString str2;
		CStdioFile *fsp=new CStdioFile(m_strFolderPath,CFile::modeRead);
		while(fsp->ReadString(str2))
		{
			m_list2.AddString(str2);
			str2=str2.Right(str2.GetLength()-str2.ReverseFind('\\') -1);//只显示歌曲名
			m_list.AddString(str2);
		}
		fsp->Close();//然后刷新播放列表

		for(int i=0;i<m_list2.GetCount();i++)
		{
			CString str3;
			m_list2.GetText(i,str3);
			if(str3==m_pathname)
			{
				m_list.SetSel(i);
				m_list2.SetSel(i);
			}
		}//将光标设置为当前播放曲目
	}
}
void CMPT5Dlg::OnBnClickedList()//播放列表出现与隐藏
{
	hide_list=!hide_list;
		if(!hide_list)
		{
			m_flexlist.LoadBitmaps(IDB_Back1,IDB_Back2);
			m_flexlist.RedrawWindow();
			m_up.ShowWindow(SW_SHOW);
			m_down.ShowWindow(SW_SHOW);
			SetWindowPos(NULL,0,0,753,554,SWP_NOMOVE);

		}
		else
		{
			
			m_flexlist.LoadBitmaps(IDB_Go1,IDB_Go2);
			m_flexlist.RedrawWindow();
			m_up.ShowWindow(SW_HIDE);
			m_down.ShowWindow(SW_HIDE);
			SetWindowPos(NULL,0,0,520,554,SWP_NOMOVE);			
		}
}

void CMPT5Dlg::OnBnClickedExit()//退出
{
	DelHistory dh;
	if(dh.DoModal()==IDOK)
	{
		if(delh)
		{
			CStdioFile delfile;
			delfile.Open(".\\List\\EachList\\默认列表.txt",CFile::modeCreate);
			delfile.Close();
			delfile.Open(".\\List\\BreakPoint.txt",CFile::modeCreate);
			delfile.Close();
		}
		else
		{
			CStdioFile file;
			file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate|CFile::modeWrite);
			now_list+="\n";
			file.WriteString(now_list);
			m_pathname+="\n";
			file.WriteString(m_pathname);
			CString time1;//给人看的时间**：**：**\**:**:**
			m_time.GetWindowText(time1);
			time1+="\n";
			file.WriteString(time1);
			CString time2;//int型时间
			time2.Format("%d",(int)m_ctr.GetCurrentPosition());
			file.WriteString(time2);
			file.Close();
			if(m_ctr.GetCurrentPosition()==0)//如果一开始没播任何曲目或者断点时间为0，要让breakpoint.txt是空的
			{
				file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate);
				file.Close();
			}
		}
		CDialog::OnCancel();
		KillTimer(1);//一定要记住在退出程序时删除计数器,释放内存，这是个很好的习惯
	}
}
void CMPT5Dlg::OnPlay()//播放
{
	flagForward = 1;
	m_play.LoadBitmaps(IDB_Pause);
	m_play.RedrawWindow();
	OnBnClickedDelaB();//重新设置AB点
	if(m_list.GetCount()>0)//若无曲目，则不播放
	{
		CString str;
		m_list2.GetText(m_list.GetCurSel(),str);
		if(PathFileExists(str))//判断文件是否存在
		{
			if(m_pathname==str)//如果再次播放曲目还是这首，歌词要重置
			{
				m_lyric.SetWindowText("");
				counts=0;
			}
			if(m_pathname!=str)//如果再次播放曲目不是这首，歌词选框勾掉，歌词显示区隐藏
			{
				m_lyric.SetWindowText("");
				m_lyric.ShowWindow(SW_HIDE);
				m_geci.SetCheck(0);
				now_pathname="12";//这里是防止播一首歌换另一首，再换回来时歌词不显示
				counts=0;
				KillTimer(3);
			}
			m_player.SetUrl(str);
			m_pathname=str;
			m_combobox.GetLBText(m_combobox.GetCurSel(),now_list);
			
			SetTimer(1,200,NULL);//在点击播放时就创建计时器
			InitialSlider();

			
		}
		else
		{
			MessageBox("文件不存在!");
			OnBnClickedRemovefile();
		}	
	}
}

void CMPT5Dlg::OnLbnDblclkPlistbox()//双击播放
{
	OnPlay();
}
void CMPT5Dlg::OnBnClickedRemovefile()//删除文件
{
	if(m_list.GetSelCount()>0 )
	{		
		if(m_list.GetCount()==m_list.GetSelCount())//全选删除
		{
			m_list.ResetContent();
			m_list2.ResetContent();
			CString str;
			m_combobox.GetLBText(m_combobox.GetCurSel(),str);
			if(str==now_list)
				m_player.close();
		}
		if(1==m_list.GetSelCount())//选一首删除
		{
			CString nowstr;//删除曲目的路径
			m_list2.GetText(m_list.GetCurSel(),nowstr);//获得删除曲目的路径
			int index1=m_list.GetCurSel();
			if(nowstr==m_pathname)//如果正在播放
			{
				m_list2.DeleteString(m_list.GetCurSel());//这里list2放上面是因为m_list.DeleteString(m_list.GetCurSel());后
														 //	m_list.GetCurSel无效
				m_list.DeleteString(m_list.GetCurSel());
				if(index1>=m_list.GetCount())
					index1=0;
				m_list.SetSel(index1);
				OnPlay();	
			}
			else//如果不在播放
			{
				m_list2.DeleteString(m_list.GetCurSel());
				m_list.DeleteString(m_list.GetCurSel());
			}
		}
		if(m_list.GetCount()>m_list.GetSelCount()&&m_list.GetSelCount()!=1)//选一部分删除
		{
			int nCount = m_list.GetSelCount();
			int* buffer = new int[nCount];
			memset(buffer, -1, sizeof(int)*nCount);
			m_list.GetSelItems(nCount, buffer);

			CString nowstr;//删除曲目的路径
			int judge=0;//判断是否删除曲目包含正在播放
			for(int i=nCount-1; i>=0; i--)
			{
				m_list2.GetText(buffer[i],nowstr);//获得删除曲目的路径
				if(nowstr==m_pathname)
					judge=1;

				m_list.DeleteString(buffer[i]);
				m_list2.DeleteString(buffer[i]);
			}
			delete[] buffer;
			if(judge==1)	
			{
				m_list.SetSel(0);//如果删除曲目包含正在播放的，则将光标设置为0
				OnPlay();
			}
			else//将光标设为当前播放
			{
				for(int i=0;i<m_list.GetCount();i++)
				{
					CString pathname;
					m_list2.GetText(i,pathname);
					if(pathname==m_pathname)
						m_list.SetSel(i);
				}
			}
		}				
	}
	Save();

}
void CMPT5Dlg::OnBnClickedAddfile()//添加文件
{
	TCHAR Buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, Buffer);//获取当前程序路径,这里dlg.DoModal()==IDOK调用后相对路径被改变，是xp的一个bug

	char szFileFilter[]="媒体文件(*.avi,*.mp3,*.wma,*.mp4,*.rmvb,*.wav,*.wmv)|*.avi;*.mp3;*.wma;*.mp4;*.rmvb;*.wav;*.wmv|";
	CFileDialog dlg(true,NULL,NULL,OFN_FILEMUSTEXIST   |   OFN_ALLOWMULTISELECT 
		|OFN_HIDEREADONLY   |   OFN_PATHMUSTEXIST     
		|   OFN_OVERWRITEPROMPT,szFileFilter,NULL);
	TCHAR*   szPathMulti   =   new   TCHAR[8*1024*   1024];   //尽量给大些 ,据说把1024改成1023正确
	dlg.m_ofn.nMaxFile   =   8*1024*   1024; 
	dlg.m_ofn.lpstrFile   =   szPathMulti; 
	dlg.m_ofn.lpstrFile[0]   =   0; 

	if(dlg.DoModal()==IDOK)
	{  
		SetCurrentDirectory(Buffer);//重新设置相对路径
		CString every="\n";//用来记录多个重复文件的路径
		POSITION pos=dlg.GetStartPosition();
		int count=0;
		CString str1;
		while(pos!=NULL)
		{
			int count2=count;
			str1=dlg.GetNextPathName(pos);
			for(int i=0;i<m_list.GetCount();i++)
			{
				CString m_pathname2;
				m_list2.GetText(i,m_pathname2);
				if(str1==m_pathname2)
				{
					count++;    
					every+=str1;
					every+="\n";
				}
			}
			if(count2==count)
			{
				m_list2.AddString(str1);
				CString str=str1;
				str=str.Right(str.GetLength()-str.ReverseFind('\\') -1);
				m_list.AddString(str);
			}
		}		
		if(count==1)
		{
			CString str;
			str.Format("有一个文件重名\n%s",str1);
			MessageBox(str,"重名");
		}
		if(count>=2)
		{
			CString str;   
			str.Format("有%d个文件重名%s",count,every); 
			MessageBox(str,"重名");
		}

		Save();
	}
}
void CMPT5Dlg::OnBnClickedAddfolder()//添加文件夹
{
	char Dir[255]= "c:\\ "; 
	BROWSEINFO bi; 
	ITEMIDLIST* pidl; 
	bi.hwndOwner=NULL; 
	bi.pidlRoot=NULL; 
	bi.pszDisplayName=Dir; 
	bi.lpszTitle= "添加文件夹 "; 
	bi.ulFlags=BIF_RETURNONLYFSDIRS; 
	bi.lpfn=NULL; 
	bi.lParam=0; 
	bi.iImage=0; 
	pidl=SHBrowseForFolder(&bi); 
	//Display "SelectFolder "dia logbox,Getthe folder name and 
	// convertit into a ITEMLIST data structure. 
	if(pidl==NULL) 
		Dir[0]=0; 
	if(!SHGetPathFromIDList(pidl,Dir)) 
		//Retrieve folder name from ITEMLIST structure. 
		Dir[0]=0; 
	if(pidl!=NULL&&SHGetPathFromIDList(pidl,Dir))
	{
		CString str=Dir; //至此获得所选文件夹路径
		int count=0;//重复文件的个数
		int count2=0;//添加文件的数量
		CString every="\n";//用来记录多个重复文件的路径
		int amount=m_list.GetCount();//播放列表中文件个数
		getFolder(str,count,count2,every,amount);//调用查找指定文件函数

		if(count==0)
		{
			CString str;
			str.Format("添加了%d个文件",count2);
			MessageBox(str,"添加文件夹");
		}
		if(count==1)
		{
			CString str;
			str.Format("有一个文件重名\n%s\n添加了一个文件",every);
			MessageBox(str,"添加文件夹");
		}
		if(count>=2)
		{
			CString   str;   
			str.Format("有%d个文件重名%s\n添加了%d个文件",count,every,count2); 
			MessageBox(str,"添加文件夹");
		}
		Save();
	}

}
void CMPT5Dlg::getFolder(CString str,int &count,int &count2,CString &every,int amount)
{	
	CString myDataPath,fdPath;
	myDataPath=str + "\\*.*";

	CFileFind find;
	BOOL bf = find.FindFile(myDataPath);
	while(bf)
	{                        
		bf = find.FindNextFile();
		if(!find.IsDots())
		{
			fdPath=find.GetFilePath();
			if (find.IsDirectory())//如果是文件夹，递归，继续往下找
			{			                      
				getFolder(fdPath,count,count2,every,amount);  
			}
			else//如果是文件
			{
				CString suffix=fdPath.Right(fdPath.GetLength()-fdPath.ReverseFind( '.')-1); //解析后缀名
				suffix=suffix.MakeLower();//转化为小写
				if(suffix=="avi"||suffix=="mp3"||suffix=="wma"||suffix=="mp4"||suffix=="rmvb"||suffix=="wav"||suffix=="wmv")
				{	
					int judge=count;
					for(int i=0;i<amount;i++)
					{
						CString m_pathname2;
						m_list2.GetText(i,m_pathname2);
						if(fdPath==m_pathname2)
						{
							count++;    
							every+=m_pathname2;
							every+="\n";
						}
					}
					if(count==judge)
					{
						count2++;
						m_list2.AddString(fdPath);
						CString str=fdPath;
						str=str.Right(str.GetLength()-str.ReverseFind('\\') -1);
						m_list.AddString(str);
					}
				}

			}
		}
	}
	find.Close();
}
void CMPT5Dlg::OnBnClickedAddlist()//新建列表,并记录新建列表的名称
{
	NewName name;
	int count=0;
	CString str;
	str.Format("新建列表%d",m_combobox.GetCount()+1);
	name.m_newname=str;//新建列表默认名,若删除列表，则有可能默认名与已有列表重复

	if(name.DoModal()==IDOK)
	{
		if(name.m_newname=="")
		{
			MessageBox("列表名称不能为空!\n请重新输入");
			OnBnClickedAddlist();
			return;
		}
		if(name.m_newname.GetLength()>=20)
		{
			MessageBox("列表名称太长!\n请重新输入");
			OnBnClickedAddlist();
			return;
		}
		int judge=0;//判断命名是否与已有列表重复
		for(int i=0;i<m_combobox.GetCount();i++)
		{
			CString str;
			m_combobox.GetLBText(i,str);
			if(name.m_newname==str)
				judge=1;
		}
		if(judge==1)
		{
			MessageBox("与已有列表名重复!\n请重新输入");
			OnBnClickedAddlist();
			return;
		}//重名判断结束

		CString str;
		str.Format(".\\List\\EachList\\%s.txt",name.m_newname);


		CStdioFile file1;
		file1.Open(str,CFile::modeCreate);
		file1.Close();//生成新建的播放列表txt文件

		CStdioFile file2;
		int j=file2.Open(".\\List\\ListName.txt",CFile::modeWrite);
		file2.SeekToEnd(); 
		file2.WriteString("\n");//换行
		file2.WriteString(name.m_newname);
		file2.Close();//将新列表写入ListName.txt

		int index=0;
		index=m_combobox.GetCurSel();//记下当前选中的播放列表
		m_combobox.ResetContent();
		CStdioFile *fsp2=new CStdioFile(".\\List\\ListName.txt",CFile::modeRead);
		CString str2;
		while(fsp2->ReadString(str2))
		{
			m_combobox.AddString(str2);
		}
		fsp2->Close();
		delete fsp2;
		m_combobox.SetCurSel(index);//播放列表下拉菜单选中
	}
	//播放列表下拉菜单重置
}
void CMPT5Dlg::OnCbnSelchangeListcombo()//播放列表下拉菜单选择播放列表
{
	CString str;
	m_combobox.GetLBText(m_combobox.GetCurSel(),str);

	CString m_strFolderPath;
	m_strFolderPath.Format(".\\List\\EachList\\%s.txt",str);
	m_list.ResetContent();
	m_list2.ResetContent();

	CString str2;
	CStdioFile *fsp=new CStdioFile(m_strFolderPath,CFile::modeRead);

	while(fsp->ReadString(str2))
	{
		m_list2.AddString(str2);
		str2=str2.Right(str2.GetLength()-str2.ReverseFind('\\') -1);//只显示歌曲名
		m_list.AddString(str2);
	}
	fsp->Close();
	int judge=0;//判断当前列表是否有歌曲正在播放（没有播放歌曲时列表切换选中问题的解决）
	if(now_list==str)
	{
		for(int i=0;i<m_list2.GetCount();i++)
		{
			CString str1;
			m_list2.GetText(i,str1);
			if(str1==m_pathname)
			{
				judge=1;
				m_list.SetSel(i);//将光标设置为当前播放曲目		
			}

		}
	}
	else
	{
		m_list.SetSel(0);
	}
	if(judge==0)
	{
		m_list.SetSel(0);
	}
}

void CMPT5Dlg::OnBnClickedDellist()//删除列表
{
	m_player.close();
	if(m_combobox.GetCurSel()!=CB_ERR)//判断是否选中列表
	{

		CString str;	
		m_combobox.GetLBText(m_combobox.GetCurSel(),str);//获取当前选中列表

		if(str=="默认列表")
		{
			MessageBox("不能删除默认列表");
			return;
		}//注意必须有一个默认列表存在，即有一个是不能删的
		CString dstr;
		dstr.Format(".\\List\\EachList\\%s.txt",str);
		CFile dfile;
		dfile.Remove(dstr);

		CStdioFile file;
		file.Open(".\\List\\ListName.txt",CFile::modeCreate);
		file.Close();//清空列表数量.txt

		int amount=m_combobox.GetCount();//获取当前列表总数
		for(int i=0;i<amount;i++)//将除了所删列表外的列表存进列表数量.txt
		{
			CString str1;
			m_combobox.GetLBText(i,str1);//从第一个开始获取列表
			if(str!=str1)
			{

				CStdioFile file2;
				file2.Open(".\\List\\ListName.txt",CFile::modeWrite);
				file2.SeekToEnd(); 
				file2.WriteString(str1);
				if(i<amount-2)
				{
					file2.SeekToEnd(); 
					file2.WriteString("\n");//防止最后有换行符，所以i<amount-2时每个单独加换行符
				}
				file2.Close();
			}
		}//至此ListName.txt已更新

		m_combobox.ResetContent();
		CStdioFile *fsp2=new CStdioFile(".\\List\\ListName.txt",CFile::modeRead);
		CString str2;
		while(fsp2->ReadString(str2))
		{
			m_combobox.AddString(str2);
		}
		fsp2->Close();
		delete fsp2;
		now_list="默认列表";////////////////////////////////////////////////////////////////////////////
		m_combobox.SetCurSel(0);//更新列表下拉菜单,默认选中第一个


		m_list.ResetContent();
		m_list2.ResetContent();
		CStdioFile *fsp=new CStdioFile(".\\List\\EachList\\默认列表.txt",CFile::modeRead);
		CString str4;
		while(fsp->ReadString(str4))
		{
			m_list2.AddString(str4);
			str4=str4.Right(str4.GetLength()-str4.ReverseFind('\\') -1);//只显示歌曲名
			m_list.AddString(str4);
		}
		fsp->Close();
		delete fsp;
		m_list.SetSel(0);//更新列表曲目，默认选中第一个
		OnBnClickedDelaB();
		m_lyric.SetWindowText("");
		m_lyric.ShowWindow(SW_HIDE);
		m_geci.SetCheck(0);
		now_pathname="12";//这里是防止播一首歌换另一首，再换回来时歌词不显示
		counts=0;
		KillTimer(3);
	}
}

void CMPT5Dlg::OnBnClickedRenamelist()//重命名列表
{
	if(m_combobox.GetCurSel()!=CB_ERR)//判断是否选中列表
	{
		CString str;
		int index=m_combobox.GetCurSel();
		m_combobox.GetLBText(index,str);//获取当前选中列表名称
		if(str=="默认列表")
		{
			MessageBox("不能重命名默认列表");//默认列表不能重命名
			return;
		}
		NewName name;
		if(name.DoModal()==IDOK)
		{
			if(name.m_newname=="")
			{
				MessageBox("列表名称不能为空!\n请重新输入");
				OnBnClickedRenamelist();
				return;
			}
			if(name.m_newname.GetLength()>=20)
			{
				MessageBox("列表名称太长!\n请重新输入");
				OnBnClickedRenamelist();
				return;
			}
			int judge=0;//判断命名是否与已有列表重复
			for(int i=0;i<m_combobox.GetCount();i++)
			{
				CString str;
				m_combobox.GetLBText(i,str);
				if(name.m_newname==str)
					judge=1;
			}
			if(judge==1)
			{
				MessageBox("与已有列表名重复!\n请重新输入");
				OnBnClickedRenamelist();
				return;
			}//重名判断结束
			CString oldname;
			oldname.Format(".\\List\\EachList\\%s.txt",str);
			CString newname;
			newname.Format(".\\List\\EachList\\%s.txt",name.m_newname);
			CFile dfile;
			dfile.Rename(oldname,newname);//所选列表重命名


			CStdioFile file;
			file.Open(".\\List\\ListName.txt",CFile::modeCreate);
			file.Close();//清空列表数量.txt

			for(int i=0;i<m_combobox.GetCount();i++)//重命名后将各个列表重新存进列表数量.txt
			{
				CString str1;
				m_combobox.GetLBText(i,str1);//从第一个开始获取列表
				if(str!=str1)//获取的列表不是要重命名的
				{
					CStdioFile file2;
					file2.Open(".\\List\\ListName.txt",CFile::modeWrite);
					file2.SeekToEnd(); 
					file2.WriteString(str1);
					if(i<m_combobox.GetCount()-1)
					{
						file2.SeekToEnd(); 
						file2.WriteString("\n");//防止最后有换行符，所以i<m_combobox.GetCount()-1时每个单独加换行符
					}
					file2.Close();
				}
				else//获取的列表是要重命名的
				{
					CStdioFile file3;
					file3.Open(".\\List\\ListName.txt",CFile::modeWrite);
					file3.SeekToEnd(); 
					file3.WriteString(name.m_newname);
					if(i<m_combobox.GetCount()-1)
					{
						file3.SeekToEnd(); 
						file3.WriteString("\n");//防止最后有换行符，所以i<m_combobox.GetCount()-1时每个单独加换行符
					}
					file3.Close();
				}
			}//至此ListName.txt已更新，ListName相应列表名称改变

			m_combobox.ResetContent();
			CStdioFile *fsp2=new CStdioFile(".\\List\\ListName.txt",CFile::modeRead);
			CString str2;
			while(fsp2->ReadString(str2))
			{
				m_combobox.AddString(str2);
			}
			fsp2->Close();
			delete fsp2;
			m_combobox.SetCurSel(index);//更新列表下拉菜单，且选中重命名的列表
		}
	}
}
void CMPT5Dlg::OnBnClickedResetlist()//清空列表
{
	m_list.ResetContent();
	m_list2.ResetContent();
	Save();
	CString str;
	m_combobox.GetLBText(m_combobox.GetCurSel(),str);
	if(str==now_list)
		m_player.close();//如果清空的是正在播放的列表，则停止
	OnBnClickedDelaB();
	m_lyric.SetWindowText("");
	m_lyric.ShowWindow(SW_HIDE);
	m_geci.SetCheck(0);
	now_pathname="12";//这里是防止播一首歌换另一首，再换回来时歌词不显示
	counts=0;
	OnBnClickedDelaB();
	KillTimer(3);
}

void CMPT5Dlg::OnBnClickedUp()//上移曲目
{
	SetList();
	int condition=m_player.GetPlayState();
	if(m_list.GetSelCount()!=1)
		return;
	if(m_list.GetCurSel()==0)
		return;
	int index1=m_list.GetCurSel();
	int index2=index1-1;
	m_list.SetSel(index1,0);
	m_list.SetSel(index2);
	CString str;
	CString str2;
	m_list.GetText(index2,str);
	m_list2.GetText(index2,str2);//记下将要被删的曲目路径

	OnBnClickedRemovefile();//删除上一首曲目
	
	m_list.InsertString(index1,str);
	m_list2.InsertString(index1,str2);//插到播放曲目的下面
	CString str3;
	for(int i=0;i<m_list.GetCount();i++)
	{
		m_list2.GetText(i,str3);
		if(str3==m_pathname)
			m_list.SetSel(i,0);
	}
	m_list.SetSel(index2);//这时光标有两个（貌似InsertString的是看不见的？），得把播放的那个去掉，把看不见的那个明化
	Save();
	if(condition==0)
	{
		m_player.close();
		m_list.SetSel(index2);
	}//如果本来不播放的话，换了之后光标就没了，这里设置光标
}

void CMPT5Dlg::OnBnClickedDown()//下移曲目
{
	SetList();
	int condition=m_player.GetPlayState();

	if(m_list.GetSelCount()!=1)
		return;
	if(m_list.GetCurSel()==m_list.GetCount()-1)
		return;
	int index1=m_list.GetCurSel();
	int index2=index1+1;
	m_list.SetSel(index1,0);
	m_list.SetSel(index2);
	CString str;
	CString str2;
	m_list.GetText(index2,str);
	m_list2.GetText(index2,str2);//记下将要被删的曲目路径
	
	OnBnClickedRemovefile();//删除下一首曲目
	
	m_list.InsertString(index1,str);
	m_list2.InsertString(index1,str2);//插到播放曲目的上面
	CString str3;
	for(int i=0;i<m_list.GetCount();i++)
	{
		m_list2.GetText(i,str3);
		if(str3==m_pathname)
			m_list.SetSel(i,0);
	}
	m_list.SetSel(index2);//这时光标有两个（貌似InsertString的是看不见的？），得把播放的那个去掉，把看不见的那个明化
	Save();
	if(condition==0)
	{
		m_player.close();
		m_list.SetSel(index2);
	}//如果本来不播放的话，换了之后光标就没了，这里设置光标
}
void CMPT5Dlg::OnBnClickedPrevious()//上一曲
{
	SetList();
	if(m_player.GetPlayState()!=0)
	{
		int index=0;
		for(int i=0;i<m_list.GetCount();i++)
		{
			CString str;
			m_list2.GetText(i,str);
			if(str==m_pathname)
				index=i;
			else
				m_list.SetSel(i,0);
		}//记下当前播放曲目的位置
		m_player.close();
		if(index==0)
		{
			m_list.SetSel(0,0);
			m_list.SetSel(m_list.GetCount()-1);
			OnPlay();
		}
		else
		{
			m_list.SetSel(index,0);
			m_list.SetSel(index-1);
			OnPlay();
		}
	}
}

void CMPT5Dlg::OnBnClickedNext()//下一曲
{
	SetList();
	if(m_player.GetPlayState()!=0)
	{
		int index=0;
		for(int i=0;i<m_list.GetCount();i++)
		{
			CString str;
			m_list2.GetText(i,str);
			if(str==m_pathname)
				index=i;
			else
				m_list.SetSel(i,0);
		}//记下当前播放曲目的位置
		m_player.close();
		if(index==m_list.GetCount()-1)
		{
			m_list.SetSel(index,0);
			m_list.SetSel(0);
			OnPlay();
		}
		else
		{
			m_list.SetSel(index,0);
			m_list.SetSel(index+1);
			OnPlay();
		}
	}
}
//A-B两点循环播放功能
void CMPT5Dlg::OnBnClickedSetAB()
{
	int pos = 7;//起点在对话框中的横坐标
	int index=m_player.GetPlayState();//播放状态
	if(index==3)
	{
		if (flagAB == 3)
		{
			flagAB =1;
			m_setab.LoadBitmaps(IDB_SetA);
			m_setab.RedrawWindow();
		}

		if (flagAB == 1)
		{
			flagAB = 2;
			m_setab.LoadBitmaps(IDB_SetB);
			m_setab.RedrawWindow();
			lengthRate = m_ctr.GetCurrentPosition()/duration;
			pos+=(int)(length*lengthRate);
			m_marka.MoveWindow(pos,375,25,25,false);
			m_marka.ShowWindow(SW_SHOW);
			startP = m_ctr.GetCurrentPosition();
		}
		else
		{
			if(flagAB == 2)
			{
				flagAB = 1;
				m_setab.LoadBitmaps(IDB_SetA);
				m_setab.RedrawWindow();
				lengthRate = m_ctr.GetCurrentPosition()/duration;
				pos+=(int)(length*lengthRate);
				m_markb.MoveWindow(pos,375,25,25,false);
				m_markb.ShowWindow(SW_SHOW);
				endP = m_ctr.GetCurrentPosition();
				if (startP > endP)
				{
					MessageBox("起点大于终点，请重新设置。");
					OnBnClickedDelaB();
					return;
				}
				m_ctr.SetCurrentPosition(startP);
			}
		}
	}
}

void CMPT5Dlg::OnBnClickedDelaB()
{
	m_marka.ShowWindow(SW_HIDE);
	m_markb.ShowWindow(SW_HIDE);
	m_setab.LoadBitmaps(IDB_SetA);
	m_setab.RedrawWindow();
	flagAB = 3;
	startP=-1.00;
	endP = -1.00;
}



void CMPT5Dlg::OnBnClickedPause()
{
	if(m_list.GetSelCount()>0)
	{
		CString str;
		m_list2.GetText(m_list.GetCurSel(),str);
		if(m_pathname!=str)
			OnPlay();
		else
		{
			flagPause=!flagPause;
			int index=m_player.GetPlayState();//播放状态
			if (index == 3||index == 2)
			{
				if (!flagPause)
				{
					m_play.LoadBitmaps(IDB_Play1);
					m_play.RedrawWindow();
					m_ctr.pause();
				}
				else
				{
					m_play.LoadBitmaps(IDB_Pause);
					m_play.RedrawWindow();
					m_ctr.play();
				}
			}
		}
	}
}

void CMPT5Dlg::OnBnClickedFastforward()
{
	flagForward=!flagForward;
	int index=m_player.GetPlayState();//播放状态
	if(index == 3||index == 4)
	{
		if (!flagForward)
		{
			m_ctr.fastForward();
		}
		else
		{
			m_ctr.play();
		}
	}
	int a = flagForward;
}

void CMPT5Dlg::OnBnClickedStop()
{
	m_play.LoadBitmaps(IDB_Play1);
	m_play.RedrawWindow();
	m_player.close();
	m_pathname="0";
	m_lyric.SetWindowText("");
	m_lyric.ShowWindow(SW_HIDE);
	m_geci.SetCheck(0);
	counts=0;
}

BOOL CMPT5Dlg::PreTranslateMessage(MSG* pMsg)
{
		m_tooltip.RelayEvent(pMsg);
		if (m_list.GetCount()>0)
		{
			MessageTips();
		}

	return CDialog::PreTranslateMessage(pMsg);
}

void CMPT5Dlg::MessageTips()
{
	CPoint point;
	CString strTxt;

	GetCursorPos(&point); //取得当前鼠标的坐标
	if (::WindowFromPoint(point)==m_list) //从当前鼠标的坐标获得鼠标所在窗口的句柄，并判断是否为LISTBOX控件 
		m_list.ScreenToClient(&point);  //由 于GetCursorPos函数返回的是相对于整个屏幕的坐标值，因此需要把这个坐标值转换成相对于ListBox 的坐标.
	BOOL bIn;
	int nNindex=m_list.ItemFromPoint (point  ,bIn);//从鼠标坐标获得鼠标目前所在的LISTBOX项目索引
	m_list2.GetText(nNindex,strTxt);//获得n项目的路径
	/////////////////////////////获得信息/////////////////////////////////////////////
	CString name = _T(strTxt);
	m_media = static_cast<CWMPMedia>(m_player.newMedia(name));  
	CString strMsg = _T("");
	long lCount =m_media.GetAttributeCount();
	for (long i = 0; i < lCount; i++)
	{
		strMsg.AppendFormat(_T("%s:%s\r\n"), m_media.getAttributeName(i), m_media.getItemInfo(m_media.getAttributeName(i)));
	}
	//////////////////////////////////////////////////////////////////////////
	if (!bIn)  
	{
		m_tooltip.UpdateTipText(strMsg,GetDlgItem(IDC_PListBox) );
	}
	else
		m_tooltip.UpdateTipText("",GetDlgItem(IDC_PListBox) );
}


void CMPT5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1)
	{
		///////////////////////播放模式//////////////////////////////////
		int index=m_player.GetPlayState();//播放状态
		if(index==1)//如果播放完成
		{	
			SetList();//如果播放的列表和当前列表不一致，转换列表
			CString playmode;
			m_combobox2.GetLBText(m_combobox2.GetCurSel(),playmode);//获取播放模式
			if(playmode=="顺序播放")//顺序播放
			{
				OnBnClickedDelaB();
				int index=0;
				for(int i=0;i<m_list.GetCount();i++)
				{
					CString str;
					m_list2.GetText(i,str);
					if(str==m_pathname)
						index=i;
					else
						m_list.SetSel(i,0);
				}//记下当前播放曲目的位置
				index++;
				if(index>=m_list.GetCount()) 
				{
					index=0;//如果播放完最后一曲
					m_play.LoadBitmaps(IDB_Play1);
					m_play.RedrawWindow();
					m_list.SetSel(index-1,0);
					m_list.SetSel(index);//自动置光标
					m_player.close();
				}		
				else
				{
					m_list.SetSel(index-1,0);
					m_list.SetSel(index);//自动置光标
					CString str;
					m_list2.GetText(index,str);
					if(PathFileExists(str))
					{
						if(m_pathname==str)//如果再次播放曲目还是这首，歌词要重置
						{
							m_lyric.SetWindowText("");
							counts=0;
						}
						if(m_pathname!=str)//如果再次播放曲目不是这首，歌词选框勾掉，歌词显示区隐藏
						{
							m_lyric.SetWindowText("");
							m_lyric.ShowWindow(SW_HIDE);
							m_geci.SetCheck(0);
							now_pathname="12";//这里是防止播一首歌换另一首，再换回来时歌词不显示
							counts=0;
							KillTimer(3);
						}
						m_player.SetUrl(str);
						m_pathname=str;
						InitialSlider();	
					}
					else
						OnBnClickedRemovefile();
				}
				
			}
			if(playmode=="列表循环")//如果是列表循环播放
			{
				OnBnClickedDelaB();
				int index=0;
				for(int i=0;i<m_list.GetCount();i++)
				{
					CString str;
					m_list2.GetText(i,str);
					if(str==m_pathname)
						index=i;
					else
						m_list.SetSel(i,0);//这里所应对的情况是在播放一首曲目，然后选中另一首或零几首，这首放完时要把选中的光标都清掉
				}//记下当前播放曲目的位置
				index++;
				if(index>=m_list.GetCount()) 
					index=0;//如果播放完最后一曲
				m_list.SetSel(index-1,0);
				m_list.SetSel(index);//自动置光标
				CString str;
				m_list2.GetText(index,str);
				if(PathFileExists(str))
				{
					if(m_pathname==str)//如果再次播放曲目还是这首，歌词要重置
					{
						m_lyric.SetWindowText("");
						counts=0;
					}
					if(m_pathname!=str)//如果再次播放曲目不是这首，歌词选框勾掉，歌词显示区隐藏
					{
						m_lyric.SetWindowText("");
						m_lyric.ShowWindow(SW_HIDE);
						m_geci.SetCheck(0);
						now_pathname="12";//这里是防止播一首歌换另一首，再换回来时歌词不显示
						counts=0;
						KillTimer(3);
					}
					m_player.SetUrl(str);
					m_pathname=str;
					InitialSlider();
				}
				else
					OnBnClickedRemovefile();
				
			}//这样就实现了列表循环播放
			if(playmode=="随机播放")//随机播放
			{
				OnBnClickedDelaB();
				for(int i=0;i<m_list.GetCount();i++)
				{
					CString str;
					m_list2.GetText(i,str);
					if(str!=m_pathname)
						m_list.SetSel(i,0);//这里所应对的情况是在播放一首曲目，然后选中另一首或零几首，这首放完时要把选中的光标都清掉
				}
				srand(time(0));//目的在于每次都能产生不同的随机数序列
				int num=rand()%m_list.GetCount();
				m_list.SetSel(m_list.GetCurSel(),0);
				m_list.SetSel(num);//随机置光标	
				CString str;
				m_list2.GetText(num,str);
				if(PathFileExists(str))
				{
					if(m_pathname==str)//如果再次播放曲目还是这首，歌词要重置
					{
						m_lyric.SetWindowText("");
						counts=0;
					}
					if(m_pathname!=str)//如果再次播放曲目不是这首，歌词选框勾掉，歌词显示区隐藏
					{
						m_lyric.SetWindowText("");
						m_lyric.ShowWindow(SW_HIDE);
						m_geci.SetCheck(0);
						now_pathname="12";//这里是防止播一首歌换另一首，再换回来时歌词不显示
						counts=0;
						KillTimer(3);
					}
					m_player.SetUrl(str);
					m_pathname=str;
					InitialSlider();
				}
				else
					OnBnClickedRemovefile();
				
			}
			if(playmode=="单曲循环")//单曲循环
			{
				OnBnClickedDelaB();
				for(int i=0;i<m_list.GetCount();i++)
				{
					CString str;
					m_list2.GetText(i,str);
					if(str!=m_pathname)
						m_list.SetSel(i,0);//这里所应对的情况是在播放一首曲目，然后选中另一首或零几首，这首放完时要把选中的光标都清掉
					else
						m_list.SetSel(i);
				}
				m_player.SetUrl(m_pathname);
				InitialSlider();
				counts=0;
			}
		}
		//////////////////两点播放////////////////////////

		if (static_cast<int>(m_ctr.GetCurrentPosition()) == static_cast<int>(endP))
		{
			m_ctr.SetCurrentPosition(startP);
			m_slider.SetPos((int)startP);
		}
		//////////////////滑动进度条/////////////
		sliderPos =(int)m_ctr.GetCurrentPosition();
		m_slider.SetPos(sliderPos);
		m_time.SetWindowText(StandardTime((int)m_slider.GetPos(),(int)duration));
		CDialog::OnTimer(nIDEvent);

		/////////////////歌词///////////////////

	}
	if(nIDEvent==2)
	{
		KillTimer(2);
		BreakPoint BP;
		CStdioFile *fsp=new CStdioFile(".\\List\\BreakPoint.txt",CFile::modeRead);
		CString listname;
		if(0==fsp->ReadString(listname))//如果breakpoint.txt是空的，不跳断点对话框
		{
			fsp->Close();
			return;
		}
		CString songname;
		fsp->ReadString(songname);		
		CString time1;
		fsp->ReadString(time1);	
		CString time2;
		fsp->ReadString(time2);
		fsp->Close();
		delete fsp;	
		CString str;
		str+=listname;
		str+="\r\n";
		str+=songname;
		str+="\r\n";
		str+=time1;
		BP.m_bp=str;
		if(BP.DoModal()==IDOK)//如果选择断点续播
		{
			for(int i=0;i<m_combobox.GetCount();i++)
			{
				CString str1;
				m_combobox.GetLBText(i,str1);
				if(str1==listname)
				{
					m_combobox.SetCurSel(i);
					now_list=listname;
					break;
				}
			}//转换播放列表
			CString m_strFolderPath;
			m_strFolderPath.Format(".\\List\\EachList\\%s.txt",now_list);
			m_list.ResetContent();
			m_list2.ResetContent();

			CString str2;
			CStdioFile *fsp=new CStdioFile(m_strFolderPath,CFile::modeRead);
			while(fsp->ReadString(str2))
			{
				m_list2.AddString(str2);
				str2=str2.Right(str2.GetLength()-str2.ReverseFind('\\') -1);//只显示歌曲名
				m_list.AddString(str2);
			}
			fsp->Close();//然后刷新播放列表
			for(int j=0;j<m_list.GetCount();j++)
			{
				CString str2;
				m_list2.GetText(j,str2);
				if(str2==songname)
				{
					m_list.SetSel(j);
					m_pathname=songname;
					if(PathFileExists(m_pathname))
					{
						m_play.LoadBitmaps(IDB_Pause);
						m_play.RedrawWindow();
						m_player.SetUrl(m_pathname);
						InitialSlider();
						int time=atof(time2);
						m_ctr.SetCurrentPosition((double)time);
						m_slider.SetPos(time);
						SetTimer(1,200,NULL);
					}
					else
						OnBnClickedRemovefile();
					break;
				}
			}
		}
	}
	if(nIDEvent==3)
	{	
		if(m_ctr.GetCurrentPosition()>=dtime[counts])//输出歌词
		{
			m_lyric.SetWindowText(strcontainer[counts]);
			counts++;
		}
		if(counts>=1)
		{
			while(m_ctr.GetCurrentPosition()<dtime[counts-1])//响应往回拖动
			{
				counts--;
			}
		}
		while(m_ctr.GetCurrentPosition()>dtime[counts+1])//响应往后拖动
		{
			counts++;
			if(dtime[counts]==0)
			{
				counts--;
				break;
			}
		}
	
	}
}

void CMPT5Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	UINT count;
	char filePath[200];

	count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	int index=m_list.GetCount();
	if(count)
	{ 
		int count1=0;//重复文件的个数
		CString every;//重复文件的路径  
		int count3=0;//不支持格式的文件的个数
		for(UINT i=0; i<count; i++)
		{
			
			int pathLen = DragQueryFile(hDropInfo, i, filePath, sizeof(filePath));

			CString str = filePath;
			str = str.Right(str.GetLength()-str.ReverseFind( '.')-1); 
			str= str.MakeLower();
			CString str1=filePath;
			CString pathname;
			if (str=="mp3"||str=="mp4"||str=="avi"||str=="wma"||str=="wav"||str=="rmvb")
			{		
				int judge=0;//判断重复
				for(int i=0;i<m_list.GetCount();i++)
				{
					m_list2.GetText(i,pathname);
					if(pathname==str1)
					{
						judge=1;
						count1++;
						every+=pathname;
						every+="\n";
					}			
				}
				if(judge==0)
				{
					m_list2.AddString(str1);
					str1=str1.Right(str1.GetLength()-str1.ReverseFind( '\\')-1); 
					m_list.AddString(str1);
				}
			}
			else
			{
				count3++;
			}
		}
		if(count3>0)
		{
			CString str2;
			str2.Format("有%d个文件格式不支持!",count3);
			MessageBox(str2,"拖放文件");	
		}
		if(count1==0)//没有重复
		{
			CString str2;
			str2.Format("添加了%d个文件",count-count3);
			MessageBox(str2,"拖放文件");		
		}
		else
		{
			CString str2;
			str2.Format("有%d个文件重复\n%s\n添加了%d个文件",count1,every,count-count1-count3);
			MessageBox(str2,"拖放文件");
		}
	}
	Save();
	DragFinish(hDropInfo);

	CDialog::OnDropFiles(hDropInfo);
}

void CMPT5Dlg::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	sliderPos = m_slider.GetPos();
	m_ctr.SetCurrentPosition(sliderPos);
	m_slider.SetPos(sliderPos);
	UpdateData(FALSE);
	if (startP!=-1&&endP!=-1 )
	{
		if (m_ctr.GetCurrentPosition() > endP||m_ctr.GetCurrentPosition() < startP)
		{
			OnBnClickedDelaB();
		}
	}

	*pResult = 0;
	SetFocus();
}
//新建一个初始化滑动条的函数，并在各个播放模式中添加。
void CMPT5Dlg::InitialSlider()
{	
	m_media = static_cast<CWMPMedia>(m_player.newMedia(m_pathname));
	m_slider.SetPos(0);//滑动进度条初始化
	duration = m_media.GetDuration();
	m_time.SetWindowText(StandardTime(0,(int)duration));//显示总时长
	m_slider.SetRange(0,(int)duration);
}
CString CMPT5Dlg::StandardTime(int now,int total)
{
	CString time;
	int nhour=now/3600;
	int nminute=(now-nhour*3600)/60;
	int nsecond=now-nhour*3600-nminute*60;
	int thour=total/3600;
	int tminute=(total-thour*3600)/60;
	int tsecond=total-thour*3600-tminute*60;
	time.Format("%02d:%02d:%02d/%02d:%02d:%02d",nhour,nminute,nsecond,thour,tminute,tsecond);
	return time;
}


void CMPT5Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)//音量调节
{
	int m_nCur;
	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	m_nCur=pSlidCtrl->GetPos();//取得当前位置值
	if (!m_settings.GetMute())
	{
		m_settings.SetVolume(-m_nCur);
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	SetFocus();
}

void CMPT5Dlg::OnBnClickedButton1()//静音
{
	if(m_settings.GetMute())
	{
		m_mute.LoadBitmaps(IDB_Volume1,IDB_Volume2);
		m_mute.RedrawWindow();
		int m_nCur;
		CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
		m_nCur=pSlidCtrl->GetPos();
		m_settings.SetVolume(-m_nCur);
		m_settings.SetMute(FALSE);
	}
	else
	{
		m_mute.LoadBitmaps(IDB_Volume_Mute1,IDB_Volume_Mute2);
		m_mute.RedrawWindow();
		
		m_settings.SetMute(TRUE);
		
	}
}
void CMPT5Dlg::AboutUs()
{
	About us;
	us.DoModal();
}
void CMPT5Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	sliderPos=m_slider.GetPos();
	m_ctr.SetCurrentPosition(sliderPos);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
bool CMPT5Dlg::ReadLyricsFile(CString str)//将歌曲名当做参数传入  
{  
	str=str.Right(str.GetLength()-str.ReverseFind('\\') -1);//只显示歌曲名
	str=str.Left(str.GetLength()-4);
	CString sn;
	sn.Format(".\\List\\Lyrics\\%s.lrc",str);
	CStdioFile file;
	if(!file.Open(sn,CFile::modeRead))
	{
		MessageBox("歌词文件不存在!");
		m_geci.SetCheck(0);
		return 0;
	}//如果歌词文件不存在，就return	
	now_pathname=m_pathname;//记下歌词曲目
    m_lyric.ShowWindow(SW_SHOW);
	CString strline;//每一行的时间以及歌词
	CString time;//时间
	CString lr;//歌词
	CStringArray tagcontainer;//存所有时间标签
    strcontainer.RemoveAll();
	while(file.ReadString(strline))//如果不是空串，并且没有到末尾，就读出这一行
	{
		lr = strline.Right(strline.GetLength()-strline.ReverseFind( ']')-1); 
		if(lr!="")//如果歌词不是空串，前面肯定有时间标签
		{     
			time=strline.Left(strline.Find(']')+1);
			tagcontainer.Add(time);//加第一个时间标签
			strcontainer.Add(lr);//加本行歌词
			strline=strline.Left(strline.GetLength()-lr.GetLength());//取strline除去歌词的部分，即只有时间标签
			while(1)
			{
				strline=strline.Right(strline.GetLength()-strline.Find(']')-1);
				if(strline=="")
					break;
				time=strline.Left(strline.Find(']')+1);
				tagcontainer.Add(time);//加时间标签
				strcontainer.Add(lr);//加本行歌词
			}
		}//至此一行的时间标签和歌词提取完毕
	}//至此所有时间标签和歌词提取完毕
	file.Close();
	for(int i=0;i<tagcontainer.GetSize();i++)//把时间标签转化为double型的时间
	{
		dtime[i]=((int)(tagcontainer[i][1])-48)*600+((int)(tagcontainer[i][2])-48)*60+((int)(tagcontainer[i][4])-48)*10+
			(int)(tagcontainer[i][5])-48+((double)(tagcontainer[i][7])-48)*0.1+((double)(tagcontainer[i][8])-48)*0.01;
	}//时间已经转化为double了
	for(int i=0;i<strcontainer.GetUpperBound();i++)//一共换这么多次
	{
		for(int j=strcontainer.GetUpperBound();j-i>0;j--)//每次比较这么多次
		{
			if(dtime[j]<dtime[j-1])
			{
				double temptime=dtime[j];
				dtime[j]=dtime[j-1];
				dtime[j-1]=temptime;
				CString tempstr=strcontainer[j];
				strcontainer[j]=strcontainer[j-1];
				strcontainer[j-1]=tempstr;
			}
		}
	}//歌词排序完成
	return 1;
}  
void CMPT5Dlg::OnBnClickedCheck1()//是否显示歌词的勾选框
{   
	if(m_list.GetCount()>0)
	{
		if((((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck()))
		{
			if(now_pathname==m_pathname)
			{
				m_lyric.ShowWindow(SW_SHOW);
				return;
			}
			CString str;
			str=m_pathname.Right(m_pathname.GetLength()-m_pathname.ReverseFind( '.')-1); //解析后缀名
			if(str=="mp3"||str=="wma"||str=="wmv")//判断是否是音频格式
			{
				counts=0;

				if(m_player.GetPlayState()==3)
				{
					if(ReadLyricsFile(m_pathname))
					{
						while(m_ctr.GetCurrentPosition()>=dtime[counts])
						{
							counts++;
						}//这里歌词变成了后一句
						counts--;
						//先将歌词调到那一句
						if(counts<0)
							counts++;
						SetTimer(3,100,NULL);
					}
				}
				else
				{
					CString s;
					m_list.GetText(m_list.GetCurSel(),s);
					if(ReadLyricsFile(s))
					{
						SetTimer(3,100,NULL);
					}
				}
			}
			else
				m_geci.SetCheck(0);
		}
		else
		{
			m_lyric.ShowWindow(SW_HIDE);
		}
	}
	else
		m_geci.SetCheck(0);
}

HBRUSH CMPT5Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(pWnd == GetDlgItem(IDC_SLIDER1))
	{
		return (HBRUSH) CreateSolidBrush(RGB(218,218,218));
	}
	if(pWnd == GetDlgItem(IDC_CHECK1))
	{
		return (HBRUSH) CreateSolidBrush(RGB(42,48,58));
	}
	if(pWnd == GetDlgItem(IDC_SLIDER2))
	{
		return (HBRUSH) CreateSolidBrush(RGB(42,48,58));
	}

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}
