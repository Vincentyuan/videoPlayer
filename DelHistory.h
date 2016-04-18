#pragma once
#include "afxwin.h"

#define  WM_MYMESSAGE_CLICKED (WM_USER+5)
// DelHistory dialog

class DelHistory : public CDialog
{
	DECLARE_DYNAMIC(DelHistory)

public:
	DelHistory(CWnd* pParent = NULL);   // standard constructor
	virtual ~DelHistory();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_delhistory;
	afx_msg void OnBnClickedCheck1();
};
