#pragma once
#include "afxwin.h"


// BreakPoint �Ի���

class BreakPoint : public CDialog
{
	DECLARE_DYNAMIC(BreakPoint)

public:
	BreakPoint(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BreakPoint();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_breakpoint;
	CString m_bp;
};
