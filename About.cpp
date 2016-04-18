// About.cpp : implementation file
//

#include "stdafx.h"
#include "MPT5.h"
#include "About.h"


// About dialog

IMPLEMENT_DYNAMIC(About, CDialog)

About::About(CWnd* pParent /*=NULL*/)
	: CDialog(About::IDD, pParent)
{

}

About::~About()
{
}

void About::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(About, CDialog)
END_MESSAGE_MAP()


// About message handlers
