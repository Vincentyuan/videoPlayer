#pragma once
#include "afxwin.h"


// BreakPoint 对话框

class BreakPoint : public CDialog
{
	DECLARE_DYNAMIC(BreakPoint)

public:
	BreakPoint(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BreakPoint();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_breakpoint;
	CString m_bp;
};
