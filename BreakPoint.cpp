// BreakPoint.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MPT5.h"
#include "BreakPoint.h"


// BreakPoint �Ի���

IMPLEMENT_DYNAMIC(BreakPoint, CDialog)

BreakPoint::BreakPoint(CWnd* pParent /*=NULL*/)
	: CDialog(BreakPoint::IDD, pParent)
	, m_bp(_T(""))
{

}

BreakPoint::~BreakPoint()
{
}

void BreakPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_breakpoint);
	DDX_Text(pDX, IDC_EDIT1, m_bp);
}


BEGIN_MESSAGE_MAP(BreakPoint, CDialog)
END_MESSAGE_MAP()


// BreakPoint ��Ϣ�������
