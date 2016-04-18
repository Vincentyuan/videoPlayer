// NewName.cpp : implementation file
//

#include "stdafx.h"
#include "MPT5.h"
#include "NewName.h"


// NewName dialog

IMPLEMENT_DYNAMIC(NewName, CDialog)

NewName::NewName(CWnd* pParent /*=NULL*/)
	: CDialog(NewName::IDD, pParent)
	, m_newname(_T(""))
{

}

NewName::~NewName()
{
}

void NewName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_newname);
}


BEGIN_MESSAGE_MAP(NewName, CDialog)
END_MESSAGE_MAP()


// NewName message handlers
