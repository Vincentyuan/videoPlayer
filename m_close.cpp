// m_close.cpp : 实现文件
//

#include "stdafx.h"
#include "MPT5.h"
#include "m_close.h"


// m_close 对话框

IMPLEMENT_DYNAMIC(m_close, CDialog)

m_close::m_close(CWnd* pParent /*=NULL*/)
	: CDialog(m_close::IDD, pParent)
{

}

m_close::~m_close()
{
}

void m_close::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(m_close, CDialog)
	ON_BN_CLICKED(IDOK, &m_close::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &m_close::OnBnClickedCancel)
END_MESSAGE_MAP()


// m_close 消息处理程序
void m_close::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	HWND hWnd = ::FindWindow(NULL,"MPT5");
	if(hWnd!= NULL ){
		::SendMessage(hWnd,WM_MYMESSAGE2,0,0);
	}
	OnOK();
}

void m_close::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	HWND hWnd = ::FindWindow(NULL,_T("MPT5"));
	if(hWnd!= NULL ){
		::SendMessage(hWnd,WM_MYMESSAGE1,0,0);
	}
	OnCancel();
}