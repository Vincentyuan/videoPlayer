#pragma once


// NewName dialog

class NewName : public CDialog
{
	DECLARE_DYNAMIC(NewName)

public:
	NewName(CWnd* pParent = NULL);   // standard constructor
	virtual ~NewName();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_newname;
};
