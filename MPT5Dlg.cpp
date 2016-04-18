// MPT5Dlg.cpp : ʵ���ļ�
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
#include <shlwapi.h>//�ж��ļ��Ƿ���ڵ�ͷ�ļ�
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int hide_button;//���ƹ��ܰ�ť����������
int hide_list=0;//���Ʋ����б����������
CString m_pathname;//��ǰ������Ŀ��·��
CString now_list;//��¼��ǰ�����б�
const int length = 338;//����������
bool lyrics=0;//ȷ������Ƿ���ʾ
CString now_pathname="12";//��ǰ���ڲ��Ÿ�ʵ���Ŀ
bool delh=0;//���źۼ������

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMPT5Dlg �Ի���




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
	this->ShowWindow(SW_SHOW);//�򵥵���ʾ���������¶�  
	DeleteTray();
}
LRESULT CMPT5Dlg::Handler(WPARAM wParam,LPARAM lParam)
{
	ToTray();
	return 0;
}
LRESULT CMPT5Dlg::Handler1(WPARAM wParam,LPARAM lParam)//�ر�
{
	CStdioFile file;
	int j=file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate|CFile::modeWrite);
	now_list+="\n";
	file.WriteString(now_list);
	m_pathname+="\n";
	file.WriteString(m_pathname);
	CString time1;//���˿���ʱ��**��**��**\**:**:**
	m_time.GetWindowText(time1);
	time1+="\n";
	file.WriteString(time1);
	CString time2;//int��ʱ��
	time2.Format("%d",(int)m_ctr.GetCurrentPosition());
	file.WriteString(time2);
	file.Close();
	if(m_ctr.GetCurrentPosition()==0)//���һ��ʼû���κ���Ŀ���߶ϵ�ʱ��Ϊ0��Ҫ��breakpoint.txt�ǿյ�
	{
		file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate);
		file.Close();
	}
	CDialog::OnCancel();
	KillTimer(1);//һ��Ҫ��ס���˳�����ʱɾ��������,�ͷ��ڴ棬���Ǹ��ܺõ�ϰ��
	return 0;
}
LRESULT CMPT5Dlg::Handler2(WPARAM wParam,LPARAM lParam)
{
	delh=1;
	return 0;
}

// CMPT5Dlg ��Ϣ�������

BOOL CMPT5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	startP = -1;
	endP = -1;
	flagAB = 3;//��ʾ�������㲥��

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

		
	EnableToolTips(TRUE);//enable use it
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.SetTipTextColor(RGB(0,0,0));//������ɫ
	m_tooltip.SetDelayTime(TTDT_INITIAL, 10); //���ָ���ú���ʾ��ʾ������
	m_tooltip.SetDelayTime(TTDT_AUTOPOP, 2000); //��걣��ָ����ʾ��ʾ��ã�����
	m_tooltip.SetMaxTipWidth(200);//�趨��ʾ��ȣ����������Զ�����
	m_tooltip.SetTipBkColor( RGB(255,255,255)); //������ʾ��ı�����ɫ
	//////////////////////��ť��ʾ/////////////////////////////
	m_tooltip.AddTool(GetDlgItem(IDC_SetAB), (LPCTSTR)"����A-B��");
	m_tooltip.AddTool(GetDlgItem(IDC_AddFile), (LPCTSTR)"����ļ�");
	m_tooltip.AddTool(GetDlgItem(IDC_AddList), (LPCTSTR)"����б�");
	m_tooltip.AddTool(GetDlgItem(IDC_DelAB), (LPCTSTR)"�˳����㲥��ģʽ");
	m_tooltip.AddTool(GetDlgItem(IDC_DelList), (LPCTSTR)"ɾ���б�");
	m_tooltip.AddTool(GetDlgItem(IDC_ReNameList),(LPCTSTR) "�������б�");
	m_tooltip.AddTool(GetDlgItem(IDC_ResetList),(LPCTSTR) "����б�");
	m_tooltip.AddTool(GetDlgItem(IDC_RemoveFile),(LPCTSTR) "�Ƴ��ļ�");
	m_tooltip.AddTool(GetDlgItem(IDC_AddFolder), (LPCTSTR)"����ļ���");
	m_tooltip.AddTool(GetDlgItem(IDC_Stop), (LPCTSTR)"ֹͣ����");
	m_tooltip.AddTool(GetDlgItem(IDC_Pause), (LPCTSTR)"����/��ͣ");
	m_tooltip.AddTool(GetDlgItem(IDC_FastForward), (LPCTSTR)"�������");
	m_tooltip.AddTool(GetDlgItem(IDC_Previous), (LPCTSTR)"��һ��");
	m_tooltip.AddTool(GetDlgItem(IDC_Next), (LPCTSTR)"��һ��");
	m_tooltip.AddTool(GetDlgItem(IDC_List), (LPCTSTR)"չ��/���ز����б�");
	m_tooltip.AddTool(GetDlgItem(IDC_ListCombo), (LPCTSTR)"ѡ�񲥷��б�");
	m_tooltip.AddTool(GetDlgItem(IDC_ModeCombo), (LPCTSTR)"ѡ�񲥷�ģʽ");
	m_tooltip.AddTool(GetDlgItem(IDC_Exit), (LPCTSTR)"�˳�������");
	m_tooltip.AddTool(GetDlgItem(IDC_Up), (LPCTSTR)"���ϵ���");
	m_tooltip.AddTool(GetDlgItem(IDC_Down), (LPCTSTR)"���µ���");
	m_tooltip.AddTool (GetDlgItem(IDC_PListBox),(LPCTSTR)"");
	m_tooltip.AddTool (GetDlgItem(IDC_BUTTON1),(LPCTSTR)"����");
	/////////////////////////��ť��ͼ//////////////////////////////////
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

	if(!PathIsDirectory(".\\List"))//�ʼʹ��ʱ�Խ��ļ�
	{
		CreateDirectory(".\\List",NULL);
		CreateDirectory(".\\List\\EachList",NULL);
		CreateDirectory(".\\List\\Lyrics",NULL);
		CStdioFile file;
		int k=file.Open(".\\List\\ListName.txt",CFile::modeCreate|CFile::modeWrite);
		file.WriteString("Ĭ���б�");
		file.Close();
		file.Open(".\\List\\EachList\\Ĭ���б�.txt",CFile::modeCreate);
		file.Close();
		file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate);
		file.Close();
	}
	else
		SetTimer(2,500,NULL);//������������Ϊһ��ʼbreakpoint.txt�ǿյ�
	m_list.SetHorizontalExtent(500);
	CStdioFile *fsp1=new CStdioFile(".\\List\\EachList\\Ĭ���б�.txt",CFile::modeRead);
	CString str1;
	while(fsp1->ReadString(str1))
	{
		m_list2.AddString(str1);
		str1=str1.Right(str1.GetLength()-str1.ReverseFind('\\') -1);//ֻ��ʾ������
		m_list.AddString(str1);
	}
	fsp1->Close();
	delete fsp1;
	m_list.SetSel(0);
	m_list2.SetSel(0);//���벥���б�

	CStdioFile *fsp2=new CStdioFile(".\\List\\ListName.txt",CFile::modeRead);
	CString str2;
	while(fsp2->ReadString(str2))
	{
		m_combobox.AddString(str2);
	}
	fsp2->Close();
	delete fsp2;
	m_combobox.SetCurSel(0);
	now_list="Ĭ���б�";//���벥���б�����

	m_combobox2.AddString("˳�򲥷�");
	m_combobox2.AddString("�б�ѭ��");
	m_combobox2.AddString("����ѭ��");
	m_combobox2.AddString("�������");
	m_combobox2.SetCurSel(0);//Ĭ�ϲ���ģʽΪ˳�򲥷�

	m_ctr = m_player.GetControls();

	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	pSlidCtrl->SetRange(-100,0,TRUE);//���û�������Χ
	pSlidCtrl->SetPos(-66);//���û�����λ��
	m_settings = m_player.GetSettings();
    
	counts=0;
	for(int i=0;i<100;i++)
		dtime[i]=0;
	m_lyric.ShowWindow(SW_HIDE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CMPT5Dlg::ToTray()//����������
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDI_MPT5ICON;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ���� 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_MPT5ICON));
	strcpy(nid.szTip,"MPT5");    //��Ϣ��ʾ�� 
	Shell_NotifyIcon(NIM_ADD,&nid);    //�����������ͼ��
	ShowWindow(SW_HIDE);    //����������
}
void CMPT5Dlg::DeleteTray()//ɾ������ͼ��
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDI_MPT5ICON;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;          //�Զ������Ϣ���� 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_MPT5ICON));
	strcpy(nid.szTip,"MPT5");    //��Ϣ��ʾ��Ϊ���ƻ��������ѡ�   
	Shell_NotifyIcon(NIM_DELETE,&nid);    //��������ɾ��ͼ�� 
}
LRESULT CMPT5Dlg::OnShowTask(WPARAM wParam,LPARAM lParam)//����
{
	if(wParam!=IDI_MPT5ICON) 
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵���
		{
			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);//�õ����λ��
			CMenu menu;
			menu.LoadMenu(IDR_MENU2); 
			menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); //ȷ������ʽ�˵���λ��                 
			HMENU hmenu=menu.Detach(); 
			menu.DestroyMenu(); //��Դ���� 
			delete lpoint; 
			//DeleteTray();
		}  break;
	case WM_LBUTTONDBLCLK:      //˫������Ĵ��� 
		{ 
			this->ShowWindow(SW_SHOW);//�򵥵���ʾ���������¶�  
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMPT5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMPT5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMPT5Dlg::Save()//�Զ�����
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
		strtemp+="\n";//��Ҫ����
		file.WriteString(strtemp);	
	}
	file.Close();
}

void CMPT5Dlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	CRect rect;//�����������

	GetDlgItem(IDC_PListBox)->GetWindowRect(&rect);//��ȡ�ؼ�����ľ���
	if(rect.PtInRect(point))
	{
		CMenu   menu;  
		VERIFY(menu.LoadMenu(IDR_MENU3));  
		CMenu*   pPopup=menu.GetSubMenu(0);  
		ASSERT(pPopup!=NULL); 
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this); //����굱ǰλ����ʾָ���˵�
	}
}
void CMPT5Dlg::SetList()//���ó����ڲ��ŵ��б�
{
	CString str;
	m_combobox.GetLBText(m_combobox.GetCurSel(),str);
	if(str!=now_list)//������ŵ��б�͵�ǰ�б�һ�£�ת���б�
	{
		for(int i=0;i<m_combobox.GetCount();i++)
		{
			m_combobox.GetLBText(i,str);
			if(str==now_list)
				m_combobox.SetCurSel(i);
		}//���Զ��������ڲ��ŵ��б�
		CString m_strFolderPath;
		m_strFolderPath.Format(".\\List\\EachList\\%s.txt",now_list);
		m_list.ResetContent();
		m_list2.ResetContent();

		CString str2;
		CStdioFile *fsp=new CStdioFile(m_strFolderPath,CFile::modeRead);
		while(fsp->ReadString(str2))
		{
			m_list2.AddString(str2);
			str2=str2.Right(str2.GetLength()-str2.ReverseFind('\\') -1);//ֻ��ʾ������
			m_list.AddString(str2);
		}
		fsp->Close();//Ȼ��ˢ�²����б�

		for(int i=0;i<m_list2.GetCount();i++)
		{
			CString str3;
			m_list2.GetText(i,str3);
			if(str3==m_pathname)
			{
				m_list.SetSel(i);
				m_list2.SetSel(i);
			}
		}//���������Ϊ��ǰ������Ŀ
	}
}
void CMPT5Dlg::OnBnClickedList()//�����б����������
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

void CMPT5Dlg::OnBnClickedExit()//�˳�
{
	DelHistory dh;
	if(dh.DoModal()==IDOK)
	{
		if(delh)
		{
			CStdioFile delfile;
			delfile.Open(".\\List\\EachList\\Ĭ���б�.txt",CFile::modeCreate);
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
			CString time1;//���˿���ʱ��**��**��**\**:**:**
			m_time.GetWindowText(time1);
			time1+="\n";
			file.WriteString(time1);
			CString time2;//int��ʱ��
			time2.Format("%d",(int)m_ctr.GetCurrentPosition());
			file.WriteString(time2);
			file.Close();
			if(m_ctr.GetCurrentPosition()==0)//���һ��ʼû���κ���Ŀ���߶ϵ�ʱ��Ϊ0��Ҫ��breakpoint.txt�ǿյ�
			{
				file.Open(".\\List\\BreakPoint.txt",CFile::modeCreate);
				file.Close();
			}
		}
		CDialog::OnCancel();
		KillTimer(1);//һ��Ҫ��ס���˳�����ʱɾ��������,�ͷ��ڴ棬���Ǹ��ܺõ�ϰ��
	}
}
void CMPT5Dlg::OnPlay()//����
{
	flagForward = 1;
	m_play.LoadBitmaps(IDB_Pause);
	m_play.RedrawWindow();
	OnBnClickedDelaB();//��������AB��
	if(m_list.GetCount()>0)//������Ŀ���򲻲���
	{
		CString str;
		m_list2.GetText(m_list.GetCurSel(),str);
		if(PathFileExists(str))//�ж��ļ��Ƿ����
		{
			if(m_pathname==str)//����ٴβ�����Ŀ�������ף����Ҫ����
			{
				m_lyric.SetWindowText("");
				counts=0;
			}
			if(m_pathname!=str)//����ٴβ�����Ŀ�������ף����ѡ�򹴵��������ʾ������
			{
				m_lyric.SetWindowText("");
				m_lyric.ShowWindow(SW_HIDE);
				m_geci.SetCheck(0);
				now_pathname="12";//�����Ƿ�ֹ��һ�׸軻��һ�ף��ٻ�����ʱ��ʲ���ʾ
				counts=0;
				KillTimer(3);
			}
			m_player.SetUrl(str);
			m_pathname=str;
			m_combobox.GetLBText(m_combobox.GetCurSel(),now_list);
			
			SetTimer(1,200,NULL);//�ڵ������ʱ�ʹ�����ʱ��
			InitialSlider();

			
		}
		else
		{
			MessageBox("�ļ�������!");
			OnBnClickedRemovefile();
		}	
	}
}

void CMPT5Dlg::OnLbnDblclkPlistbox()//˫������
{
	OnPlay();
}
void CMPT5Dlg::OnBnClickedRemovefile()//ɾ���ļ�
{
	if(m_list.GetSelCount()>0 )
	{		
		if(m_list.GetCount()==m_list.GetSelCount())//ȫѡɾ��
		{
			m_list.ResetContent();
			m_list2.ResetContent();
			CString str;
			m_combobox.GetLBText(m_combobox.GetCurSel(),str);
			if(str==now_list)
				m_player.close();
		}
		if(1==m_list.GetSelCount())//ѡһ��ɾ��
		{
			CString nowstr;//ɾ����Ŀ��·��
			m_list2.GetText(m_list.GetCurSel(),nowstr);//���ɾ����Ŀ��·��
			int index1=m_list.GetCurSel();
			if(nowstr==m_pathname)//������ڲ���
			{
				m_list2.DeleteString(m_list.GetCurSel());//����list2����������Ϊm_list.DeleteString(m_list.GetCurSel());��
														 //	m_list.GetCurSel��Ч
				m_list.DeleteString(m_list.GetCurSel());
				if(index1>=m_list.GetCount())
					index1=0;
				m_list.SetSel(index1);
				OnPlay();	
			}
			else//������ڲ���
			{
				m_list2.DeleteString(m_list.GetCurSel());
				m_list.DeleteString(m_list.GetCurSel());
			}
		}
		if(m_list.GetCount()>m_list.GetSelCount()&&m_list.GetSelCount()!=1)//ѡһ����ɾ��
		{
			int nCount = m_list.GetSelCount();
			int* buffer = new int[nCount];
			memset(buffer, -1, sizeof(int)*nCount);
			m_list.GetSelItems(nCount, buffer);

			CString nowstr;//ɾ����Ŀ��·��
			int judge=0;//�ж��Ƿ�ɾ����Ŀ�������ڲ���
			for(int i=nCount-1; i>=0; i--)
			{
				m_list2.GetText(buffer[i],nowstr);//���ɾ����Ŀ��·��
				if(nowstr==m_pathname)
					judge=1;

				m_list.DeleteString(buffer[i]);
				m_list2.DeleteString(buffer[i]);
			}
			delete[] buffer;
			if(judge==1)	
			{
				m_list.SetSel(0);//���ɾ����Ŀ�������ڲ��ŵģ��򽫹������Ϊ0
				OnPlay();
			}
			else//�������Ϊ��ǰ����
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
void CMPT5Dlg::OnBnClickedAddfile()//����ļ�
{
	TCHAR Buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, Buffer);//��ȡ��ǰ����·��,����dlg.DoModal()==IDOK���ú����·�����ı䣬��xp��һ��bug

	char szFileFilter[]="ý���ļ�(*.avi,*.mp3,*.wma,*.mp4,*.rmvb,*.wav,*.wmv)|*.avi;*.mp3;*.wma;*.mp4;*.rmvb;*.wav;*.wmv|";
	CFileDialog dlg(true,NULL,NULL,OFN_FILEMUSTEXIST   |   OFN_ALLOWMULTISELECT 
		|OFN_HIDEREADONLY   |   OFN_PATHMUSTEXIST     
		|   OFN_OVERWRITEPROMPT,szFileFilter,NULL);
	TCHAR*   szPathMulti   =   new   TCHAR[8*1024*   1024];   //��������Щ ,��˵��1024�ĳ�1023��ȷ
	dlg.m_ofn.nMaxFile   =   8*1024*   1024; 
	dlg.m_ofn.lpstrFile   =   szPathMulti; 
	dlg.m_ofn.lpstrFile[0]   =   0; 

	if(dlg.DoModal()==IDOK)
	{  
		SetCurrentDirectory(Buffer);//�����������·��
		CString every="\n";//������¼����ظ��ļ���·��
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
			str.Format("��һ���ļ�����\n%s",str1);
			MessageBox(str,"����");
		}
		if(count>=2)
		{
			CString str;   
			str.Format("��%d���ļ�����%s",count,every); 
			MessageBox(str,"����");
		}

		Save();
	}
}
void CMPT5Dlg::OnBnClickedAddfolder()//����ļ���
{
	char Dir[255]= "c:\\ "; 
	BROWSEINFO bi; 
	ITEMIDLIST* pidl; 
	bi.hwndOwner=NULL; 
	bi.pidlRoot=NULL; 
	bi.pszDisplayName=Dir; 
	bi.lpszTitle= "����ļ��� "; 
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
		CString str=Dir; //���˻����ѡ�ļ���·��
		int count=0;//�ظ��ļ��ĸ���
		int count2=0;//����ļ�������
		CString every="\n";//������¼����ظ��ļ���·��
		int amount=m_list.GetCount();//�����б����ļ�����
		getFolder(str,count,count2,every,amount);//���ò���ָ���ļ�����

		if(count==0)
		{
			CString str;
			str.Format("�����%d���ļ�",count2);
			MessageBox(str,"����ļ���");
		}
		if(count==1)
		{
			CString str;
			str.Format("��һ���ļ�����\n%s\n�����һ���ļ�",every);
			MessageBox(str,"����ļ���");
		}
		if(count>=2)
		{
			CString   str;   
			str.Format("��%d���ļ�����%s\n�����%d���ļ�",count,every,count2); 
			MessageBox(str,"����ļ���");
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
			if (find.IsDirectory())//������ļ��У��ݹ飬����������
			{			                      
				getFolder(fdPath,count,count2,every,amount);  
			}
			else//������ļ�
			{
				CString suffix=fdPath.Right(fdPath.GetLength()-fdPath.ReverseFind( '.')-1); //������׺��
				suffix=suffix.MakeLower();//ת��ΪСд
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
void CMPT5Dlg::OnBnClickedAddlist()//�½��б�,����¼�½��б������
{
	NewName name;
	int count=0;
	CString str;
	str.Format("�½��б�%d",m_combobox.GetCount()+1);
	name.m_newname=str;//�½��б�Ĭ����,��ɾ���б����п���Ĭ�����������б��ظ�

	if(name.DoModal()==IDOK)
	{
		if(name.m_newname=="")
		{
			MessageBox("�б����Ʋ���Ϊ��!\n����������");
			OnBnClickedAddlist();
			return;
		}
		if(name.m_newname.GetLength()>=20)
		{
			MessageBox("�б�����̫��!\n����������");
			OnBnClickedAddlist();
			return;
		}
		int judge=0;//�ж������Ƿ��������б��ظ�
		for(int i=0;i<m_combobox.GetCount();i++)
		{
			CString str;
			m_combobox.GetLBText(i,str);
			if(name.m_newname==str)
				judge=1;
		}
		if(judge==1)
		{
			MessageBox("�������б����ظ�!\n����������");
			OnBnClickedAddlist();
			return;
		}//�����жϽ���

		CString str;
		str.Format(".\\List\\EachList\\%s.txt",name.m_newname);


		CStdioFile file1;
		file1.Open(str,CFile::modeCreate);
		file1.Close();//�����½��Ĳ����б�txt�ļ�

		CStdioFile file2;
		int j=file2.Open(".\\List\\ListName.txt",CFile::modeWrite);
		file2.SeekToEnd(); 
		file2.WriteString("\n");//����
		file2.WriteString(name.m_newname);
		file2.Close();//�����б�д��ListName.txt

		int index=0;
		index=m_combobox.GetCurSel();//���µ�ǰѡ�еĲ����б�
		m_combobox.ResetContent();
		CStdioFile *fsp2=new CStdioFile(".\\List\\ListName.txt",CFile::modeRead);
		CString str2;
		while(fsp2->ReadString(str2))
		{
			m_combobox.AddString(str2);
		}
		fsp2->Close();
		delete fsp2;
		m_combobox.SetCurSel(index);//�����б������˵�ѡ��
	}
	//�����б������˵�����
}
void CMPT5Dlg::OnCbnSelchangeListcombo()//�����б������˵�ѡ�񲥷��б�
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
		str2=str2.Right(str2.GetLength()-str2.ReverseFind('\\') -1);//ֻ��ʾ������
		m_list.AddString(str2);
	}
	fsp->Close();
	int judge=0;//�жϵ�ǰ�б��Ƿ��и������ڲ��ţ�û�в��Ÿ���ʱ�б��л�ѡ������Ľ����
	if(now_list==str)
	{
		for(int i=0;i<m_list2.GetCount();i++)
		{
			CString str1;
			m_list2.GetText(i,str1);
			if(str1==m_pathname)
			{
				judge=1;
				m_list.SetSel(i);//���������Ϊ��ǰ������Ŀ		
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

void CMPT5Dlg::OnBnClickedDellist()//ɾ���б�
{
	m_player.close();
	if(m_combobox.GetCurSel()!=CB_ERR)//�ж��Ƿ�ѡ���б�
	{

		CString str;	
		m_combobox.GetLBText(m_combobox.GetCurSel(),str);//��ȡ��ǰѡ���б�

		if(str=="Ĭ���б�")
		{
			MessageBox("����ɾ��Ĭ���б�");
			return;
		}//ע�������һ��Ĭ���б���ڣ�����һ���ǲ���ɾ��
		CString dstr;
		dstr.Format(".\\List\\EachList\\%s.txt",str);
		CFile dfile;
		dfile.Remove(dstr);

		CStdioFile file;
		file.Open(".\\List\\ListName.txt",CFile::modeCreate);
		file.Close();//����б�����.txt

		int amount=m_combobox.GetCount();//��ȡ��ǰ�б�����
		for(int i=0;i<amount;i++)//��������ɾ�б�����б����б�����.txt
		{
			CString str1;
			m_combobox.GetLBText(i,str1);//�ӵ�һ����ʼ��ȡ�б�
			if(str!=str1)
			{

				CStdioFile file2;
				file2.Open(".\\List\\ListName.txt",CFile::modeWrite);
				file2.SeekToEnd(); 
				file2.WriteString(str1);
				if(i<amount-2)
				{
					file2.SeekToEnd(); 
					file2.WriteString("\n");//��ֹ����л��з�������i<amount-2ʱÿ�������ӻ��з�
				}
				file2.Close();
			}
		}//����ListName.txt�Ѹ���

		m_combobox.ResetContent();
		CStdioFile *fsp2=new CStdioFile(".\\List\\ListName.txt",CFile::modeRead);
		CString str2;
		while(fsp2->ReadString(str2))
		{
			m_combobox.AddString(str2);
		}
		fsp2->Close();
		delete fsp2;
		now_list="Ĭ���б�";////////////////////////////////////////////////////////////////////////////
		m_combobox.SetCurSel(0);//�����б������˵�,Ĭ��ѡ�е�һ��


		m_list.ResetContent();
		m_list2.ResetContent();
		CStdioFile *fsp=new CStdioFile(".\\List\\EachList\\Ĭ���б�.txt",CFile::modeRead);
		CString str4;
		while(fsp->ReadString(str4))
		{
			m_list2.AddString(str4);
			str4=str4.Right(str4.GetLength()-str4.ReverseFind('\\') -1);//ֻ��ʾ������
			m_list.AddString(str4);
		}
		fsp->Close();
		delete fsp;
		m_list.SetSel(0);//�����б���Ŀ��Ĭ��ѡ�е�һ��
		OnBnClickedDelaB();
		m_lyric.SetWindowText("");
		m_lyric.ShowWindow(SW_HIDE);
		m_geci.SetCheck(0);
		now_pathname="12";//�����Ƿ�ֹ��һ�׸軻��һ�ף��ٻ�����ʱ��ʲ���ʾ
		counts=0;
		KillTimer(3);
	}
}

void CMPT5Dlg::OnBnClickedRenamelist()//�������б�
{
	if(m_combobox.GetCurSel()!=CB_ERR)//�ж��Ƿ�ѡ���б�
	{
		CString str;
		int index=m_combobox.GetCurSel();
		m_combobox.GetLBText(index,str);//��ȡ��ǰѡ���б�����
		if(str=="Ĭ���б�")
		{
			MessageBox("����������Ĭ���б�");//Ĭ���б���������
			return;
		}
		NewName name;
		if(name.DoModal()==IDOK)
		{
			if(name.m_newname=="")
			{
				MessageBox("�б����Ʋ���Ϊ��!\n����������");
				OnBnClickedRenamelist();
				return;
			}
			if(name.m_newname.GetLength()>=20)
			{
				MessageBox("�б�����̫��!\n����������");
				OnBnClickedRenamelist();
				return;
			}
			int judge=0;//�ж������Ƿ��������б��ظ�
			for(int i=0;i<m_combobox.GetCount();i++)
			{
				CString str;
				m_combobox.GetLBText(i,str);
				if(name.m_newname==str)
					judge=1;
			}
			if(judge==1)
			{
				MessageBox("�������б����ظ�!\n����������");
				OnBnClickedRenamelist();
				return;
			}//�����жϽ���
			CString oldname;
			oldname.Format(".\\List\\EachList\\%s.txt",str);
			CString newname;
			newname.Format(".\\List\\EachList\\%s.txt",name.m_newname);
			CFile dfile;
			dfile.Rename(oldname,newname);//��ѡ�б�������


			CStdioFile file;
			file.Open(".\\List\\ListName.txt",CFile::modeCreate);
			file.Close();//����б�����.txt

			for(int i=0;i<m_combobox.GetCount();i++)//�������󽫸����б����´���б�����.txt
			{
				CString str1;
				m_combobox.GetLBText(i,str1);//�ӵ�һ����ʼ��ȡ�б�
				if(str!=str1)//��ȡ���б���Ҫ��������
				{
					CStdioFile file2;
					file2.Open(".\\List\\ListName.txt",CFile::modeWrite);
					file2.SeekToEnd(); 
					file2.WriteString(str1);
					if(i<m_combobox.GetCount()-1)
					{
						file2.SeekToEnd(); 
						file2.WriteString("\n");//��ֹ����л��з�������i<m_combobox.GetCount()-1ʱÿ�������ӻ��з�
					}
					file2.Close();
				}
				else//��ȡ���б���Ҫ��������
				{
					CStdioFile file3;
					file3.Open(".\\List\\ListName.txt",CFile::modeWrite);
					file3.SeekToEnd(); 
					file3.WriteString(name.m_newname);
					if(i<m_combobox.GetCount()-1)
					{
						file3.SeekToEnd(); 
						file3.WriteString("\n");//��ֹ����л��з�������i<m_combobox.GetCount()-1ʱÿ�������ӻ��з�
					}
					file3.Close();
				}
			}//����ListName.txt�Ѹ��£�ListName��Ӧ�б����Ƹı�

			m_combobox.ResetContent();
			CStdioFile *fsp2=new CStdioFile(".\\List\\ListName.txt",CFile::modeRead);
			CString str2;
			while(fsp2->ReadString(str2))
			{
				m_combobox.AddString(str2);
			}
			fsp2->Close();
			delete fsp2;
			m_combobox.SetCurSel(index);//�����б������˵�����ѡ�����������б�
		}
	}
}
void CMPT5Dlg::OnBnClickedResetlist()//����б�
{
	m_list.ResetContent();
	m_list2.ResetContent();
	Save();
	CString str;
	m_combobox.GetLBText(m_combobox.GetCurSel(),str);
	if(str==now_list)
		m_player.close();//�����յ������ڲ��ŵ��б���ֹͣ
	OnBnClickedDelaB();
	m_lyric.SetWindowText("");
	m_lyric.ShowWindow(SW_HIDE);
	m_geci.SetCheck(0);
	now_pathname="12";//�����Ƿ�ֹ��һ�׸軻��һ�ף��ٻ�����ʱ��ʲ���ʾ
	counts=0;
	OnBnClickedDelaB();
	KillTimer(3);
}

void CMPT5Dlg::OnBnClickedUp()//������Ŀ
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
	m_list2.GetText(index2,str2);//���½�Ҫ��ɾ����Ŀ·��

	OnBnClickedRemovefile();//ɾ����һ����Ŀ
	
	m_list.InsertString(index1,str);
	m_list2.InsertString(index1,str2);//�嵽������Ŀ������
	CString str3;
	for(int i=0;i<m_list.GetCount();i++)
	{
		m_list2.GetText(i,str3);
		if(str3==m_pathname)
			m_list.SetSel(i,0);
	}
	m_list.SetSel(index2);//��ʱ�����������ò��InsertString���ǿ������ģ������ðѲ��ŵ��Ǹ�ȥ�����ѿ��������Ǹ�����
	Save();
	if(condition==0)
	{
		m_player.close();
		m_list.SetSel(index2);
	}//������������ŵĻ�������֮�����û�ˣ��������ù��
}

void CMPT5Dlg::OnBnClickedDown()//������Ŀ
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
	m_list2.GetText(index2,str2);//���½�Ҫ��ɾ����Ŀ·��
	
	OnBnClickedRemovefile();//ɾ����һ����Ŀ
	
	m_list.InsertString(index1,str);
	m_list2.InsertString(index1,str2);//�嵽������Ŀ������
	CString str3;
	for(int i=0;i<m_list.GetCount();i++)
	{
		m_list2.GetText(i,str3);
		if(str3==m_pathname)
			m_list.SetSel(i,0);
	}
	m_list.SetSel(index2);//��ʱ�����������ò��InsertString���ǿ������ģ������ðѲ��ŵ��Ǹ�ȥ�����ѿ��������Ǹ�����
	Save();
	if(condition==0)
	{
		m_player.close();
		m_list.SetSel(index2);
	}//������������ŵĻ�������֮�����û�ˣ��������ù��
}
void CMPT5Dlg::OnBnClickedPrevious()//��һ��
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
		}//���µ�ǰ������Ŀ��λ��
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

void CMPT5Dlg::OnBnClickedNext()//��һ��
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
		}//���µ�ǰ������Ŀ��λ��
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
//A-B����ѭ�����Ź���
void CMPT5Dlg::OnBnClickedSetAB()
{
	int pos = 7;//����ڶԻ����еĺ�����
	int index=m_player.GetPlayState();//����״̬
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
					MessageBox("�������յ㣬���������á�");
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
			int index=m_player.GetPlayState();//����״̬
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
	int index=m_player.GetPlayState();//����״̬
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

	GetCursorPos(&point); //ȡ�õ�ǰ��������
	if (::WindowFromPoint(point)==m_list) //�ӵ�ǰ����������������ڴ��ڵľ�������ж��Ƿ�ΪLISTBOX�ؼ� 
		m_list.ScreenToClient(&point);  //�� ��GetCursorPos�������ص��������������Ļ������ֵ�������Ҫ���������ֵת���������ListBox ������.
	BOOL bIn;
	int nNindex=m_list.ItemFromPoint (point  ,bIn);//��������������Ŀǰ���ڵ�LISTBOX��Ŀ����
	m_list2.GetText(nNindex,strTxt);//���n��Ŀ��·��
	/////////////////////////////�����Ϣ/////////////////////////////////////////////
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
		///////////////////////����ģʽ//////////////////////////////////
		int index=m_player.GetPlayState();//����״̬
		if(index==1)//����������
		{	
			SetList();//������ŵ��б�͵�ǰ�б�һ�£�ת���б�
			CString playmode;
			m_combobox2.GetLBText(m_combobox2.GetCurSel(),playmode);//��ȡ����ģʽ
			if(playmode=="˳�򲥷�")//˳�򲥷�
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
				}//���µ�ǰ������Ŀ��λ��
				index++;
				if(index>=m_list.GetCount()) 
				{
					index=0;//������������һ��
					m_play.LoadBitmaps(IDB_Play1);
					m_play.RedrawWindow();
					m_list.SetSel(index-1,0);
					m_list.SetSel(index);//�Զ��ù��
					m_player.close();
				}		
				else
				{
					m_list.SetSel(index-1,0);
					m_list.SetSel(index);//�Զ��ù��
					CString str;
					m_list2.GetText(index,str);
					if(PathFileExists(str))
					{
						if(m_pathname==str)//����ٴβ�����Ŀ�������ף����Ҫ����
						{
							m_lyric.SetWindowText("");
							counts=0;
						}
						if(m_pathname!=str)//����ٴβ�����Ŀ�������ף����ѡ�򹴵��������ʾ������
						{
							m_lyric.SetWindowText("");
							m_lyric.ShowWindow(SW_HIDE);
							m_geci.SetCheck(0);
							now_pathname="12";//�����Ƿ�ֹ��һ�׸軻��һ�ף��ٻ�����ʱ��ʲ���ʾ
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
			if(playmode=="�б�ѭ��")//������б�ѭ������
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
						m_list.SetSel(i,0);//������Ӧ�Ե�������ڲ���һ����Ŀ��Ȼ��ѡ����һ�׻��㼸�ף����׷���ʱҪ��ѡ�еĹ�궼���
				}//���µ�ǰ������Ŀ��λ��
				index++;
				if(index>=m_list.GetCount()) 
					index=0;//������������һ��
				m_list.SetSel(index-1,0);
				m_list.SetSel(index);//�Զ��ù��
				CString str;
				m_list2.GetText(index,str);
				if(PathFileExists(str))
				{
					if(m_pathname==str)//����ٴβ�����Ŀ�������ף����Ҫ����
					{
						m_lyric.SetWindowText("");
						counts=0;
					}
					if(m_pathname!=str)//����ٴβ�����Ŀ�������ף����ѡ�򹴵��������ʾ������
					{
						m_lyric.SetWindowText("");
						m_lyric.ShowWindow(SW_HIDE);
						m_geci.SetCheck(0);
						now_pathname="12";//�����Ƿ�ֹ��һ�׸軻��һ�ף��ٻ�����ʱ��ʲ���ʾ
						counts=0;
						KillTimer(3);
					}
					m_player.SetUrl(str);
					m_pathname=str;
					InitialSlider();
				}
				else
					OnBnClickedRemovefile();
				
			}//������ʵ�����б�ѭ������
			if(playmode=="�������")//�������
			{
				OnBnClickedDelaB();
				for(int i=0;i<m_list.GetCount();i++)
				{
					CString str;
					m_list2.GetText(i,str);
					if(str!=m_pathname)
						m_list.SetSel(i,0);//������Ӧ�Ե�������ڲ���һ����Ŀ��Ȼ��ѡ����һ�׻��㼸�ף����׷���ʱҪ��ѡ�еĹ�궼���
				}
				srand(time(0));//Ŀ������ÿ�ζ��ܲ�����ͬ�����������
				int num=rand()%m_list.GetCount();
				m_list.SetSel(m_list.GetCurSel(),0);
				m_list.SetSel(num);//����ù��	
				CString str;
				m_list2.GetText(num,str);
				if(PathFileExists(str))
				{
					if(m_pathname==str)//����ٴβ�����Ŀ�������ף����Ҫ����
					{
						m_lyric.SetWindowText("");
						counts=0;
					}
					if(m_pathname!=str)//����ٴβ�����Ŀ�������ף����ѡ�򹴵��������ʾ������
					{
						m_lyric.SetWindowText("");
						m_lyric.ShowWindow(SW_HIDE);
						m_geci.SetCheck(0);
						now_pathname="12";//�����Ƿ�ֹ��һ�׸軻��һ�ף��ٻ�����ʱ��ʲ���ʾ
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
			if(playmode=="����ѭ��")//����ѭ��
			{
				OnBnClickedDelaB();
				for(int i=0;i<m_list.GetCount();i++)
				{
					CString str;
					m_list2.GetText(i,str);
					if(str!=m_pathname)
						m_list.SetSel(i,0);//������Ӧ�Ե�������ڲ���һ����Ŀ��Ȼ��ѡ����һ�׻��㼸�ף����׷���ʱҪ��ѡ�еĹ�궼���
					else
						m_list.SetSel(i);
				}
				m_player.SetUrl(m_pathname);
				InitialSlider();
				counts=0;
			}
		}
		//////////////////���㲥��////////////////////////

		if (static_cast<int>(m_ctr.GetCurrentPosition()) == static_cast<int>(endP))
		{
			m_ctr.SetCurrentPosition(startP);
			m_slider.SetPos((int)startP);
		}
		//////////////////����������/////////////
		sliderPos =(int)m_ctr.GetCurrentPosition();
		m_slider.SetPos(sliderPos);
		m_time.SetWindowText(StandardTime((int)m_slider.GetPos(),(int)duration));
		CDialog::OnTimer(nIDEvent);

		/////////////////���///////////////////

	}
	if(nIDEvent==2)
	{
		KillTimer(2);
		BreakPoint BP;
		CStdioFile *fsp=new CStdioFile(".\\List\\BreakPoint.txt",CFile::modeRead);
		CString listname;
		if(0==fsp->ReadString(listname))//���breakpoint.txt�ǿյģ������ϵ�Ի���
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
		if(BP.DoModal()==IDOK)//���ѡ��ϵ�����
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
			}//ת�������б�
			CString m_strFolderPath;
			m_strFolderPath.Format(".\\List\\EachList\\%s.txt",now_list);
			m_list.ResetContent();
			m_list2.ResetContent();

			CString str2;
			CStdioFile *fsp=new CStdioFile(m_strFolderPath,CFile::modeRead);
			while(fsp->ReadString(str2))
			{
				m_list2.AddString(str2);
				str2=str2.Right(str2.GetLength()-str2.ReverseFind('\\') -1);//ֻ��ʾ������
				m_list.AddString(str2);
			}
			fsp->Close();//Ȼ��ˢ�²����б�
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
		if(m_ctr.GetCurrentPosition()>=dtime[counts])//������
		{
			m_lyric.SetWindowText(strcontainer[counts]);
			counts++;
		}
		if(counts>=1)
		{
			while(m_ctr.GetCurrentPosition()<dtime[counts-1])//��Ӧ�����϶�
			{
				counts--;
			}
		}
		while(m_ctr.GetCurrentPosition()>dtime[counts+1])//��Ӧ�����϶�
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
		int count1=0;//�ظ��ļ��ĸ���
		CString every;//�ظ��ļ���·��  
		int count3=0;//��֧�ָ�ʽ���ļ��ĸ���
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
				int judge=0;//�ж��ظ�
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
			str2.Format("��%d���ļ���ʽ��֧��!",count3);
			MessageBox(str2,"�Ϸ��ļ�");	
		}
		if(count1==0)//û���ظ�
		{
			CString str2;
			str2.Format("�����%d���ļ�",count-count3);
			MessageBox(str2,"�Ϸ��ļ�");		
		}
		else
		{
			CString str2;
			str2.Format("��%d���ļ��ظ�\n%s\n�����%d���ļ�",count1,every,count-count1-count3);
			MessageBox(str2,"�Ϸ��ļ�");
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
//�½�һ����ʼ���������ĺ��������ڸ�������ģʽ����ӡ�
void CMPT5Dlg::InitialSlider()
{	
	m_media = static_cast<CWMPMedia>(m_player.newMedia(m_pathname));
	m_slider.SetPos(0);//������������ʼ��
	duration = m_media.GetDuration();
	m_time.SetWindowText(StandardTime(0,(int)duration));//��ʾ��ʱ��
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


void CMPT5Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)//��������
{
	int m_nCur;
	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	m_nCur=pSlidCtrl->GetPos();//ȡ�õ�ǰλ��ֵ
	if (!m_settings.GetMute())
	{
		m_settings.SetVolume(-m_nCur);
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	SetFocus();
}

void CMPT5Dlg::OnBnClickedButton1()//����
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
bool CMPT5Dlg::ReadLyricsFile(CString str)//��������������������  
{  
	str=str.Right(str.GetLength()-str.ReverseFind('\\') -1);//ֻ��ʾ������
	str=str.Left(str.GetLength()-4);
	CString sn;
	sn.Format(".\\List\\Lyrics\\%s.lrc",str);
	CStdioFile file;
	if(!file.Open(sn,CFile::modeRead))
	{
		MessageBox("����ļ�������!");
		m_geci.SetCheck(0);
		return 0;
	}//�������ļ������ڣ���return	
	now_pathname=m_pathname;//���¸����Ŀ
    m_lyric.ShowWindow(SW_SHOW);
	CString strline;//ÿһ�е�ʱ���Լ����
	CString time;//ʱ��
	CString lr;//���
	CStringArray tagcontainer;//������ʱ���ǩ
    strcontainer.RemoveAll();
	while(file.ReadString(strline))//������ǿմ�������û�е�ĩβ���Ͷ�����һ��
	{
		lr = strline.Right(strline.GetLength()-strline.ReverseFind( ']')-1); 
		if(lr!="")//�����ʲ��ǿմ���ǰ��϶���ʱ���ǩ
		{     
			time=strline.Left(strline.Find(']')+1);
			tagcontainer.Add(time);//�ӵ�һ��ʱ���ǩ
			strcontainer.Add(lr);//�ӱ��и��
			strline=strline.Left(strline.GetLength()-lr.GetLength());//ȡstrline��ȥ��ʵĲ��֣���ֻ��ʱ���ǩ
			while(1)
			{
				strline=strline.Right(strline.GetLength()-strline.Find(']')-1);
				if(strline=="")
					break;
				time=strline.Left(strline.Find(']')+1);
				tagcontainer.Add(time);//��ʱ���ǩ
				strcontainer.Add(lr);//�ӱ��и��
			}
		}//����һ�е�ʱ���ǩ�͸����ȡ���
	}//��������ʱ���ǩ�͸����ȡ���
	file.Close();
	for(int i=0;i<tagcontainer.GetSize();i++)//��ʱ���ǩת��Ϊdouble�͵�ʱ��
	{
		dtime[i]=((int)(tagcontainer[i][1])-48)*600+((int)(tagcontainer[i][2])-48)*60+((int)(tagcontainer[i][4])-48)*10+
			(int)(tagcontainer[i][5])-48+((double)(tagcontainer[i][7])-48)*0.1+((double)(tagcontainer[i][8])-48)*0.01;
	}//ʱ���Ѿ�ת��Ϊdouble��
	for(int i=0;i<strcontainer.GetUpperBound();i++)//һ������ô���
	{
		for(int j=strcontainer.GetUpperBound();j-i>0;j--)//ÿ�αȽ���ô���
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
	}//����������
	return 1;
}  
void CMPT5Dlg::OnBnClickedCheck1()//�Ƿ���ʾ��ʵĹ�ѡ��
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
			str=m_pathname.Right(m_pathname.GetLength()-m_pathname.ReverseFind( '.')-1); //������׺��
			if(str=="mp3"||str=="wma"||str=="wmv")//�ж��Ƿ�����Ƶ��ʽ
			{
				counts=0;

				if(m_player.GetPlayState()==3)
				{
					if(ReadLyricsFile(m_pathname))
					{
						while(m_ctr.GetCurrentPosition()>=dtime[counts])
						{
							counts++;
						}//�����ʱ���˺�һ��
						counts--;
						//�Ƚ���ʵ�����һ��
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
