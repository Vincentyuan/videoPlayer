// DelHistory.cpp : implementation file
//
#include "stdafx.h"
#include "MPT5.h"
#include "DelHistory.h"


// DelHistory dialog

IMPLEMENT_DYNAMIC(DelHistory, CDialog)

DelHistory::DelHistory(CWnd* pParent /*=NULL*/)
	: CDialog(DelHistory::IDD, pParent)
{

}

DelHistory::~DelHistory()
{
}

void DelHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_delhistory);
}


BEGIN_MESSAGE_MAP(DelHistory, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, &DelHistory::OnBnClickedCheck1)
END_MESSAGE_MAP()


// DelHistory message handlers

void DelHistory::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	HWND hWnd = ::FindWindow(NULL,"MPT5");
	if(hWnd!= NULL ){
		::SendMessage(hWnd,WM_MYMESSAGE_CLICKED,0,0);
	}
}
